/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/web_socket_message.hpp"
#include "corvusoft/restbed/detail/web_socket_message_impl.hpp"

//External Includes

//System Namespaces
using std::tuple;
using std::string;
using std::uint8_t;
using std::uint32_t;
using std::uint64_t;
using std::shared_ptr;
using std::make_tuple;

//Project Namespaces
using restbed::detail::WebSocketMessageImpl;

//External Namespaces

namespace restbed
{
    WebSocketMessage::WebSocketMessage( void ) : m_pimpl( new WebSocketMessageImpl )
    {
        return;
    }
    
    WebSocketMessage::WebSocketMessage( const WebSocketMessage::OpCode code, const Bytes& data ) : m_pimpl( new WebSocketMessageImpl )
    {
        m_pimpl->m_data = data;
        m_pimpl->m_opcode = code;
        
        const auto length = data.size( );
        
        if ( length <= 125 )
        {
            m_pimpl->m_payload_length = length;
        }
        else
        {
            m_pimpl->m_extended_payload_length = length;
            m_pimpl->m_payload_length = ( length < 65535 ) ? 126 : 127;
        }
    }
    
    WebSocketMessage::WebSocketMessage( const WebSocketMessage::OpCode code, const string& data ) : m_pimpl( new WebSocketMessageImpl )
    {
        m_pimpl->m_data = String::to_bytes( data );
        m_pimpl->m_opcode = code;
        
        const auto length = data.size( );
        
        if ( length <= 125 )
        {
            m_pimpl->m_payload_length = length;
        }
        else
        {
            m_pimpl->m_extended_payload_length = length;
            m_pimpl->m_payload_length = ( length < 65535 ) ? 126 : 127;
        }
    }
    
    WebSocketMessage::WebSocketMessage( const WebSocketMessage::OpCode code, const Bytes& data, const uint32_t mask ) : m_pimpl( new WebSocketMessageImpl )
    {
        m_pimpl->m_data = data;
        m_pimpl->m_mask = mask;
        m_pimpl->m_opcode = code;
        
        const auto length = data.size( );
        
        if ( length <= 125 )
        {
            m_pimpl->m_payload_length = length;
        }
        else
        {
            m_pimpl->m_extended_payload_length = length;
            m_pimpl->m_payload_length = ( length < 65535 ) ? 126 : 127;
        }
    }
    
    WebSocketMessage::WebSocketMessage( const WebSocketMessage::OpCode code, const string& data, const uint32_t mask ) : m_pimpl( new WebSocketMessageImpl )
    {
        m_pimpl->m_data = String::to_bytes( data );
        m_pimpl->m_mask = mask;
        m_pimpl->m_opcode = code;
        
        const auto length = data.size( );
        
        if ( length <= 125 )
        {
            m_pimpl->m_payload_length = length;
        }
        else
        {
            m_pimpl->m_extended_payload_length = length;
            m_pimpl->m_payload_length = ( length < 65535 ) ? 126 : 127;
        }
    }
    
    WebSocketMessage::~WebSocketMessage( void )
    {
        return;
    }
    
