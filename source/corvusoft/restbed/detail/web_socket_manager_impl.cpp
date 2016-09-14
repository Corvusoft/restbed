/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <tuple>
#include <string>
#include <sstream>
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
#include <kashmir/uuid_gen.h>
#include <kashmir/system/devrand.h>

//System Namespaces
using std::get;
using std::tuple;
using std::string;
using std::function;
using std::to_string;
using std::shared_ptr;
using std::error_code;
using std::make_shared;
using std::stringstream;
using std::placeholders::_1;

//Project Namespaces
using restbed::detail::WebSocketManagerImpl;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        WebSocketManagerImpl::WebSocketManagerImpl( void ) : m_logger( nullptr ),
            m_sockets( )
        {
            return;
        }

        WebSocketManagerImpl::~WebSocketManagerImpl( void )
        {
            return;
        }

        shared_ptr< WebSocketMessage > WebSocketManagerImpl::parse( const Bytes& packet )
        {
            if ( packet.empty( ) )
            {
                return nullptr;
            }

            auto message = make_shared< WebSocketMessage >( );

            Byte byte = packet[ 0 ];
            message->set_final_frame_flag( byte & 128 );
            message->set_reserved_flags( byte & 64, byte & 32, byte & 16 );
            message->set_opcode( static_cast< WebSocketMessage::OpCode >( byte & 15 ) );

            const auto packet_length = packet.size( );
            if ( packet_length == 1 )
            {
                return message;
            }

            byte = packet[ 1 ];
            message->set_mask_flag( byte & 128 );
            message->set_length( byte & 127 );

            if ( packet_length == 2 )
            {
                return message;
            }

            size_t offset = 3;
            uint64_t length = message->get_length( );

            if ( length == 126 )
            {
                length  = packet[ offset++ ] << 8;
                length |= packet[ offset++ ]     ;

                message->set_extended_length( length );
            }
            else if ( length == 127 )
            {
                length |= packet[ offset++ ] << 24;
                length |= packet[ offset++ ] << 16;
                length |= packet[ offset++ ] <<  8;
                length  = packet[ offset++ ]      ;

                message->set_extended_length( length );
            }

            if ( message->get_mask_flag( ) == true )
            {
                uint32_t mask  = packet[ offset++ ] << 24;
                mask |= packet[ offset++ ] << 16;
                mask |= packet[ offset++ ] <<  8;
                mask |= packet[ offset   ]      ;

                message->set_mask( mask );
            }

            Bytes payload = packet;

            if ( message->get_mask_flag( ) == true )
            {
                auto masking_key = message->get_mask( );

                Byte mask[ 4 ] = { };
                mask[ 0 ] = ( masking_key >> 24 ) & 0xFF;
                mask[ 1 ] = ( masking_key >> 16 ) & 0xFF;
                mask[ 2 ] = ( masking_key >>  8 ) & 0xFF;
                mask[ 3 ] =   masking_key         & 0xFF;

                for ( size_t index = offset; index < payload.size( ); index++ )
                {
                    payload[ index ] ^= mask[ index % 4 ];
                }
            }

            message->set_data( payload );

            return message;
        }

        Bytes WebSocketManagerImpl::compose( const shared_ptr< WebSocketMessage >& message )
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
            if ( session == nullptr )
            {
                return nullptr;
            }

            kashmir::uuid_t uuid;
            kashmir::system::DevRand random;
            random >> uuid;
            stringstream stream;
            stream << uuid;
            const auto key = stream.str( );

            auto socket = make_shared< WebSocket >( );
            socket->set_key( key );
            socket->set_logger( m_logger ); //session->get_logger( );
            socket->set_manager( shared_from_this( ) );
            //session->get_socket( );
            socket->set_socket( session->m_pimpl->m_request->m_pimpl->m_socket );

            m_sockets.insert( make_pair( key, socket ) );

            return socket;
        }

        shared_ptr< WebSocket > WebSocketManagerImpl::read( const string& key )
        {
            auto socket = m_sockets.find( key );
            return ( socket not_eq m_sockets.end( ) ) ? socket->second : nullptr;
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
