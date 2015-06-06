/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <regex>
#include <utility>
#include <stdexcept>

//Project Includes
#include "corvusoft/restbed/session.h"
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/response.h"
#include "corvusoft/restbed/resource.h"
#include "corvusoft/restbed/settings.h"
#include "corvusoft/restbed/detail/request_impl.h"
#include "corvusoft/restbed/detail/session_impl.h"
#include "corvusoft/restbed/detail/resource_impl.h"

//External Includes
#include <corvusoft/framework/uri>
#include <corvusoft/framework/string>

//System Namespaces
using std::map;
using std::regex;
using std::smatch;
using std::string;
using std::getline;
using std::istream;
using std::function;
using std::multimap;
using std::make_pair;
using std::ssub_match;
using std::shared_ptr;
using std::make_shared;
using std::regex_match;
using std::exception;
using std::to_string;
using std::runtime_error;
using std::placeholders::_1;
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
using asio::ip::tcp;
using asio::error_code;
using asio::async_write;
using asio::steady_timer;
using asio::async_read_until;
using framework::Uri;
using framework::Byte;
using framework::Bytes;
using framework::String;

namespace restbed
{
    namespace detail
    {
        SessionImpl::SessionImpl( void ) : m_is_closed( false ),
            m_id( String::empty ),
            m_origin( String::empty ),
            m_destination( String::empty ),
            m_session( nullptr ),
            m_request( nullptr ),
            m_resource( nullptr ),
            m_settings( nullptr ),
            m_buffer( nullptr ),
            m_timer( nullptr ),
            m_socket( nullptr ),
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

        bool SessionImpl::is_open( void ) const
        {
            return not is_closed( );
        }

        bool SessionImpl::is_closed( void ) const
        {
            return ( m_is_closed or m_socket == nullptr or not m_socket->is_open( ) );
        }

        void SessionImpl::purge( const std::function< void ( const std::shared_ptr< Session >& ) >& callback )
        {
            close( );
            //m_session_manager->purge( m_session, callback );
        }

        void SessionImpl::close( void )
        {
            m_is_closed = true;
            m_socket->close( );
        }

        void SessionImpl::close( const string& body )
        {
            asio::async_write( *m_socket,
                               asio::buffer( body.data( ), body.size( ) ),
                               [ this ]( const asio::error_code& error, size_t bytes_transferred )
                               {
                                   //if error
                                   this->close( );
                               } );
        }

        void SessionImpl::close( const int status, const string& body, const multimap< string, string >& headers )
        {
            close( status, String::to_bytes( body ), headers );
        }

        void SessionImpl::close( const int status, const Bytes& body, const multimap< string, string >& headers )
        {
            m_is_closed = true;

            Response response;
            response.set_body( body );
            response.set_headers( headers );
            response.set_status_code( status );

            auto socket = m_socket;
            transmit( response, [ socket ]( const asio::error_code& error, size_t bytes_transferred )
            {
                //if error -> log
                socket->close( );
            } );
        }

        void SessionImpl::yield( const int status, const string& body, const multimap< string, string >& headers, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            Response response;
            response.set_body( body );
            response.set_headers( headers );
            response.set_status_code( status );

            transmit( response, [ this, callback ]( const asio::error_code& error, size_t bytes_transferred )
            {
                //if error -> log
                if ( callback == nullptr )
                {
                    this->fetch( this->m_session, this->m_router );
                }
                else
                {
                    callback( this->m_session );
                }
            } );
        }

        void SessionImpl::yield( const string& body, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            asio::async_write( *m_socket,
                              asio::buffer( body.data( ), body.size( ) ),
                              [ this, callback ]( const asio::error_code& error, size_t bytes_transferred )
                              {
                                  //if error
                                  callback( this->m_session );
                              } );
        }

        void SessionImpl::fetch( const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            fetch( m_session, callback );
        }

        void SessionImpl::fetch( const size_t length, const function< void ( const shared_ptr< Session >&, const Bytes& ) >& callback )
        {
            if ( length > m_buffer->size( ) )
            {
                size_t size = length - m_buffer->size( );

                asio::async_read( *m_socket, *m_buffer, asio::transfer_at_least( size ), [ this, length, callback ]( const asio::error_code& error,
                                                                                                             std::size_t bytes_transferred )
                 {
                     //if error

                     const auto data_ptr = asio::buffer_cast< const Byte* >( this->m_buffer->data( ) );
                     const auto data = Bytes( data_ptr, data_ptr + length );
                     this->m_buffer->consume( length );

                     const auto request = this->m_session->m_pimpl->get_request( );
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
                     
                     callback( m_session, data );
                 } );
            }
            else
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

                callback( m_session, data );
            }
        }

        void SessionImpl::fetch( const string& delimiter, const function< void ( const shared_ptr< Session >&, const Bytes& ) >& callback )
        {
            asio::async_read_until( *m_socket, *m_buffer, delimiter, [ this, callback ]( const asio::error_code& error,
                                                                                         std::size_t bytes_transferred ) //const bytes_trans..?
             {
                 //if error

                 const auto data_ptr = asio::buffer_cast< const Byte* >( this->m_buffer->data( ) );
                 const auto data = Bytes( data_ptr, data_ptr + bytes_transferred );
                 m_buffer->consume( bytes_transferred );

                 const auto request = this->m_session->m_pimpl->get_request( );
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
                 
                 callback( m_session, data );
             } );
        }

