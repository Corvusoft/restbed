/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <regex>
#include <utility>
#include <stdexcept>
#include <iostream> //debug

//Project Includes
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/session.h"
#include "corvusoft/restbed/resource.h"
#include "corvusoft/restbed/status_message.h"
#include "corvusoft/restbed/detail/request_impl.h"
#include "corvusoft/restbed/detail/session_impl.h"

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
using framework::String;

namespace restbed
{
    namespace detail
    {
        SessionImpl::SessionImpl( void ) : m_is_closed( false ),
            m_id( String::empty ),
            m_session( nullptr ),
            m_request( nullptr ),
            m_resource( nullptr ),
            m_buffer( nullptr ),
            m_socket( nullptr ),
            m_callback( nullptr ),
            m_default_headers( )
        {
            return;
        }

        SessionImpl::~SessionImpl( void )
        {
            fprintf( stderr, "DESTORYING SESSION\n\n\n" );
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

        void SessionImpl::close( void )
        {
            m_is_closed = true;
            m_socket->close( );
        }

        void SessionImpl::close( const int status, const string& body, const multimap< string, string >& headers )
        {
            m_is_closed = true;

            const auto message = ( status_message.count( status ) ) ? status_message.at( status ) : status_message.at( 999 );

            auto data = String::format( "HTTP/1.1 %i %s\r\n", status, message.data( ) );

            auto response_headers = m_default_headers;

            if ( m_resource not_eq nullptr )
            {
                const auto resource_headers = m_resource->get_default_headers( );
                response_headers.insert( resource_headers.begin( ), resource_headers.end( ) );
            }

            response_headers.insert( headers.begin( ), headers.end( ) );

            for ( auto header : response_headers )
            {
                data += String::format( "%s: %s\r\n", header.first.data( ), header.second.data( ) );
            }

            data += "\r\n" + body;

            auto socket = m_socket;
            asio::async_write( *socket,
                              asio::buffer( data, data.length( ) ),
                              [ socket ]( const asio::error_code& error, std::size_t bytes_transferred )
                              {
                                  //if error -> log
                                  socket->close( );
                              } );
        }

        void SessionImpl::yield( const int status, const string& body, const multimap< string, string >& headers )
        {
            const auto message = ( status_message.count( status ) ) ? status_message.at( status ) : status_message.at( 999 );

            auto data = String::format( "HTTP/1.1 %i %s\r\n", status, message.data( ) );

            auto response_headers = m_default_headers;

            if ( m_resource not_eq nullptr )
            {
                const auto resource_headers = m_resource->get_default_headers( );
                response_headers.insert( resource_headers.begin( ), resource_headers.end( ) );
            }

            response_headers.insert( headers.begin( ), headers.end( ) );

            for ( auto header : response_headers )
            {
                data += String::format( "%s: %s\r\n", header.first.data( ), header.second.data( ) );
            }

            data += "\r\n" + body;

            asio::async_write( *m_socket,
                              asio::buffer( data, data.length( ) ),
                              [ this ]( const asio::error_code& error, std::size_t bytes_transferred )
                              {
                                  //if error -> log
                                  this->fetch( this->m_session, this->m_callback );
                              } );
        }

        void SessionImpl::fetch( const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            fetch( m_session, callback );
        }

        void SessionImpl::fetch( const shared_ptr< Session >& session,
                                 const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            if ( m_callback == nullptr and m_session == nullptr )
            {
                m_session = session;
                m_callback = callback;
            }

            m_buffer = make_shared< asio::streambuf >( ); //pass as argument!

            asio::async_read_until( *m_socket,
                                    *m_buffer,
                                    "\r\n\r\n",
                                    bind( &SessionImpl::parse_request, this, _1, session, callback ) );
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

        void SessionImpl::set_id( const string& value )
        {
            m_id = value;
        }

        void SessionImpl::set_request( const shared_ptr< Request >& value )
        {
            m_request = value;
        }

        void SessionImpl::set_resource( const std::shared_ptr< Resource >& value )
        {
            m_resource = value;
        }

        void SessionImpl::set_socket( const std::shared_ptr< tcp::socket >& value )
        {
            m_socket = value;
        }

        void SessionImpl::set_default_headers( const multimap< string, string >& values )
        {
            m_default_headers = values;
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
    }
}
