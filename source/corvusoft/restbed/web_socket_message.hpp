/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_WEB_SOCKET_MESSAGE_H
#define _RESTBED_WEB_SOCKET_MESSAGE_H 1

//System Includes
#include <tuple>
#include <string>
#include <memory>
#include <cstdint>
#include <system_error>

//Project Includes
#include <corvusoft/restbed/byte.hpp>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    namespace detail
    {
        struct WebSocketMessageImpl;
    }
    
    class WebSocketMessage
    {
        public:
            //Friends
            
            //Definitions
            enum OpCode : uint8_t
            {
                CONTINUATION_FRAME     = 0x00,
                TEXT_FRAME             = 0x01,
                BINARY_FRAME           = 0x02,
                CONNECTION_CLOSE_FRAME = 0x08,
                PING_FRAME             = 0x09,
                PONG_FRAME             = 0x0A
            };
            
            //Constructors
            WebSocketMessage( void );
            
            WebSocketMessage( const WebSocketMessage& original );
            
            WebSocketMessage( const OpCode code, const Bytes& data = { } );
            
            WebSocketMessage( const OpCode code, const std::string& data );
            
            WebSocketMessage( const OpCode code, const Bytes& data, const std::uint32_t mask );
            
            WebSocketMessage( const OpCode code, const std::string& data, const std::uint32_t mask );
            
            virtual ~WebSocketMessage( void );
            
            //Functionality
            Bytes to_bytes( void ) const;
            
            //Getters
            Bytes get_data( void ) const;
            
            OpCode get_opcode( void ) const;
            
            std::uint32_t get_mask( void ) const;
            
            std::uint8_t get_length( void ) const;
            
            std::uint64_t get_extended_length( void ) const;
            
            bool get_mask_flag( void ) const;
            
            bool get_final_frame_flag( void ) const;
            
            std::tuple< bool, bool, bool > get_reserved_flags( void ) const;
            
            //Setters
            void set_data( const Bytes& value );
            
            void set_data( const std::string& value );
            
            void set_opcode( const OpCode value );
            
            void set_mask( const std::uint32_t value );
            
            void set_length( const std::uint8_t value );
            
            void set_extended_length( const std::uint64_t value );
            
            void set_mask_flag( const bool value );
            
            void set_final_frame_flag( const bool value );
            
            void set_reserved_flags( const bool rsv1, const bool rsv2, const bool rsv3 );
            
            //Operators
            
            //Properties
            
        protected:
            //Friends
            
            //Definitions
            
            //Constructors
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            
            //Properties
            
        private:
            //Friends
            
            //Definitions
            
            //Constructors
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            WebSocketMessage& operator =( const WebSocketMessage& value ) = delete;
            
            //Properties
            std::unique_ptr< detail::WebSocketMessageImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_WEB_SOCKET_MESSAGE_H */
