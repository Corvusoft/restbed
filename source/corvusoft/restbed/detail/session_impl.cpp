/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <regex>
#include <utility>
#include <stdexcept>

//Project Includes
#include "corvusoft/restbed/uri.hpp"
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/response.hpp"
#include "corvusoft/restbed/resource.hpp"
#include "corvusoft/restbed/settings.hpp"
#include "corvusoft/restbed/context_value.hpp"
#include "corvusoft/restbed/session_manager.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"
#include "corvusoft/restbed/detail/request_impl.hpp"
#include "corvusoft/restbed/detail/session_impl.hpp"
#include "corvusoft/restbed/detail/resource_impl.hpp"

//External Includes

//System Namespaces
using std::map;
using std::set;
using std::regex;
using std::smatch;
using std::string;
using std::getline;
using std::istream;
using std::function;
using std::multimap;
using std::make_pair;
using std::exception;
using std::to_string;
using std::ssub_match;
using std::shared_ptr;
using std::make_shared;
using std::regex_match;
using std::regex_error;
using std::runtime_error;
using std::placeholders::_1;
using std::rethrow_exception;
using std::current_exception;
using std::chrono::hours;
using std::chrono::minutes;
using std::chrono::seconds;
using std::chrono::milliseconds;
using std::chrono::microseconds;
using std::chrono::duration_cast;

//Project Namespaces
using restbed::detail::SessionImpl;

//External Namespaces
using asio::buffer;
using asio::error_code;

namespace restbed
{
    namespace detail
    {
        SessionImpl::SessionImpl( void ) : m_id( "" ),
            m_logger( nullptr ),
            m_session( nullptr ),
            m_socket( nullptr ),
            m_request( nullptr ),
            m_resource( nullptr ),
            m_settings( nullptr ),
            m_session_manager( nullptr ),
            m_buffer( nullptr ),
            m_headers( ),
            m_router( nullptr ),
            m_error_handler( nullptr )
        {
            return;
        }
        
        SessionImpl::~SessionImpl( void )
        {
            return;
        }

        void SessionImpl::erase( const string& name )
        {
            if ( name.empty( ) )
            {
                m_context.clear( );
            }
            else
            {
                m_context.erase( name );
            }
        }

        bool SessionImpl::has( const string& name ) const
        {
            return m_context.find( name ) not_eq m_context.end( );
        }

        const set< string > SessionImpl::keys( void ) const
        {
            std::set< std::string > keys;

            for( const auto& value : m_context )
            {
                keys.insert( keys.end( ), value.first );
            }

            return keys;
        }
        
        bool SessionImpl::is_open( void ) const
        {
            return m_socket not_eq nullptr and m_socket->is_open( );
        }
        
        bool SessionImpl::is_closed( void ) const
        {
            return not is_open( );
        }
        
        void SessionImpl::close( void )
        {
            m_session_manager->purge( m_session, [ this ]( const shared_ptr< Session >& )
            {
                m_socket->close( );
            } );
        }
        
        void SessionImpl::close( const Bytes& body )
        {
            m_socket->write( body, [ this ]( const asio::error_code & error, size_t )
            {
                if ( error )
                {
                    const auto message = String::format( "Close failed: %s", error.message( ).data( ) );
                    failure( 500, runtime_error( message ), m_session );
                }
                else
                {
                    close( );
                }
            } );
        }

        void SessionImpl::close( const string& body )
        {
            close( Bytes( body.begin( ), body.end( ) ) );
        }

        void SessionImpl::close( const Response& response )
        {
            transmit( response, [ this ]( const asio::error_code & error, size_t )
            {
                if ( error )
                {
                    const auto message = String::format( "Close failed: %s", error.message( ).data( ) );
                    failure( 500, runtime_error( message ), m_session );
                }
                
                m_socket->close( );
                m_session_manager->purge( m_session, nullptr );
            } );
        }
        
        void SessionImpl::close( const int status, const string& body, const multimap< string, string >& headers )
        {
            close( status, String::to_bytes( body ), headers );
        }
        
        void SessionImpl::close( const int status, const Bytes& body, const multimap< string, string >& headers )
        {
            Response response;
            response.set_body( body );
            response.set_headers( headers );
            response.set_status_code( status );
            
            close( response );
        }
        
        void SessionImpl::yield( const Bytes& body, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            m_socket->write( body, [ this, callback ]( const asio::error_code & error, size_t )
            {
                if ( error )
                {
                    const auto message = String::format( "Yield failed: %s", error.message( ).data( ) );
                    failure( 500, runtime_error( message ), m_session );
                }
                else
                {
                    callback( m_session );
                }
            } );
        }

        void SessionImpl::yield( const string& body, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            yield( String::to_bytes( body ), callback );
        }
        
