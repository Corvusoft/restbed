/*
 * Copyright 2013-2026, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <tuple>
#include <mutex>
#include <string>
#include <random>
#include <ciso646>
#include <system_error>

//Project Includes
#include "corvusoft/restbed/logger.hpp"
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/web_socket.hpp"
#include "corvusoft/restbed/web_socket_message.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"
#include "corvusoft/restbed/detail/request_impl.hpp"
#include "corvusoft/restbed/detail/session_impl.hpp"
#include "corvusoft/restbed/detail/web_socket_impl.hpp"
#include "corvusoft/restbed/detail/web_socket_manager_impl.hpp"

//External Includes

//System Namespaces
using std::get;
using std::tuple;
using std::string;
using std::mt19937;
using std::function;
using std::to_string;
using std::shared_ptr;
using std::error_code;
using std::make_shared;
using std::random_device;
using std::placeholders::_1;
using std::uniform_int_distribution;

//Project Namespaces
using restbed::detail::WebSocketManagerImpl;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        WebSocketManagerImpl::WebSocketManagerImpl( void ) : m_logger( nullptr ),
            m_socket_lock( ),
            m_sockets( )
        {
            return;
        }
        
        shared_ptr< WebSocketMessage > WebSocketManagerImpl::parse( const Bytes& packet )
        {
            if ( packet.empty( ) )
            {
                return nullptr;
            }
            
            uint8_t datum = static_cast<uint8_t>( packet[ 0 ] );
            
            auto message = make_shared< WebSocketMessage >( );
            message->set_final_frame_flag( ( datum & 0x80 ) ? true : false );
            message->set_reserved_flags(   ( datum & 0x40 ) ? true : false,
                                           ( datum & 0x20 ) ? true : false,
                                           ( datum & 0x10 ) ? true : false );
            message->set_opcode( static_cast< WebSocketMessage::OpCode >( datum & 0x0F ) );
            
            const auto packet_length = packet.size( );
            
            if ( packet_length == 1 )
            {
                return message;
            }
            
            datum = static_cast<uint8_t>( packet[ 1 ] );
            message->set_mask_flag( ( datum & 0x80 ) ? true : false );
            message->set_length( datum & 0x7F );
            
            if ( packet_length == 2 )
            {
                return message;
            }
            
            size_t offset = 2;
            uint64_t length = message->get_length( );
            
            if ( length == 126 )
            {
                // 2-byte extended length. packet_length and offset are unsigned,
                // so compare additively to avoid wrap-around on short frames.
                if ( packet_length < offset + 2 )
                {
                    return nullptr;
                }
                
                length  = static_cast<uint64_t>( static_cast<uint8_t>( packet[ offset++ ] ) ) << 8;
                length |= static_cast<uint64_t>( static_cast<uint8_t>( packet[ offset++ ] ) )     ;
                
                message->set_extended_length( length );
            }
            else if ( length == 127 )
            {
                // 8-byte extended length.
                if ( packet_length < offset + 8 )
                {
                    return nullptr;
                }
                
                length  = static_cast<uint64_t>( static_cast<uint8_t>( packet[ offset++ ] ) ) << 56;
                length |= static_cast<uint64_t>( static_cast<uint8_t>( packet[ offset++ ] ) ) << 48;
                length |= static_cast<uint64_t>( static_cast<uint8_t>( packet[ offset++ ] ) ) << 40;
                length |= static_cast<uint64_t>( static_cast<uint8_t>( packet[ offset++ ] ) ) << 32;
                length |= static_cast<uint64_t>( static_cast<uint8_t>( packet[ offset++ ] ) ) << 24;
                length |= static_cast<uint64_t>( static_cast<uint8_t>( packet[ offset++ ] ) ) << 16;
                length |= static_cast<uint64_t>( static_cast<uint8_t>( packet[ offset++ ] ) ) <<  8;
                length |= static_cast<uint64_t>( static_cast<uint8_t>( packet[ offset++ ] ) )      ;
                
                message->set_extended_length( length );
            }
            
            if ( message->get_mask_flag( ) == true )
            {
                // 4-byte masking key.
                if ( packet_length < offset + 4 )
                {
                    return nullptr;
                }
                
                uint32_t mask = static_cast<uint32_t>( static_cast<uint8_t>( packet[ offset++ ] ) ) << 24;
                mask |= static_cast<uint32_t>( static_cast<uint8_t>( packet[ offset++ ] ) )         << 16;
                mask |= static_cast<uint32_t>( static_cast<uint8_t>( packet[ offset++ ] ) )         <<  8;
                mask |= static_cast<uint32_t>( static_cast<uint8_t>( packet[ offset++ ] ) )              ;
                
                message->set_mask( mask );
            }
            
            Bytes payload( packet.begin( ) + offset, packet.end( ) );
            
            if ( message->get_mask_flag( ) == true )
            {
                auto masking_key = message->get_mask( );
                
                uint8_t mask[ 4 ] = { };
                mask[ 0 ] = ( masking_key >> 24 ) & 0xFF;
                mask[ 1 ] = ( masking_key >> 16 ) & 0xFF;
                mask[ 2 ] = ( masking_key >>  8 ) & 0xFF;
                mask[ 3 ] =   masking_key         & 0xFF;
                
                for ( size_t index = 0; index < payload.size( ); index++ )
                {
                    payload[ index ] ^= std::byte{mask[ index % 4 ]};
                }
            }
            
            message->set_data( payload );
            
            return message;
        }
        
        Bytes WebSocketManagerImpl::compose( const shared_ptr< WebSocketMessage >& message )
        {
            return message->to_bytes( );
        }
        
        shared_ptr< WebSocket > WebSocketManagerImpl::create( const std::shared_ptr< Session >& session )
        {
            if ( session == nullptr )
            {
                return nullptr;
            }
            
            static auto& charset = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
            thread_local static mt19937 generator{ random_device{ }( ) };
            thread_local static uniform_int_distribution< string::size_type > pick( 0, sizeof( charset ) - 2 );
            
            string key;
            auto length = 16;
            key.reserve( length );
            
            while ( length-- )
            {
                key += charset[ pick( generator ) ];
            }
            
            auto socket = make_shared< WebSocket >( );
            socket->set_key( key );
            socket->set_logger( m_logger );
            socket->set_socket( session->m_pimpl->m_request->m_pimpl->m_socket );
            socket->m_pimpl->m_manager = shared_from_this( );
            
            {
                std::lock_guard< std::mutex > guard( m_socket_lock );
                
                std::erase_if( m_sockets, []( const auto & entry )
                {
                    return entry.second.expired( );
                } );
                
                m_sockets.insert( make_pair( key, std::weak_ptr< WebSocket >( socket ) ) );
            }
            
            return socket;
        }
        
        shared_ptr< WebSocket > WebSocketManagerImpl::read( const string& key )
        {
            std::lock_guard< std::mutex > guard( m_socket_lock );
            auto socket = m_sockets.find( key );
            return ( socket not_eq m_sockets.end( ) ) ? socket->second.lock( ) : nullptr;
        }
        
        shared_ptr< WebSocket > WebSocketManagerImpl::update( const shared_ptr< WebSocket >& socket )
        {
            return socket;
        }
        
        void WebSocketManagerImpl::destroy( const shared_ptr< WebSocket >& socket )
        {
            if ( socket == nullptr )
            {
                return;
            }
            
            std::lock_guard< std::mutex > guard( m_socket_lock );
            m_sockets.erase( socket->get_key( ) );
        }
        
        shared_ptr< Logger > WebSocketManagerImpl::get_logger( void ) const
        {
            return m_logger;
        }
        
        void WebSocketManagerImpl::set_logger( const shared_ptr< Logger >& value )
        {
            m_logger = value;
        }
    }
}
