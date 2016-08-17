/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_DETAIL_WEB_SOCKET_MESSAGE_IMPL_H
#define _RESTBED_DETAIL_WEB_SOCKET_MESSAGE_IMPL_H 1

//System Includes
#include <cstdint>

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/web_socket.hpp>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    namespace detail
    {
        //Forward Declarations
        
        struct WebSocketMessageImpl
        {
            Bytes m_data = { };
            
            std::uint32_t m_mask = 0;
            
            std::uint8_t m_length = 0;
            
            std::uint64_t m_extended_length = 0;
            
            bool m_mask_flag = false;
            
            bool m_final_frame_flag = true;
            
            bool m_reserved_flag_one = false;
            
            bool m_reserved_flag_two = false;
            
            bool m_reserved_flag_three = false;
            
            WebSocketMessage::OpCode m_opcode = WebSocketMessage::OpCode::BINARY_FRAME;
        };
    }
}

#endif  /* _RESTBED_DETAIL_WEB_SOCKET_MESSAGE_IMPL_H */