        void SessionImpl::yield( const Response& response, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            transmit( response, [ this, callback ]( const asio::error_code & error, size_t )
            {
                if ( error )
                {
                    const auto message = String::format( "Yield failed: %s", error.message( ).data( ) );
                    failure( 500, runtime_error( message ), m_session );
                }
                else
                {
                    if ( callback == nullptr )
                    {
                        fetch( m_session, m_router );
                    }
                    else
                    {
                        callback( m_session );
                    }
                }
            } );
        }

        void SessionImpl::yield( const int status, const string& body, const multimap< string, string >& headers, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            yield( status, String::to_bytes( body ), headers, callback );
        }
        
        void SessionImpl::yield( const int status, const Bytes& body, const multimap< string, string >& headers, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            Response response;
            response.set_body( body );
            response.set_headers( headers );
            response.set_status_code( status );
            
            yield( response, callback );
        }
        
        void SessionImpl::fetch( const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            fetch( m_session, callback );
        }
        
        void SessionImpl::fetch( const shared_ptr< Session >& session, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            if ( m_router == nullptr and m_session == nullptr )
            {
                m_session = session;
                m_router = callback;
            }
            
            m_buffer = make_shared< asio::streambuf >( );
            
            m_socket->read( m_buffer, "\r\n\r\n", bind( &SessionImpl::parse_request, this, _1, m_session, callback ) );
        }
        
        void SessionImpl::fetch( const size_t length, const function< void ( const shared_ptr< Session >&, const Bytes& ) >& callback )
        {
            if ( length > m_buffer->size( ) )
            {
                size_t size = length - m_buffer->size( );
                
                m_socket->read( m_buffer, size, [ this, length, callback ]( const asio::error_code & error, size_t )
                {
                    if ( error )
                    {
                        const auto message = String::format( "Fetch failed: %s", error.message( ).data( ) );
                        failure( 500, runtime_error( message ), m_session );
                    }
                    else
                    {
                        const auto data = fetch_body( length );
                        callback( m_session, data );
                    }
                } );
            }
            else
            {
                const auto data = fetch_body( length );
                callback( m_session, data );
            }
        }
        
        void SessionImpl::fetch( const string& delimiter, const function< void ( const shared_ptr< Session >&, const Bytes& ) >& callback )
        {
            m_socket->read( m_buffer, delimiter, [ this, callback ]( const asio::error_code & error, size_t length )
            {
                if ( error )
                {
                    const auto message = String::format( "Fetch failed: %s", error.message( ).data( ) );
                    failure( 500, runtime_error( message ), m_session );
                }
                else
                {
                    const auto data = fetch_body( length );
                    callback( m_session, data );
                }
            } );
        }
        
        void SessionImpl::wait_for( const hours& delay, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            wait_for( duration_cast< microseconds >( delay ), callback );
        }
        
        void SessionImpl::wait_for( const minutes& delay, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            wait_for( duration_cast< microseconds >( delay ), callback );
        }
        
        void SessionImpl::wait_for( const seconds& delay, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            wait_for( duration_cast< microseconds >( delay ), callback );
        }
        
        void SessionImpl::wait_for( const milliseconds& delay, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            wait_for( duration_cast< microseconds >( delay ), callback );
        }
        
        void SessionImpl::wait_for( const microseconds& delay, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            m_socket->wait( delay, [ callback, this ]( const error_code & error )
            {
                if ( error )
                {
                    const auto message = String::format( "Wait failed: %s", error.message( ).data( ) );
                    failure( 500, runtime_error( message ), m_session );
                }
                else
                {
                    callback( m_session );
                }
            } );
        }

        void SessionImpl::wait_for( const hours& interval, const function< hours ( const hours& ) >& trigger, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            wait_for( duration_cast< microseconds >( interval ), [ trigger ]( const microseconds& interval )
            {
                return duration_cast< microseconds >( trigger( duration_cast< hours >( interval ) ) );
            }, callback );
        }
        
        void SessionImpl::wait_for( const minutes& interval, const function< minutes ( const minutes& ) >& trigger, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            wait_for( duration_cast< microseconds >( interval ), [ trigger ]( const microseconds& interval )
            {
                return duration_cast< microseconds >( trigger( duration_cast< minutes >( interval ) ) );
            }, callback );
        }
        
        void SessionImpl::wait_for( const seconds& interval, const function< seconds ( const seconds& ) >& trigger, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            wait_for( duration_cast< microseconds >( interval ), [ trigger ]( const microseconds& interval )
            {
                return duration_cast< microseconds >( trigger( duration_cast< seconds >( interval ) ) );
            }, callback );
        }
        
        void SessionImpl::wait_for( const milliseconds& interval, const function< milliseconds ( const milliseconds& ) >& trigger, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            wait_for( duration_cast< microseconds >( interval ), [ trigger ]( const microseconds& interval )
            {
                return duration_cast< microseconds >( trigger( duration_cast< milliseconds >( interval ) ) );
            }, callback );
        }
        
