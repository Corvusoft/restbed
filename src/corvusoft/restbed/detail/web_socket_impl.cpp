/*
 * Copyright 2013-2026, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <ciso646>
#include <system_error>

//Project Includes
#include "corvusoft/restbed/web_socket.hpp"
#include "corvusoft/restbed/web_socket_message.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"
#include "corvusoft/restbed/detail/web_socket_impl.hpp"
#include "corvusoft/restbed/detail/web_socket_manager_impl.hpp"

//External Includes

//System Namespaces
using std::bind;
using std::errc;
using std::string;
using std::shared_ptr;
using std::error_code;
using std::make_error_code;
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
            if ( m_socket == nullptr )
            {
                if ( m_error_handler not_eq nullptr )
                {
                    m_error_handler( socket, make_error_code( errc::not_connected ) );
                }
                
                return;
            }
            
            m_socket->start_read( 2, bind( &WebSocketImpl::parse_flags, this, _1, socket ), [ this, socket ]( const error_code code )
            {
                if ( m_error_handler not_eq nullptr )
                {
                    m_error_handler( socket, code );
                }
            } );
        }
        
        std::size_t WebSocketImpl::frame_header_remainder( const std::uint8_t length_indicator, const bool masked )
        {
            std::size_t length = 0;
            
            if ( length_indicator == 126 )
            {
                // 16-bit extended length.
                length = 2;
            }
            else if ( length_indicator == 127 )
            {
                // 64-bit extended length.
                length = 8;
            }
            
            if ( masked )
            {
                length += 4;
            }
            
            return length;
        }
        
        std::uint64_t WebSocketImpl::payload_length( const std::uint8_t length_indicator, const std::uint64_t extended_length )
        {
            return ( length_indicator < 126 ) ? length_indicator : extended_length;
        }
        
        bool WebSocketImpl::payload_length_within_limit( const std::uint8_t length_indicator, const std::uint64_t extended_length, const std::size_t max_frame_size )
        {
            if ( length_indicator == 127 and ( extended_length & 0x8000000000000000ULL ) not_eq 0 )
            {
                return false;
            }
            
            if ( max_frame_size not_eq 0 and payload_length( length_indicator, extended_length ) > max_frame_size )
            {
                return false;
            }
            
            return true;
        }
        
        void WebSocketImpl::parse_flags( const Bytes data, const shared_ptr< WebSocket > socket )
        {
            auto message = m_manager->parse( data );
            
            if ( message == nullptr )
            {
                if ( m_error_handler not_eq nullptr )
                {
                    m_error_handler( socket, make_error_code( errc::bad_message ) );
                }
                
                return;
            }
            
            const auto length = frame_header_remainder( message->get_length( ), message->get_mask_flag( ) );
            
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
            
            if ( message == nullptr )
            {
                if ( m_error_handler not_eq nullptr )
                {
                    m_error_handler( socket, make_error_code( errc::bad_message ) );
                }
                
                return;
            }
            
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
            
            if ( message == nullptr )
            {
                if ( m_error_handler not_eq nullptr )
                {
                    m_error_handler( socket, make_error_code( errc::bad_message ) );
                }
                
                return;
            }
            
            if ( not payload_length_within_limit( message->get_length( ), message->get_extended_length( ), m_manager->get_max_frame_size( ) ) )
            {
                if ( m_error_handler not_eq nullptr )
                {
                    m_error_handler( socket, make_error_code( errc::message_size ) );
                }
                
                return;
            }
            
            const auto length = payload_length( message->get_length( ), message->get_extended_length( ) );
            
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
