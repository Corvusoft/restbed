/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <ciso646>

//Project Includes
#include "corvusoft/restbed/web_socket.hpp"
#include "corvusoft/restbed/web_socket_message.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"
#include "corvusoft/restbed/detail/web_socket_impl.hpp"
#include "corvusoft/restbed/detail/web_socket_manager_impl.hpp"

//External Includes

//System Namespaces
using std::bind;
using std::string;
using std::shared_ptr;
using std::error_code;
using std::placeholders::_1;

//Project Namespaces
using restbed::detail::SocketImpl;
using restbed::detail::WebSocketImpl;
using restbed::detail::WebSocketManagerImpl;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        WebSocketImpl::WebSocketImpl( void )
        {
            return;
        }
        
        WebSocketImpl::~WebSocketImpl( void )
        {
            return;
        }
        
        void WebSocketImpl::log( const Logger::Level level, const string& message ) const
        {
            if ( m_logger not_eq nullptr )
            {
                try
                {
                    m_logger->log( level, "%s", message.data( ) );
                }
                catch ( ... )
                {
                    fprintf( stderr, "Failed to create log entry: %s", message.data( ) );
                }
            }
        }
        
        void WebSocketImpl::listen( const shared_ptr< WebSocket > socket )
        {
            m_socket->start_read( 2, bind( &WebSocketImpl::parse_flags, this, _1, socket ), [ this, socket ]( const error_code code )
            {
                if ( m_error_handler not_eq nullptr )
                {
                    m_error_handler( socket, code );
                }
            } );
        }
        
        void WebSocketImpl::parse_flags( const Bytes data, const shared_ptr< WebSocket > socket )
        {
            auto message = m_manager->parse( data );
            
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
            
            m_socket->start_read( length, bind( &WebSocketImpl::parse_length_and_mask, this, _1, data, socket ), [ this, socket ]( const error_code code )
            {
                if ( m_error_handler not_eq nullptr )
                {
                    m_error_handler( socket, code );
                }
            } );
        }
        
        void WebSocketImpl::parse_payload( const Bytes data, Bytes packet, const shared_ptr< WebSocket > socket )
        {
            packet.insert( packet.end( ), data.begin( ), data.end( ) );
            auto message = m_manager->parse( packet );
            
            if ( m_message_handler not_eq nullptr )
            {
                m_message_handler( socket, message );
            }
            
            listen( socket );
        }
        
        void WebSocketImpl::parse_length_and_mask( const Bytes data, Bytes packet, const shared_ptr< WebSocket > socket )
        {
            packet.insert( packet.end( ), data.begin( ), data.end( ) );
            auto message = m_manager->parse( packet );
            
            auto length = message->get_extended_length( );
            
            if ( length == 0 )
            {
                length = message->get_length( );
            }
            
            m_socket->start_read( length, bind( &WebSocketImpl::parse_payload, this, _1, packet, socket ), [ this, socket ]( const error_code code )
            {
                if ( m_error_handler not_eq nullptr )
                {
                    m_error_handler( socket, code );
                }
            } );
        }
    }
}