        void SessionImpl::wait_for( const microseconds& interval, const function< microseconds ( const microseconds& ) >& trigger, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            m_socket->wait( interval, [ interval, trigger, callback, this ]( const error_code & error )
            {
                if ( error )
                {
                    const auto message = String::format( "Wait failed: %s", error.message( ).data( ) );
                    failure( 500, runtime_error( message ), m_session );
                }
                else
                {
                    const microseconds new_interval = trigger( interval );

                    if ( new_interval == microseconds::zero( ) )
                    {
                        callback( m_session );
                    }
                    else
                    {
                        wait_for( new_interval, trigger, callback );
                    }
                }
            } );
        }
        
        const string& SessionImpl::get_id( void ) const
        {
            return m_id;
        }
        
        const string SessionImpl::get_origin( void ) const
        {
            if ( m_socket == nullptr )
            {
                return "";
            }

            return m_socket->get_remote_endpoint( );
        }
        
        const string SessionImpl::get_destination( void ) const
        {
            if ( m_socket == nullptr )
            {
                return "";
            }
            
            return m_socket->get_local_endpoint( );
        }
        
        const shared_ptr< const Request >& SessionImpl::get_request( void ) const
        {
            return m_request;
        }
        
        const shared_ptr< const Resource >& SessionImpl::get_resource( void ) const
        {
            return m_resource;
        }
        
        const multimap< string, string >& SessionImpl::get_headers( void ) const
        {
            return m_headers;
        }

        const ContextValue& SessionImpl::get( const string& name ) const
        {
            return m_context.at( name );
        }

        const ContextValue& SessionImpl::get( const string& name, const ContextValue& default_value ) const
        {
            if ( has( name ) )
            {
                return m_context.at( name );
            }

            return default_value;
        }
            
        void SessionImpl::set( const string& name, const ContextValue& value )
        {
            m_context.insert( make_pair( name, value ) );
        }
        
        void SessionImpl::set_id( const string& value )
        {
            m_id = value;
        }
        
        void SessionImpl::set_logger(  const shared_ptr< Logger >& value )
        {
            m_logger = value;
        }

        void SessionImpl::set_socket( const shared_ptr< SocketImpl >& value )
        {            
            m_socket = value;
        }
        
        void SessionImpl::set_request( const shared_ptr< const Request >& value )
        {
            m_request = value;
        }
        
        void SessionImpl::set_resource( const shared_ptr< const Resource >& value )
        {
            m_resource = value;
        }
        
        void SessionImpl::set_settings( const shared_ptr< const Settings >& value )
        {
            m_settings = value;
        }
        
        void SessionImpl::set_header( const string& name, const string& value )
        {
            m_headers.insert( make_pair( name, value ) );
        }
        
        void SessionImpl::set_headers( const multimap< string, string >& values )
        {
            m_headers = values;
        }

        void SessionImpl::set_session_manager( const shared_ptr< SessionManager >& value )
        {
            m_session_manager = value;
        }
        
        void SessionImpl::set_error_handler( const function< void ( const int, const exception&, const shared_ptr< Session >& ) >& value )
        {
            m_error_handler = value;
        }
        
        Bytes SessionImpl::fetch_body( const size_t length ) const
        {
            const auto data_ptr = asio::buffer_cast< const Byte* >( m_buffer->data( ) );
            const auto data = Bytes( data_ptr, data_ptr + length );
            m_buffer->consume( length );
            
            const auto request = m_session->m_pimpl->get_request( );
            auto body = request->get_body( );
            
            if ( body.empty( ) )
            {
                request->m_pimpl->set_body( data );
            }
            else
            {
                body.insert( body.end( ), data.begin( ), data.end( ) );
                request->m_pimpl->set_body( body );
            }
            
            return data;
        }
        
        void SessionImpl::log( const Logger::Level level, const string& message ) const
        {
            if ( m_logger not_eq nullptr )
            {
                m_logger->log( level, "%s", message.data( ) );
            }
        }
        
        void SessionImpl::failure( const int status, const exception& error, const shared_ptr< Session >& session ) const
        {
            auto error_handler = m_error_handler;
            
            if ( session->get_resource( ) not_eq nullptr )
            {
                auto resource = session->get_resource( );
                auto handler = resource->m_pimpl->get_error_handler( );
                
                if ( handler not_eq nullptr )
                {
                    error_handler = handler;
                }
            }
            
            if ( error_handler not_eq nullptr )
            {
                error_handler( status, error, session );
            }
            else
            {
                log( Logger::Level::ERROR, String::format( "Error %i, %s", status, error.what( ) ) );
                
                string body = error.what( );
                session->close( status, body, { { "Content-Type", "text/plain" }, { "Content-Length", ::to_string( body.length( ) ) } } );
            }
        }
        
