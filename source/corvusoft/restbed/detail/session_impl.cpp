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
using std::runtime_error;
using std::placeholders::_1;

//Project Namespaces
using restbed::detail::SessionImpl;

//External Namespaces
using asio::buffer;
using asio::ip::tcp;
using asio::error_code;
using asio::async_write;
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
            m_socket( nullptr ),
            m_headers( ),
            m_router( nullptr )
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

        void SessionImpl::close( const int status, const string& body, const multimap< string, string >& headers )
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

        void SessionImpl::yield( const int status, const string& body, const multimap< string, string >& headers )
        {
            Response response;
            response.set_body( body );
            response.set_headers( headers );
            response.set_status_code( status );

            transmit( response, [ this ]( const asio::error_code& error, size_t bytes_transferred )
            {
                //if error -> log
                this->fetch( this->m_session, this->m_router );
            } );
        }

        void SessionImpl::fetch( const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            fetch( m_session, callback );
        }

        void SessionImpl::fetch( const size_t length, const function< void ( const shared_ptr< Session >&, const shared_ptr< Bytes >& ) >& callback )
        {
            if ( length > m_buffer->size( ) )
            {
                size_t size = length - m_buffer->size( );

                asio::async_read( *m_socket, *m_buffer, asio::transfer_at_least( size ), [ this, length, callback ]( const asio::error_code& error,
                                                                                                             std::size_t bytes_transferred )
                 {
                     //if error

                     const auto data_ptr = asio::buffer_cast< const Byte* >( this->m_buffer->data( ) );
                     const auto data = make_shared< Bytes >( data_ptr, data_ptr + length );
                     this->m_buffer->consume( length );

                     const auto request = this->m_session->m_pimpl->get_request( );
                     auto body = request->get_body( );

                     if ( body == nullptr )
                     {
                         request->m_pimpl->set_body( data );
                     }
                     else
                     {
                         body->insert( body->end( ), data->begin( ), data->end( ) );
                         request->m_pimpl->set_body( body );
                     }
                     
                     callback( m_session, data );
                 } );
            }
            else
            {
                const auto data_ptr = asio::buffer_cast< const Byte* >( m_buffer->data( ) );
                const auto data = make_shared< Bytes >( data_ptr, data_ptr + length );
                m_buffer->consume( length );

                const auto request = m_session->m_pimpl->get_request( );
                auto body = request->get_body( );

                if ( body == nullptr )
                {
                    request->m_pimpl->set_body( data );
                }
                else
                {
                    body->insert( body->end( ), data->begin( ), data->end( ) );
                    request->m_pimpl->set_body( body );
                }

                callback( m_session, data );
            }
        }

        void SessionImpl::fetch( const string& delimiter, const function< void ( const shared_ptr< Session >&, const shared_ptr< Bytes >& ) >& callback )
        {
            asio::async_read_until( *m_socket, *m_buffer, delimiter, [ this, callback ]( const asio::error_code& error,
                                                                                         std::size_t bytes_transferred ) //const bytes_trans..?
             {
                 //if error

                 const auto data_ptr = asio::buffer_cast< const Byte* >( this->m_buffer->data( ) );
                 const auto data = make_shared< Bytes >( data_ptr, data_ptr + bytes_transferred );
                 m_buffer->consume( bytes_transferred );

                 const auto request = this->m_session->m_pimpl->get_request( );
                 auto body = request->get_body( );

                 if ( body == nullptr )
                 {
                     request->m_pimpl->set_body( data );
                 }
                 else
                 {
                     body->insert( body->end( ), data->begin( ), data->end( ) );
                     request->m_pimpl->set_body( body );
                 }
                 
                 callback( m_session, data );
             } );
        }

        void SessionImpl::fetch( const shared_ptr< Session >& session,
                                 const function< void ( const shared_ptr< Session >& ) >& callback )
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

        const map< string, string > SessionImpl::parse_request_line( istream& stream )
        {
            smatch matches;
            static const regex pattern( "^(.*) (.*) (HTTP\\/[0-9]\\.[0-9])\\s*$" );
            string data = String::empty;
            getline( stream, data );

            if ( not regex_match( data, matches, pattern ) or matches.size( ) not_eq 4 )
            {
                throw runtime_error( "FAILED BAD REQUEST!" );
            }

            const string protocol = matches[ 3 ].str( );
            const auto delimiter = protocol.find_first_of( "/" );

            return map< string, string > {
                { "path", matches[ 2 ].str( ) },
                { "method", matches[ 1 ].str( ) },
                { "version", protocol.substr( delimiter + 1 ) },
                { "protocol", protocol.substr( 0, delimiter ) },
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
                    throw runtime_error( "FAILED BAD REQUEST!" );
                }

                headers.insert( make_pair( matches[ 1 ].str( ), matches[ 2 ].str( ) ) );
            }
            
            return headers;
        }

        void SessionImpl::parse_request( const asio::error_code& error,
                                         const std::shared_ptr< Session >& session,
                                         const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            if ( error )
            {
                throw runtime_error( "" ); //throw asio::system_error( code );
            }

            istream stream( m_buffer.get( ) );
            const auto items = parse_request_line( stream );
            const auto uri = Uri::parse( "http://localhost" + items.at( "path" ) );

            auto request = make_shared< Request >( );
            request->m_pimpl->set_path( uri.get_path( ) );
            request->m_pimpl->set_method( items.at( "method" ) );
            request->m_pimpl->set_version( stod( items.at( "version" ) ) );
            request->m_pimpl->set_headers( parse_request_headers( stream ) );
            request->m_pimpl->set_query_parameters( uri.get_query_parameters( ) );

            session->m_pimpl->set_request( request );

            callback( session );
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

            if ( response.get_status_message( ) == String::empty )
            {
                response.set_status_message( m_settings->get_status_message( response.get_status_code( ) ) );
            }

            const auto data = response.to_bytes( );
            asio::async_write( *m_socket, asio::buffer( data, data.size( ) ), callback );
        }
    }
}
