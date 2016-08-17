/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <ciso646>

//Project Includes
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/web_socket.hpp"
#include "corvusoft/restbed/web_socket_message.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"
#include "corvusoft/restbed/detail/web_socket_impl.hpp"
#include "corvusoft/restbed/detail/web_socket_manager_impl.hpp"

//External Includes

//System Namespaces
using std::bind;
using std::string;
using std::function;
using std::error_code;
using std::shared_ptr;
using std::make_shared;
using std::placeholders::_1;

//Project Namespaces
using restbed::detail::WebSocketImpl;

//External Namespaces

namespace restbed
{
    WebSocket::WebSocket( void ) : m_pimpl( new WebSocketImpl )
    {
        return;
    }
    
    WebSocket::~WebSocket( void )
    {
        try
        {
            close( );
        }
        catch ( ... )
        {
            //m_logger->log( failure );
        }
    }
    
    bool WebSocket::is_open( void ) const
    {
        return m_pimpl->m_socket not_eq nullptr and m_pimpl->m_socket->is_open( );
    }
    
    bool WebSocket::is_closed( void ) const
    {
        return m_pimpl->m_socket not_eq nullptr and m_pimpl->m_socket->is_closed( );
    }
    
    void WebSocket::close( void )
    {
        //m_pimpl->m_socket->close( );
        //m_web_socket_manager->destroy( m_key );
    }
    
    void WebSocket::send( const shared_ptr< WebSocketMessage > message, const function< void ( const shared_ptr< WebSocket > ) > callback )
    {
        const auto data = m_pimpl->m_manager->to_bytes( message );
        
        m_pimpl->m_socket->write( data, [ this, callback ]( const error_code & code, size_t )
        {
            if ( code )
            {
                if ( m_pimpl->m_error_handler not_eq nullptr  )
                {
                    m_pimpl->m_error_handler( shared_from_this( ), code );
                }
                
                return;
            }
            
            if ( callback not_eq nullptr )
            {
                callback( shared_from_this( ) );
            }
        } );
    }
    
    void WebSocket::set_open_handler( const function< void ( const shared_ptr< WebSocket > ) >& value )
    {
        m_pimpl->m_open_handler = value;
    }
    
    void WebSocket::set_close_handler( const function< void ( const shared_ptr< WebSocket > ) >& value )
    {
        m_pimpl->m_close_handler = bind( value, shared_from_this( ) );
    }
    
    void WebSocket::set_error_handler( const function< void ( const shared_ptr< WebSocket >, const error_code ) >& value )
    {
        m_pimpl->m_error_handler = [ value, this ]( const shared_ptr< WebSocket > socket, const error_code code )
        {
            if ( m_pimpl->m_error_handler_invoked == false )
            {
                value( socket, code );
            }
        };
    }
    
    void WebSocket::set_message_handler( const function< void ( const shared_ptr< WebSocket >, const shared_ptr< WebSocketMessage > ) >& value )
    {
        m_pimpl->m_message_handler = value;
        
        //auto message = WebSocketManager::parse_message( socket );
        
        auto socket = shared_from_this( );
        
        m_pimpl->m_socket->read( 2, bind( WebSocket::parse_flags, _1, socket ), [ socket ]( const error_code code )
        {
            socket->m_pimpl->m_error_handler( socket, code );
        } );
    }
    
    void WebSocket::parse_flags( const Bytes data, const shared_ptr< WebSocket > socket )
    {
        auto message = make_shared< WebSocketMessage >( );
        
        Byte byte = data[ 0 ];
        message->set_final_frame_flag( byte & 128 );
        message->set_reserved_flags( byte & 64, byte & 32, byte & 16 );
        message->set_opcode( static_cast< WebSocketMessage::OpCode >( byte & 15 ) );
        
        byte = data[ 1 ];
        message->set_mask_flag( byte & 128 );
        message->set_length( byte & 127 );
        
        auto length = message->get_length( );
        
        if ( length == 126 )
        {
            length = 2;
        }
        else if ( length == 127 )
        {
            length = 4;
        }
        else
        {
            length = 0;
        }
        
        if ( message->get_mask_flag( ) == true )
        {
            length += 4;
        }
        
        socket->m_pimpl->m_socket->read( length, bind( WebSocket::parse_length_and_mask, _1, socket, message ), [ socket ]( const error_code code )
        {
            //Place this logic on SocketImpl
            //SocketImpl::set_close_handler
            //SocketImpl::set_error_handler
            socket->m_pimpl->m_error_handler( socket, code );
        } );
    }
    
    void WebSocket::parse_payload( const Bytes data, const shared_ptr< WebSocket > socket, const shared_ptr< WebSocketMessage > message )
    {
        Bytes payload = data;
        
        if ( message->get_mask_flag( ) == true )
        {
            auto masking_key = message->get_mask( );
            
            Byte mask[ 4 ] = { };
            mask[ 0 ] = ( masking_key >> 24 ) & 0xFF;
            mask[ 1 ] = ( masking_key >> 16 ) & 0xFF;
            mask[ 2 ] = ( masking_key >>  8 ) & 0xFF;
            mask[ 3 ] =   masking_key         & 0xFF;
            
            for ( size_t index = 0; index < payload.size( ); index++ )
            {
                payload[ index ] ^= mask[ index % 4 ];
            }
        }
        
        message->set_data( payload );
        
        socket->m_pimpl->m_message_handler( socket, message );
    }
    
    void WebSocket::parse_length_and_mask( const Bytes data, const shared_ptr< WebSocket > socket, const shared_ptr< WebSocketMessage > message )
    {
        size_t offset = 0;
        uint64_t length = message->get_length( );
        
        if ( length == 126 )
        {
            length  = data[ offset++ ] << 8;
            length |= data[ offset++ ]     ;
            
            message->set_extended_length( length );
        }
        else if ( length == 127 )
        {
            length |= data[ offset++ ] << 24;
            length |= data[ offset++ ] << 16;
            length |= data[ offset++ ] <<  8;
            length  = data[ offset++ ]      ;
            
            message->set_extended_length( length );
        }
        
        if ( message->get_mask_flag( ) == true )
        {
            uint32_t mask  = data[ offset++ ] << 24;
            mask |= data[ offset++ ] << 16;
            mask |= data[ offset++ ] <<  8;
            mask |= data[ offset   ]      ;
            
            message->set_mask( mask );
        }
        
        socket->m_pimpl->m_socket->read( length, bind( WebSocket::parse_payload, _1, socket, message ), [ socket ]( const error_code code )
        {
            socket->m_pimpl->m_error_handler( socket, code );
        } );
    }
}