        void SessionImpl::transmit( const Response& response, const function< void ( const asio::error_code&, size_t ) >& callback ) const
        {
            auto headers = m_settings->get_default_headers( );
            
            if ( m_resource not_eq nullptr )
            {
                const auto hdrs = m_resource->m_pimpl->get_default_headers( );
                headers.insert( hdrs.begin( ), hdrs.end( ) );
            }
            
            auto hdrs = m_session->get_headers( );
            headers.insert( hdrs.begin( ), hdrs.end( ) );
            
            hdrs = response.get_headers( );
            headers.insert( hdrs.begin( ), hdrs.end( ) );

            Response payload;
            payload.set_headers( headers );
            payload.set_body( response.get_body( ) );
            payload.set_version( response.get_version( ) );
            payload.set_protocol( response.get_protocol( ) );
            payload.set_status_code( response.get_status_code( ) );
            payload.set_status_message( response.get_status_message( ) );
            
            if ( payload.get_status_message( ).empty( ) )
            {
                payload.set_status_message( m_settings->get_status_message( payload.get_status_code( ) ) );
            }

            m_socket->write( payload.to_bytes( ), callback );
        }
        
        const map< string, string > SessionImpl::parse_request_line( istream& stream )
        {
            smatch matches;
            static const regex pattern( "^([0-9a-zA-Z]*) ([a-zA-Z0-9:@_~!,;=#%&'\\-\\.\\/\\?\\$\\(\\)\\*\\+]+) (HTTP\\/[0-9]\\.[0-9])\\s*$" );
            string data = "";
            getline( stream, data );
            
            if ( not regex_match( data, matches, pattern ) or matches.size( ) not_eq 4 )
            {
                throw runtime_error( "Your client has issued a malformed or illegal request status line. That’s all we know." );
            }
            
            const string protocol = matches[ 3 ].str( );
            const auto delimiter = protocol.find_first_of( "/" );
            
            return map< string, string >
            {
                { "path", matches[ 2 ].str( ) },
                { "method", matches[ 1 ].str( ) },
                { "version", protocol.substr( delimiter + 1 ) },
                { "protocol", protocol.substr( 0, delimiter ) }
            };
        }
        
        const multimap< string, string > SessionImpl::parse_request_headers( istream& stream )
        {
            smatch matches;
            string data = "";
            multimap< string, string > headers;
            static const regex pattern( "^([^:.]*): *(.*)\\s*$" );
            
            while ( getline( stream, data ) and data not_eq "\r" )
            {
                if ( not regex_match( data, matches, pattern ) or matches.size( ) not_eq 3 )
                {
                    throw runtime_error( "Your client has issued a malformed or illegal request header. That’s all we know." );
                }
                
                headers.insert( make_pair( matches[ 1 ].str( ), matches[ 2 ].str( ) ) );
            }
            
            return headers;
        }
        
        void SessionImpl::parse_request( const asio::error_code& error, const shared_ptr< Session >& session, const function< void ( const shared_ptr< Session >& ) >& callback ) const
        
        try
        {
            if ( error )
            {
                throw runtime_error( error.message( ) );
            }
            
            istream stream( m_buffer.get( ) );
            const auto items = parse_request_line( stream );
            const auto uri = Uri::parse( "http://localhost" + items.at( "path" ) );
            
            auto request = make_shared< Request >( );
            request->m_pimpl->set_path( Uri::decode( uri.get_path( ) ) );
            request->m_pimpl->set_method( items.at( "method" ) );
            request->m_pimpl->set_version( stod( items.at( "version" ) ) );
            request->m_pimpl->set_headers( parse_request_headers( stream ) );
            request->m_pimpl->set_query_parameters( uri.get_query_parameters( ) );
            
            session->m_pimpl->set_request( request );

            callback( session );
        }
        catch ( const int status_code )
        {
            runtime_error re( m_settings->get_status_message( status_code ) );
            failure( status_code, re, session );
        }
        catch ( const regex_error& re )
        {
            failure( 500, re, session );
        }
        catch ( const runtime_error& re )
        {
            failure( 400, re, session );
        }
        catch ( const exception& ex )
        {
            failure( 500, ex, session );
        }
        catch ( ... )
        {
            auto cex = current_exception( );
            
            if ( cex not_eq nullptr )
            {
                try
                {
                    rethrow_exception( cex );
                }
                catch ( const exception& ex )
                {
                    failure( 500, ex, session );
                }
                catch ( ... )
                {
                    runtime_error re( "Internal Server Error" );
                    failure( 500, re, session );
                }
            }
            else
            {
                runtime_error re( "Internal Server Error" );
                failure( 500, re, session );
            }
        }
    }
}
