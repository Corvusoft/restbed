/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <map>
#include <regex>
#include <sstream>
#include <cstdlib>
#include <clocale>
#include <ciso646>

//Project Includes
#include "corvusoft/restbed/uri.hpp"
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/response.hpp"
#include "corvusoft/restbed/settings.hpp"
#include "corvusoft/restbed/ssl_settings.hpp"
#include "corvusoft/restbed/detail/http_impl.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"
#include "corvusoft/restbed/detail/request_impl.hpp"

//External Includes
#include <asio/error.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/buffer.hpp>
#include <asio/streambuf.hpp>

#ifdef BUILD_SSL
    #include <asio/ssl.hpp>
#endif

//System Namespaces
using std::free;
using std::bind;
using std::stod;
using std::regex;
using std::smatch;
using std::string;
using std::istream;
using std::function;
using std::multimap;
using std::setlocale;
using std::to_string;
using std::shared_ptr;
using std::error_code;
using std::make_shared;
using std::placeholders::_1;
using std::placeholders::_2;

//Project Namespaces

//External Namespaces
using asio::buffer;
using asio::ip::tcp;
using asio::streambuf;
using asio::io_service;
#ifdef BUILD_SSL
    using asio::ssl::stream;
#endif

namespace restbed
{
    namespace detail
    {
        Bytes HttpImpl::to_bytes( const shared_ptr< Request >& request )
        {
            auto path = request->get_path( );
            
            auto parameters = request->get_query_parameters( );
            
            if ( not parameters.empty( ) )
            {
                string query = String::empty;
                
                for ( const auto parameter : parameters )
                {
                    query += Uri::encode_parameter( parameter.first ) + "=" + Uri::encode_parameter( parameter.second ) + "&";
                }
                
                path += "?" + query.substr( 0, query.length( ) - 1 );
            }
            
            auto uri = request->m_pimpl->m_uri;
            
            if ( uri not_eq nullptr and not uri->get_fragment( ).empty( ) )
            {
                path += "#" + uri->get_fragment( );
            }
            
            auto protocol = request->get_protocol( );
            
            if ( String::uppercase( protocol ) == "HTTPS" )
            {
                protocol = "HTTP";
            }
            
            char* locale = nullptr;
            if (auto current_locale = setlocale( LC_NUMERIC, nullptr ) )
            {
                locale = strdup(current_locale);
                setlocale( LC_NUMERIC, "C" );
            }
            
            auto data = String::format( "%s %s %s/%.1f\r\n",
                                        request->get_method( ).data( ),
                                        path.data( ),
                                        protocol.data( ),
                                        request->get_version( ) );
            
            if (locale) {
                setlocale( LC_NUMERIC, locale );
                free( locale );
            }
            
            auto headers = request->get_headers( );
            
            if ( not headers.empty( ) )
            {
                data += String::join( headers, ": ", "\r\n" ) + "\r\n";
            }
            
            data += "\r\n";
            
            auto bytes = String::to_bytes( data );
            auto body = request->get_body( );
            
            if ( not body.empty( ) )
            {
                bytes.insert( bytes.end( ), body.begin( ), body.end( ) );
            }
            
            return bytes;
        }
        
        void HttpImpl::socket_setup( const shared_ptr< Request >& request, const shared_ptr< const Settings >& settings )
        {
            if ( request->m_pimpl->m_socket == nullptr )
            {
                if ( request->m_pimpl->m_io_service == nullptr )
                {
                    request->m_pimpl->m_io_service = make_shared< asio::io_service >( );
                }
                
#ifdef BUILD_SSL
                
                if ( String::uppercase( request->m_pimpl->m_protocol ) == "HTTPS" )
                {
                    ssl_socket_setup( request, settings->get_ssl_settings( ) );
                }
                else
                {
#endif
                    auto socket = make_shared< tcp::socket >( *request->m_pimpl->m_io_service );
                    request->m_pimpl->m_socket = make_shared< SocketImpl >( socket );
#ifdef BUILD_SSL
                }
                
#endif
            }
            
            request->m_pimpl->m_socket->set_timeout( settings->get_connection_timeout( ) );
        }
        
#ifdef BUILD_SSL
        void HttpImpl::ssl_socket_setup( const shared_ptr< Request >& request, const shared_ptr< const SSLSettings >& settings )
        {
            asio::ssl::context context( asio::ssl::context::sslv23 );
            shared_ptr< asio::ssl::stream< asio::ip::tcp::socket > > socket = nullptr;
            
            if ( settings not_eq nullptr )
            {
                const auto pool = settings->get_certificate_authority_pool( );
                
                if ( pool.empty( ) )
                {
                    context.set_default_verify_paths( );
                }
                else
                {
#ifdef _WIN32
                    context.load_verify_file(settings->get_certificate_authority_pool());
#else
                    context.add_verify_path( settings->get_certificate_authority_pool( ) );
#endif
                }
                
                socket = make_shared< asio::ssl::stream< asio::ip::tcp::socket > >( *request->m_pimpl->m_io_service, context );
                socket->set_verify_mode( asio::ssl::verify_peer | asio::ssl::verify_fail_if_no_peer_cert );
            }
            else
            {
                socket = make_shared< asio::ssl::stream< asio::ip::tcp::socket > >( *request->m_pimpl->m_io_service, context );
                socket->set_verify_mode( asio::ssl::verify_none );
            }
            
            socket->set_verify_callback( asio::ssl::rfc2818_verification( request->get_host( ) ) );
            request->m_pimpl->m_socket = make_shared< SocketImpl >( socket );
        }
#endif
        void HttpImpl::request_handler( const error_code& error, const shared_ptr< Request >& request, const function< void ( const shared_ptr< Request >, const shared_ptr< Response > ) >& callback   )
        {
            if ( error )
            {
                const auto body = String::format( "Failed to locate HTTP endpoint: %s", error.message( ).data( ) );
                return callback( request, create_error_response( request, body ) );
            }
            
            request->m_pimpl->m_socket->start_write( to_bytes( request ), bind( write_handler, _1, _2, request, callback ) );
        }
        
