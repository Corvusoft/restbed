/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <map>
#include <regex>
#include <memory>
#include <string>
#include <vector>
#include <ciso646>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

//Project Includes
#include "corvusoft/restbed/uri.hpp"
#include "corvusoft/restbed/http.hpp"
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/response.hpp"
#include "corvusoft/restbed/ssl_settings.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"
#include "corvusoft/restbed/detail/request_impl.hpp"
#include "corvusoft/restbed/detail/response_impl.hpp"

//External Includes
#include <asio.hpp>

//System Namespaces
using std::stoi;
using std::stod;
using std::regex;
using std::string;
using std::smatch;
using std::istream;
using std::multimap;
using std::to_string;
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;

//Project Namespaces
using restbed::detail::SocketImpl;
using restbed::detail::RequestImpl;
using restbed::detail::ResponseImpl;

//External Namespaces
using asio::buffer;
using asio::ip::tcp;

namespace restbed
{
#ifdef BUILD_SSL
    shared_ptr< const Response > Http::sync( const shared_ptr< const Request >& request, const shared_ptr< const SSLSettings >& ssl_settings )
#else
    shared_ptr< const Response > Http::sync( const shared_ptr< const Request >& request )
#endif
    {
        asio::error_code error;
        
        if ( request->m_pimpl->m_io_service == nullptr )
        {
            request->m_pimpl->m_io_service = make_shared< asio::io_service >( );
        }
        
        if ( request->m_pimpl->m_socket == nullptr )
        {
#ifdef BUILD_SSL
        
            if ( ssl_settings not_eq nullptr or request->m_pimpl->m_is_https )
            {
                asio::ssl::context context( asio::ssl::context::sslv23 );
                shared_ptr< asio::ssl::stream< asio::ip::tcp::socket > > socket = nullptr;
                
                if ( ssl_settings not_eq nullptr )
                {
                    const auto pool = ssl_settings->get_certificate_authority_pool( );
                    
                    if ( pool.empty( ) )
                    {
                        context.set_default_verify_paths( );
                    }
                    else
                    {
                        context.add_verify_path( ssl_settings->get_certificate_authority_pool( ) );
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
            else
            {
#endif
                auto socket = make_shared< tcp::socket >( *request->m_pimpl->m_io_service );
                request->m_pimpl->m_socket = make_shared< SocketImpl >( socket );
#ifdef BUILD_SSL
            }
            
#endif
        }
        
        if ( request->m_pimpl->m_socket->is_closed( ) )
        {
            request->m_pimpl->m_socket->connect( request->get_host( ), request->get_port( ), error );
            
            if ( error )
            {
                throw runtime_error( String::format( "Socket connect failed: %s\n", error.message( ).data( ) ) );
            }
        }
        
        request->m_pimpl->m_socket->write( request->to_bytes( ), error );
        
        if ( error )
        {
            throw runtime_error( String::format( "Socket write failed: %s\n", error.message( ).data( ) ) );
        }
        
        request->m_pimpl->m_buffer = make_shared< asio::streambuf >( );
        istream response_stream( request->m_pimpl->m_buffer.get( ) );
        request->m_pimpl->m_socket->read( request->m_pimpl->m_buffer, "\r\n", error );
        
        if ( error )
        {
            throw runtime_error( String::format( "Socket receive failed: %s\n", error.message( ).data( ) ) );
        }
        
        string status_line = String::empty;
        getline( response_stream, status_line );
        
        smatch matches;
        static const regex status_line_pattern( "^([a-zA-Z]+)\\/(\\d*\\.?\\d*) (-?\\d+) (.+)\\r$" );
        
        if ( not regex_match( status_line, matches, status_line_pattern ) or matches.size( ) not_eq 5 )
        {
            throw runtime_error( String::format( "HTTP response status line malformed: '%s'\n", status_line.data( ) ) );
        }
        
        auto response = make_shared< Response >( );
        response->m_pimpl->m_request = request;
        request->m_pimpl->m_response = response;
        response->set_protocol( matches[ 1 ].str( ) );
        response->set_version( stod( matches[ 2 ].str( ) ) );
        response->set_status_code( stoi( matches[ 3 ].str( ) ) );
        response->set_status_message( matches[ 4 ].str( ) );
        
        request->m_pimpl->m_socket->read( request->m_pimpl->m_buffer, "\r\n\r\n", error );
        
        if ( error == asio::error::eof )
        {
            return response;
        }
        
        if ( error )
        {
            throw runtime_error( String::format( "Socket receive failed: '%s'\n", error.message( ).data( ) ) );
        }
        
        string header = String::empty;
        multimap< string, string > headers = { };
        
        while ( getline( response_stream, header ) and header not_eq "\r" )
        {
            static const regex header_pattern( "^([^:.]*): *(.*)\\s*$" );
            
            if ( not regex_match( header, matches, header_pattern ) or matches.size( ) not_eq 3 )
            {
                throw runtime_error( String::format( "HTTP header malformed: '%s'\n", header.data( ) ) );
            }
            
            headers.insert( make_pair( matches[ 1 ], matches[ 2 ] ) );
        }
        
        response->set_headers( headers );
        
        return response;
    }
    
    Bytes Http::fetch( const size_t length, const shared_ptr< const Response >& response )
    {
        Bytes data = { };
        auto request = response->get_request( );
        
        if ( length > request->m_pimpl->m_buffer->size( ) )
        {
            asio::error_code error;
            const size_t adjusted_length = length - request->m_pimpl->m_buffer->size( );
            
            const size_t size = request->m_pimpl->m_socket->read( request->m_pimpl->m_buffer, adjusted_length, error );
            
            if ( error and error not_eq asio::error::eof )
            {
                throw runtime_error( String::format( "Socket receive failed: '%s'\n", error.message( ).data( ) ) );
            }
            
            const auto data_ptr = asio::buffer_cast< const Byte* >( request->m_pimpl->m_buffer->data( ) );
            data = Bytes( data_ptr, data_ptr + size );
            request->m_pimpl->m_buffer->consume( size );
        }
        else
        {
            const auto data_ptr = asio::buffer_cast< const Byte* >( request->m_pimpl->m_buffer->data( ) );
            data = Bytes( data_ptr, data_ptr + length );
            request->m_pimpl->m_buffer->consume( length );
        }
        
        auto& body = response->m_pimpl->m_body;
        
        if ( body.empty( ) )
        {
            body = data;
        }
        else
        {
            body.insert( body.end( ), data.begin( ), data.end( ) );
        }
        
        return data;
    }
    
    Bytes Http::fetch( const string& delimiter, const shared_ptr< const Response >& response )
    {
        asio::error_code error;
        auto request = response->m_pimpl->m_request;
        const size_t size = request->m_pimpl->m_socket->read( request->m_pimpl->m_buffer, delimiter, error );
        
        if ( error )
        {
            throw runtime_error( String::format( "Socket receive failed: '%s'\n", error.message( ).data( ) ) );
        }
        
        const auto data_ptr = asio::buffer_cast< const Byte* >( request->m_pimpl->m_buffer->data( ) );
        const Bytes data( data_ptr, data_ptr + size );
        request->m_pimpl->m_buffer->consume( size );
        
        auto& body = response->m_pimpl->m_body;
        
        if ( body.empty( ) )
        {
            body = data;
        }
        else
        {
            body.insert( body.end( ), data.begin( ), data.end( ) );
        }
        
        return data;
    }
}
