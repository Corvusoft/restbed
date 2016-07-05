/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <memory>
#include <string>
#include <ciso646>
#include <cstdint>
#include <stdexcept>
#include <system_error>

//Project Includes
#include "corvusoft/restbed/uri.hpp"
#include "corvusoft/restbed/http.hpp"
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/response.hpp"
#include "corvusoft/restbed/settings.hpp"
#include "corvusoft/restbed/ssl_settings.hpp"
#include "corvusoft/restbed/detail/http_impl.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"
#include "corvusoft/restbed/detail/request_impl.hpp"
#include "corvusoft/restbed/detail/response_impl.hpp"

//External Includes
#include <asio/error.hpp>
#include <asio/buffer.hpp>

//System Namespaces
using std::bind;
using std::string;
using std::future;
using std::function;
using std::error_code;
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;
using std::invalid_argument;
using std::placeholders::_1;
using std::placeholders::_2;

//Project Namespaces
using restbed::detail::HttpImpl;
using restbed::detail::SocketImpl;
using restbed::detail::RequestImpl;
using restbed::detail::ResponseImpl;

//External Namespaces
using asio::buffer;

namespace restbed
{
    Bytes Http::to_bytes( const shared_ptr< Request >& value )
    {
        return HttpImpl::to_bytes( value );
    }
    
    Bytes Http::to_bytes( const shared_ptr< Response >& value )
    {
        auto data = String::format( "%s/%.1f %i %s\r\n",
                                    value->get_protocol( ).data( ),
                                    value->get_version( ),
                                    value->get_status_code( ),
                                    value->get_status_message( ).data( ) );
                                    
        auto headers = value->get_headers( );
        
        if ( not headers.empty( ) )
        {
            data += String::join( headers, ": ", "\r\n" ) + "\r\n";
        }
        
        data += "\r\n";
        
        auto bytes = String::to_bytes( data );
        auto body = value->get_body( );
        
        if ( not body.empty( ) )
        {
            bytes.insert( bytes.end( ), body.begin( ), body.end( ) );
        }
        
        return bytes;
    }
    
    void Http::close( const shared_ptr< Request >& value )
    {
        if ( value not_eq nullptr and value->m_pimpl->m_socket not_eq nullptr )
        {
            value->m_pimpl->m_socket->close( );
        }
    }
    
    bool Http::is_open( const shared_ptr< Request >& value )
    {
        if ( value not_eq nullptr and value->m_pimpl->m_socket not_eq nullptr )
        {
            return value->m_pimpl->m_socket->is_open( );
        }
        
        return false;
    }
    
    bool Http::is_closed( const shared_ptr< Request >& value )
    {
        return not is_open( value );
    }
    
    const shared_ptr< Response > Http::sync( const shared_ptr< Request > request, const shared_ptr< const Settings >& settings )
    {
        auto response = Http::async( request, nullptr, settings );
        response.wait( );
        
        return response.get( );
    }
    
    future< shared_ptr< Response > > Http::async( const shared_ptr< Request > request, const function< void ( const shared_ptr< Request >, const shared_ptr< Response > ) >& callback, const shared_ptr< const Settings >& settings )
    {
#ifndef BUILD_SSL
    
        if ( settings->get_ssl_settings( ) not_eq nullptr )
        {
            throw runtime_error( "Not Implemented! Rebuild Restbed with SSL funcationality enabled." );
        }
        
#endif
        bool finished = true;
        auto completion_handler = callback;
        
        if ( completion_handler == nullptr )
        {
            finished = false;
            completion_handler = [ &finished ]( const shared_ptr< Request >, const shared_ptr< Response > )
            {
                finished = true;
            };
        }
        
        HttpImpl::socket_setup( request, settings );
        
        request->m_pimpl->m_response = make_shared< Response >( );
        request->m_pimpl->m_response->m_pimpl->m_request = request.get( );
        
        if ( request->m_pimpl->m_socket not_eq nullptr and request->m_pimpl->m_socket->is_closed( ) )
        {
            request->m_pimpl->m_socket->connect( request->get_host( ), request->get_port( ), bind( HttpImpl::request_handler, _1, request, completion_handler ) );
        }
        else
        {
            request->m_pimpl->m_socket->write( HttpImpl::to_bytes( request ), bind( HttpImpl::write_handler, _1, _2, request, completion_handler ) );
        }
        
        if ( finished )
        {
            return std::async( std::launch::async, [ ]( const shared_ptr< Request > request ) -> shared_ptr< Response >
            {
                request->m_pimpl->m_io_service->run( );
                return request->m_pimpl->m_response;
            }, request );
        }
        else
        {
            do
            {
                request->m_pimpl->m_io_service->run_one( );
            }
            while ( finished == false and not request->m_pimpl->m_io_service->stopped( ) );
            
            std::promise< shared_ptr< Response > > result;
            result.set_value( request->m_pimpl->m_response );
            
            return result.get_future( );
        }
    }
    
    Bytes Http::fetch( const size_t length, const shared_ptr< Response >& response )
    {
        if ( response == nullptr )
        {
            throw invalid_argument( String::empty );
        }
        
        auto request = response->m_pimpl->m_request;
        
        if ( request == nullptr or request->m_pimpl->m_buffer == nullptr or request->m_pimpl->m_socket == nullptr )
        {
            throw invalid_argument( String::empty );
        }
        
        Bytes data = { };
        
        if ( length > request->m_pimpl->m_buffer->size( ) )
        {
            error_code error;
            const size_t size = length - request->m_pimpl->m_buffer->size( );
            
            request->m_pimpl->m_socket->read( request->m_pimpl->m_buffer, size, error );
            
            if ( error and error not_eq asio::error::eof )
            {
                throw runtime_error( String::format( "Socket receive failed: '%s'", error.message( ).data( ) ) );
            }
            
            const auto data_ptr = asio::buffer_cast< const Byte* >( request->m_pimpl->m_buffer->data( ) );
            data = Bytes( data_ptr, data_ptr + length );
            request->m_pimpl->m_buffer->consume( length );
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
    
    Bytes Http::fetch( const string& delimiter, const shared_ptr< Response >& response )
    {
        if ( response == nullptr )
        {
            throw invalid_argument( String::empty );
        }
        
        auto request = response->m_pimpl->m_request;
        
        if ( request == nullptr or request->m_pimpl->m_buffer == nullptr or request->m_pimpl->m_socket == nullptr )
        {
            throw invalid_argument( String::empty );
        }
        
        error_code error;
        const size_t size = request->m_pimpl->m_socket->read( request->m_pimpl->m_buffer, delimiter, error );
        
        if ( error )
        {
            throw runtime_error( String::format( "Socket receive failed: '%s'", error.message( ).data( ) ) );
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