    Bytes WebSocketMessage::to_bytes( void ) const
    {
        Byte byte = 0;
        
        if ( m_pimpl->m_final_frame_flag )
        {
            byte |= 10000000;
        }
        
        if ( m_pimpl->m_reserved_flag_one )
        {
            byte |= 01000000;
        }
        
        if ( m_pimpl->m_reserved_flag_two )
        {
            byte |= 00100000;
        }
        
        if ( m_pimpl->m_reserved_flag_three )
        {
            byte |= 00010000;
        }
        
        byte |= ( m_pimpl->m_opcode & 15 );
        
        Bytes frame = { };
        frame.push_back( byte );
        
        if ( m_pimpl->m_payload_length == 126 )
        {
            frame.push_back( ( m_pimpl->m_mask_flag ) ? 254 : 126 );
            frame.push_back( ( m_pimpl->m_extended_payload_length >> 8 ) & 0xFF );
            frame.push_back(   m_pimpl->m_extended_payload_length        & 0xFF );
        }
        else if ( m_pimpl->m_payload_length == 127 )
        {
            frame.push_back( ( m_pimpl->m_mask_flag ) ? 255 : 127 );
            frame.push_back( ( m_pimpl->m_extended_payload_length >> 56 ) & 0xFF );
            frame.push_back( ( m_pimpl->m_extended_payload_length >> 48 ) & 0xFF );
            frame.push_back( ( m_pimpl->m_extended_payload_length >> 40 ) & 0xFF );
            frame.push_back( ( m_pimpl->m_extended_payload_length >> 32 ) & 0xFF );
            frame.push_back( ( m_pimpl->m_extended_payload_length >> 24 ) & 0xFF );
            frame.push_back( ( m_pimpl->m_extended_payload_length >> 16 ) & 0xFF );
            frame.push_back( ( m_pimpl->m_extended_payload_length >>  8 ) & 0xFF );
            frame.push_back(   m_pimpl->m_extended_payload_length         & 0xFF );
        }
        else
        {
            frame.push_back( m_pimpl->m_payload_length ); //add mask value
        }
        
        // if ( m_pimpl->m_mask_flag )
        // {
        //     uint8_t mask[ 4 ] = { };
        //     mask[ 0 ] =   m_pimpl->m_mask         & 0xFF;
        //     mask[ 1 ] = ( m_pimpl->m_mask >>  8 ) & 0xFF;
        //     mask[ 2 ] = ( m_pimpl->m_mask >> 16 ) & 0xFF;
        //     mask[ 3 ] = ( m_pimpl->m_mask >> 24 ) & 0xFF;
        //
        //     frame.push_back( mask[ 3 ] );
        //     frame.push_back( mask[ 2 ] );
        //     frame.push_back( mask[ 1 ] );
        //     frame.push_back( mask[ 0 ] );
        //
        //     for ( size_t index = 0; index < m_pimpl->m_data.size( ); index++ )
        //     {
        //         auto datum = m_pimpl->m_data.at( index );
        //         datum ^= mask[ index % 4 ];
        //         frame.push_back( datum );
        //     }
        // }
        // else
        // {
        frame.insert( frame.end( ), m_pimpl->m_data.begin( ), m_pimpl->m_data.end( ) );
        //}
        
        return frame;
    }
    
    Bytes WebSocketMessage::get_data( void ) const
    {
        return m_pimpl->m_data;
    }
    
    WebSocketMessage::OpCode WebSocketMessage::get_opcode( void ) const
    {
        return m_pimpl->m_opcode;
    }
    
    uint32_t WebSocketMessage::get_mask( void ) const
    {
        return m_pimpl->m_mask;
    }
    
    uint8_t WebSocketMessage::get_payload_length( void ) const
    {
        return m_pimpl->m_payload_length;
    }
    
    uint64_t WebSocketMessage::get_extended_payload_length( void ) const
    {
        return m_pimpl->m_extended_payload_length;
    }
    
    bool WebSocketMessage::get_mask_flag( void ) const
    {
        return m_pimpl->m_mask_flag;
    }
    
    bool WebSocketMessage::get_final_frame_flag( void ) const
    {
        return m_pimpl->m_final_frame_flag;
    }
    
    tuple< bool, bool, bool > WebSocketMessage::get_reserved_flags( void ) const
    {
        return make_tuple( m_pimpl->m_reserved_flag_one, m_pimpl->m_reserved_flag_two, m_pimpl->m_reserved_flag_three );
    }
    
    void WebSocketMessage::set_data( const Bytes& value )
    {
        m_pimpl->m_data = value;
    }
    
    void WebSocketMessage::set_data( const string& value )
    {
        m_pimpl->m_data = String::to_bytes( value );
    }
    
    void WebSocketMessage::set_opcode( const WebSocketMessage::OpCode value )
    {
        m_pimpl->m_opcode = value;
    }
    
    void WebSocketMessage::set_mask( const uint32_t value )
    {
        m_pimpl->m_mask = value;
    }
    
    void WebSocketMessage::set_payload_length( const uint8_t value )
    {
        m_pimpl->m_payload_length = value;
    }
    
    void WebSocketMessage::set_extended_payload_length( const uint64_t value )
    {
        m_pimpl->m_extended_payload_length = value;
    }
    
    void WebSocketMessage::set_mask_flag( const bool value )
    {
        m_pimpl->m_mask_flag = value;
    }
    
    void WebSocketMessage::set_final_frame_flag( const bool value )
    {
        m_pimpl->m_final_frame_flag = value;
    }
    
    void WebSocketMessage::set_reserved_flags( const bool rsv1, const bool rsv2, const bool rsv3 )
    {
        m_pimpl->m_reserved_flag_one = rsv1;
        m_pimpl->m_reserved_flag_two = rsv2;
        m_pimpl->m_reserved_flag_three = rsv3;
    }
}
