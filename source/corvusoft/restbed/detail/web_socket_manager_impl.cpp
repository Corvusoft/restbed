/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <tuple>
#include <ciso646>

//Project Includes
#include "corvusoft/restbed/logger.hpp"
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/web_socket.hpp"
#include "corvusoft/restbed/web_socket_message.hpp"
#include "corvusoft/restbed/detail/request_impl.hpp"
#include "corvusoft/restbed/detail/session_impl.hpp"
#include "corvusoft/restbed/detail/web_socket_impl.hpp"
#include "corvusoft/restbed/detail/web_socket_manager_impl.hpp"

//External Includes

//System Namespaces
using std::get;
using std::tuple;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using restbed::detail::WebSocketManagerImpl;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        WebSocketManagerImpl::WebSocketManagerImpl( const shared_ptr< Logger >& logger ) : m_logger( logger ),
            m_sockets( )
        {
            return;
        }
        
        WebSocketManagerImpl::~WebSocketManagerImpl( void )
        {
            return;
        }
        
        Bytes WebSocketManagerImpl::to_bytes( const shared_ptr< WebSocketMessage >& message )
        {
            Byte byte = 0;
            
            if ( message->get_final_frame_flag( ) )
            {
                byte |= 10000000;
            }
            
            auto reserved_flags = message->get_reserved_flags( );
            
            if ( get< 0 >( reserved_flags ) )
            {
                byte |= 01000000;
            }
            
            if ( get< 1 >( reserved_flags ) )
            {
                byte |= 00100000;
            }
            
            if ( get< 2 >( reserved_flags ) )
            {
                byte |= 00010000;
            }
            
            byte |= ( message->get_opcode( ) & 15 );
            
            Bytes frame = { };
            frame.push_back( byte );
            
            auto length = message->get_length( );
            auto mask_flag = message->get_mask_flag( );
            
            if ( length == 126 )
            {
                auto extended_length = message->get_extended_length( );
                frame.push_back( ( mask_flag ) ? 254 : 126 );
                frame.push_back( ( extended_length >> 8 ) & 0xFF );
                frame.push_back(   extended_length        & 0xFF );
            }
            else if ( length == 127 )
            {
                auto extended_length = message->get_extended_length( );
                frame.push_back( ( mask_flag ) ? 255 : 127 );
                frame.push_back( ( extended_length >> 56 ) & 0xFF );
                frame.push_back( ( extended_length >> 48 ) & 0xFF );
                frame.push_back( ( extended_length >> 40 ) & 0xFF );
                frame.push_back( ( extended_length >> 32 ) & 0xFF );
                frame.push_back( ( extended_length >> 24 ) & 0xFF );
                frame.push_back( ( extended_length >> 16 ) & 0xFF );
                frame.push_back( ( extended_length >>  8 ) & 0xFF );
                frame.push_back(   extended_length         & 0xFF );
            }
            else
            {
                frame.push_back( length );
            }
            
            if ( mask_flag )
            {
                auto masking_key = message->get_mask( );
                frame.push_back( masking_key );
                
                uint8_t mask[ 4 ] = { };
                mask[ 0 ] =   masking_key         & 0xFF;
                mask[ 1 ] = ( masking_key >>  8 ) & 0xFF;
                mask[ 2 ] = ( masking_key >> 16 ) & 0xFF;
                mask[ 3 ] = ( masking_key >> 24 ) & 0xFF;
                
                frame.push_back( mask[ 3 ] );
                frame.push_back( mask[ 2 ] );
                frame.push_back( mask[ 1 ] );
                frame.push_back( mask[ 0 ] );
                
                auto data = message->get_data( );
                
                for ( size_t index = 0; index < data.size( ); index++ )
                {
                    auto datum = data.at( index );
                    datum ^= mask[ index % 4 ];
                    frame.push_back( datum );
                }
            }
            else
            {
                auto data = message->get_data( );
                frame.insert( frame.end( ), data.begin( ), data.end( ) );
            }
            
            return frame;
        }
        
        shared_ptr< WebSocket > WebSocketManagerImpl::create( const std::shared_ptr< Session >& session )
        {
            auto socket = make_shared< WebSocket >( );
            socket->m_pimpl->m_logger = m_logger;
            socket->m_pimpl->m_manager = shared_from_this( );
            socket->m_pimpl->m_socket = session->m_pimpl->m_request->m_pimpl->m_socket;
            
            m_sockets.push_back( socket );
            
            return socket;
        }
    }
}