        void SessionImpl::fetch( const shared_ptr< Session >& session, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            if ( m_router == nullptr and m_session == nullptr )
            {
                m_session = session;
                m_router = callback;
            }

            m_buffer = make_shared< asio::streambuf >( );

            asio::async_read_until( *m_socket,
                                    *m_buffer,
                                    "\r\n\r\n",
                                    bind( &SessionImpl::parse_request, this, _1, m_session, callback ) );
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
            auto session = m_session;

            m_timer = make_shared< asio::steady_timer >( m_socket->get_io_service( ) );
            m_timer->expires_from_now( delay );
            m_timer->async_wait( [ callback, session ]( const error_code& error )
            {
               //if error
               callback( session );
            } );
        }

        const string& SessionImpl::get_id( void ) const
        {
            return m_id;
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

        void SessionImpl::set_id( const string& value )
        {
            m_id = value;
        }

        void SessionImpl::set_origin( const string& value )
        {
            m_origin = value;
        }

        void SessionImpl::set_destination( const string& value )
        {
            m_destination = value;
        }

        const string& SessionImpl::get_origin( void ) const
        {
            return m_origin;
        }

        const string& SessionImpl::get_destination( void ) const
        {
            return m_destination;
        }

        void SessionImpl::set_request( const shared_ptr< Request >& value )
        {
            m_request = value;
        }

        void SessionImpl::set_resource( const std::shared_ptr< Resource >& value )
        {
            m_resource = value;
        }

        void SessionImpl::set_settings( const shared_ptr< Settings >& value )
        {
            m_settings = value;
        }

        void SessionImpl::set_socket( const std::shared_ptr< tcp::socket >& value )
        {
            m_socket = value;
        }

        void SessionImpl::set_header( const string& name, const string& value )
        {
            m_headers.insert( make_pair( name, value ) );
        }

        void SessionImpl::set_headers( const multimap< string, string >& values )
        {
            m_headers = values;
        }

        void SessionImpl::set_error_handler( const function< void ( const int, const exception&, const shared_ptr< Session >& ) >& value )
        {
            m_error_handler = value;
        }

        const map< string, string > SessionImpl::parse_request_line( istream& stream )
        {
            smatch matches;
            static const regex pattern( "^([0-9a-zA-Z]*) ([a-zA-Z0-9\\/\\?:@\\-\\._~!$&'\\(\\)\\*\\+\\,;\\=#%]*) (HTTP\\/[0-9]\\.[0-9])\\s*$" );
            string data = String::empty;
            getline( stream, data );

            if ( not regex_match( data, matches, pattern ) or matches.size( ) not_eq 4 )
            {
                throw runtime_error( "Your client has issued a malformed or illegal request status line. That’s all we know." );
            }

            const string protocol = matches[ 3 ].str( );
            const auto delimiter = protocol.find_first_of( "/" );

            return map< string, string > {
                { "path", matches[ 2 ].str( ) },
                { "method", matches[ 1 ].str( ) },
                { "version", protocol.substr( delimiter + 1 ) },
                { "protocol", protocol.substr( 0, delimiter ) }
            };
        }

        const multimap< string, string > SessionImpl::parse_request_headers( istream& stream )
        {
            smatch matches;
            string data = String::empty;
            multimap< string, string > headers;
            static const regex pattern( "^(.*): *(.*)\\s*$" );

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

        void SessionImpl::parse_request( const asio::error_code& error, const std::shared_ptr< Session >& session, const function< void ( const shared_ptr< Session >& ) >& callback )
        try
        {
            if ( error )
            {
                throw runtime_error( "" ); //throw asio::system_error( code );
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
        catch ( const runtime_error& re )
        {
            if ( m_error_handler not_eq nullptr )
            {
                m_error_handler( 400, re, session );
            }
            else
            {
                string body = re.what( );
                session->close( 400, body, { { "Content-Type", "text/plain" }, { "Content-Length", ::to_string( body.length( ) ) } } );
            }
        }
        catch ( const exception& ex )
        {
            if ( m_error_handler not_eq nullptr )
            {
                m_error_handler( 500, ex, session );
            }
            else
            {
                string body = ex.what( );
                session->close( 500, body, { { "Content-Type", "text/plain" }, { "Content-Length", ::to_string( body.length( ) ) } } );
            }
        }
        catch ( ... )
        {
            if ( m_error_handler not_eq nullptr )
            {
                runtime_error re( "An unknown error has occured." );
                m_error_handler( 500, re, session );
            }
            else
            {
                session->close( 500, "An unknown error has occured.", { { "Content-Type", "text/plain" }, { "Content-Length", "29" } } );
            }
        }

        void SessionImpl::transmit( Response& response, const function< void ( const asio::error_code&, size_t ) >& callback ) const
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
            response.set_headers( headers );

            if ( response.get_status_message( ) == String::empty )
            {
                response.set_status_message( m_settings->get_status_message( response.get_status_code( ) ) );
            }

            const auto data = response.to_bytes( );
            asio::async_write( *m_socket, asio::buffer( data.data( ), data.size( ) ), callback );
        }
    }
}
