/*
 * Copyright 2013-2026, Corvusoft Ltd, All Rights Reserved.
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
    
    WebSocketMessage::WebSocketMessage( const WebSocketMessage& original ) : m_pimpl( new WebSocketMessageImpl )
    {
        *m_pimpl = *original.m_pimpl;
    }
    
    WebSocketMessage::WebSocketMessage( const WebSocketMessage::OpCode code, const Bytes& data ) : WebSocketMessage( code, data, 0 )
    {
        return;
    }
    
    WebSocketMessage::WebSocketMessage( const WebSocketMessage::OpCode code, const string& data ) : WebSocketMessage( code, data, 0 )
    {
        return;
    }
    
    WebSocketMessage::WebSocketMessage( const WebSocketMessage::OpCode code, const Bytes& data, const uint32_t mask ) : m_pimpl( new WebSocketMessageImpl )
    {
        m_pimpl->m_data = data;
        m_pimpl->m_mask = mask;
        m_pimpl->m_opcode = code;
        m_pimpl->m_mask_flag = ( mask == 0 ) ? false : true;
        
        const auto length = data.size( );
        
        if ( length <= 125 )
        {
            m_pimpl->m_length = static_cast< uint8_t >( length );
        }
        else
        {
            m_pimpl->m_extended_length = length;
            m_pimpl->m_length = ( length <= 65535 ) ? 126 : 127;
        }
    }
    
    WebSocketMessage::WebSocketMessage( const WebSocketMessage::OpCode code, const string& data, const uint32_t mask ) : WebSocketMessage( code, String::to_bytes( data ), mask )
    {
        return;
    }
    
    WebSocketMessage::~WebSocketMessage( void )
    {
        return;
    }
    
    Bytes WebSocketMessage::to_bytes( void ) const
    {
        std::byte datum = ( m_pimpl->m_final_frame_flag ) ? std::byte{ 0x80 } :
                          std::byte{ 0x00 };
                          
        if ( m_pimpl->m_reserved_flag_one )
        {
            datum |= std::byte{ 0x40 };
        }
        
        if ( m_pimpl->m_reserved_flag_two )
        {
            datum |= std::byte{ 0x20 };
        }
        
        if ( m_pimpl->m_reserved_flag_three )
        {
            datum |= std::byte{ 0x10 };
        }
        
        datum |= static_cast< std::byte >( m_pimpl->m_opcode & 0x0F );
        
        Bytes frame = { datum };
        
        const auto mask_flag = m_pimpl->m_mask_flag;
        const auto payload_length = m_pimpl->m_data.size( );
        
        if ( payload_length > 65535 )
        {
            const auto extended_length = payload_length;
            frame.push_back( static_cast< std::byte >( ( mask_flag ) ? 255 : 127 ) );
            frame.push_back( static_cast< std::byte >( ( extended_length >> 56 ) & 0xFF ) );
            frame.push_back( static_cast< std::byte >( ( extended_length >> 48 ) & 0xFF ) );
            frame.push_back( static_cast< std::byte >( ( extended_length >> 40 ) & 0xFF ) );
            frame.push_back( static_cast< std::byte >( ( extended_length >> 32 ) & 0xFF ) );
            frame.push_back( static_cast< std::byte >( ( extended_length >> 24 ) & 0xFF ) );
            frame.push_back( static_cast< std::byte >( ( extended_length >> 16 ) & 0xFF ) );
            frame.push_back( static_cast< std::byte >( ( extended_length >>  8 ) & 0xFF ) );
            frame.push_back( static_cast< std::byte >(  extended_length         & 0xFF ) );
        }
        else if ( payload_length > 125 )
        {
            const auto extended_length = payload_length;
            frame.push_back( static_cast< std::byte >( ( mask_flag ) ? 254 : 126 ) );
            frame.push_back( static_cast< std::byte >( ( extended_length >> 8 ) & 0xFF ) );
            frame.push_back( static_cast< std::byte >(  extended_length        & 0xFF ) );
        }
        else
        {
            uint8_t code = static_cast< uint8_t >( payload_length );
            code = ( mask_flag ) ? ( code | 0x80 ) : ( code & ~0x80 );
            frame.push_back( std::byte{ code } );
        }
        
        if ( mask_flag )
        {
            const auto masking_key = m_pimpl->m_mask;
            const uint8_t mask[ 4 ] =
            {
                static_cast< uint8_t >( ( masking_key >> 24 ) & 0xFF ),
                static_cast< uint8_t >( ( masking_key >> 16 ) & 0xFF ),
                static_cast< uint8_t >( ( masking_key >>  8 ) & 0xFF ),
                static_cast< uint8_t >(   masking_key         & 0xFF )
            };
            
            frame.push_back( std::byte{ mask[ 0 ] } );
            frame.push_back( std::byte{ mask[ 1 ] } );
            frame.push_back( std::byte{ mask[ 2 ] } );
            frame.push_back( std::byte{ mask[ 3 ] } );
            
            for ( size_t index = 0; index < m_pimpl->m_data.size( ); index++ )
            {
                auto dat = m_pimpl->m_data[ index ];
                dat ^= std::byte{ mask[ index % 4 ] };
                frame.push_back( dat );
            }
        }
        else
        {
            frame.insert( frame.end( ), m_pimpl->m_data.begin( ), m_pimpl->m_data.end( ) );
        }
        
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
    
    uint8_t WebSocketMessage::get_length( void ) const
    {
        return m_pimpl->m_length;
    }
    
    uint64_t WebSocketMessage::get_extended_length( void ) const
    {
        return m_pimpl->m_extended_length;
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
        m_pimpl->m_mask_flag = ( value == 0 ) ? false : true;
    }
    
    void WebSocketMessage::set_length( const uint8_t value )
    {
        m_pimpl->m_length = value;
    }
    
    void WebSocketMessage::set_extended_length( const uint64_t value )
    {
        m_pimpl->m_extended_length = value;
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