        void HttpImpl::write_handler( const error_code& error, const size_t, const shared_ptr< Request >& request, const function< void ( const shared_ptr< Request >, const shared_ptr< Response > ) >& callback )
        {
            if ( error )
            {
                const auto body = String::format( "Socket write failed: %s", error.message( ).data( ) );
                return callback( request, create_error_response( request, body ) );
            }
            
            request->m_pimpl->m_buffer = make_shared< asio::streambuf >( );
            request->m_pimpl->m_socket->start_read( request->m_pimpl->m_buffer, "\r\n", bind( read_status_handler, _1, _2, request, callback ) );
        }
        
        const shared_ptr< Response > HttpImpl::create_error_response( const shared_ptr< Request >& request, const string& message )
        {
            auto response = request->m_pimpl->m_response;
            response->set_protocol( request->get_protocol( ) );
            response->set_version( request->get_version( ) );
            response->set_status_code( 0 );
            response->set_status_message( "Error" );
            response->set_header( "Content-Type", "text/plain; utf-8" );
            response->set_header( "Content-Length", ::to_string( message.length( ) ) );
            response->set_body( message );
            
            return response;
        }
        
        void HttpImpl::read_status_handler( const error_code& error, const size_t, const shared_ptr< Request >& request, const function< void ( const shared_ptr< Request >, const shared_ptr< Response > ) >& callback )
        {
            if ( error )
            {
                const auto body = String::format( "Failed to read HTTP response status line: %s", error.message( ).data( ) );
                return callback( request, create_error_response( request, body ) );
            }
            
            istream response_stream( request->m_pimpl->m_buffer.get( ) );
            string status_line = String::empty;
            getline( response_stream, status_line );
            
            smatch matches;
            static const regex status_line_pattern( "^([a-zA-Z]+)\\/(\\d*\\.?\\d*) (-?\\d+) (.*)\\r$" );
            
            if ( not regex_match( status_line, matches, status_line_pattern ) or matches.size( ) not_eq 5 )
            {
                const auto body = String::format( "HTTP response status line malformed: '%s'", status_line.data( ) );
                return callback( request, create_error_response( request, body ) );
            }
            
            auto response = request->m_pimpl->m_response;
            response->set_protocol( matches[ 1 ].str( ) );
            response->set_version( stod( matches[ 2 ].str( ) ) );
            response->set_status_code( stoi( matches[ 3 ].str( ) ) );
            response->set_status_message( matches[ 4 ].str( ) );
            
            request->m_pimpl->m_socket->start_read( request->m_pimpl->m_buffer, "\r\n\r\n", bind( read_headers_handler, _1, _2, request, callback ) );
        }
        
        void HttpImpl::read_headers_handler( const error_code& error, const size_t, const shared_ptr< Request >& request, const function< void ( const shared_ptr< Request >, const shared_ptr< Response > ) >& callback )
        {
            if ( error == asio::error::eof )
            {
                return callback( request, request->m_pimpl->m_response );
            }
            
            if ( error )
            {
                const auto body = String::format( "Failed to read HTTP response status headers: '%s'", error.message( ).data( ) );
                return callback( request, create_error_response( request, body ) );
            }
            
            string header = String::empty;
            multimap< string, string > headers = { };
            istream response_stream( request->m_pimpl->m_buffer.get( ) );
            
            while ( getline( response_stream, header ) and header not_eq "\r" )
            {
                static const regex header_pattern( "^([^:.]*): *(.*)\\s*$" );
                smatch matches;
                
                if ( not regex_match( header, matches, header_pattern ) or matches.size( ) not_eq 3 )
                {
                    const auto body = String::format( "Malformed HTTP response header: '%s'", header.data( ) );
                    return callback( request, create_error_response( request, body ) );
                }
                
                headers.insert( make_pair( matches[ 1 ], matches[ 2 ] ) );
            }
            
            auto response = request->m_pimpl->m_response;
            response->set_headers( headers );
            
            callback( request, response );
        }
    }
}
