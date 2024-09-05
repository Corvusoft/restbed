/*
 * Copyright 2013-2020, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <tuple>
#include <string>
#include <memory>
#include <cstdint>
#include <system_error>

//Project Includes
#include <corvusoft/restbed/byte.hpp>

//External Includes

//Windows DLL Exports
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#ifdef WIN_DLL_EXPORT
		#define WEB_SOCKET_MESSAGE_EXPORT __declspec(dllexport)
	#else
		#define WEB_SOCKET_MESSAGE_EXPORT __declspec(dllimport)
	#endif
#else
	#define WEB_SOCKET_MESSAGE_EXPORT __attribute__((visibility ("default")))
#endif

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
            WEB_SOCKET_MESSAGE_EXPORT WebSocketMessage( void );
            
            WEB_SOCKET_MESSAGE_EXPORT WebSocketMessage( const WebSocketMessage& original );
            
            WEB_SOCKET_MESSAGE_EXPORT WebSocketMessage( const OpCode code, const Bytes& data = { } );
            
            WEB_SOCKET_MESSAGE_EXPORT WebSocketMessage( const OpCode code, const std::string& data );
            
            WEB_SOCKET_MESSAGE_EXPORT WebSocketMessage( const OpCode code, const Bytes& data, const std::uint32_t mask );
            
            WEB_SOCKET_MESSAGE_EXPORT WebSocketMessage( const OpCode code, const std::string& data, const std::uint32_t mask );
            
            WEB_SOCKET_MESSAGE_EXPORT virtual ~WebSocketMessage( void );
            
            //Functionality
            WEB_SOCKET_MESSAGE_EXPORT Bytes to_bytes( void ) const;
            
            //Getters
            WEB_SOCKET_MESSAGE_EXPORT Bytes get_data( void ) const;
            
            WEB_SOCKET_MESSAGE_EXPORT OpCode get_opcode( void ) const;
            
            WEB_SOCKET_MESSAGE_EXPORT std::uint32_t get_mask( void ) const;
            
            WEB_SOCKET_MESSAGE_EXPORT std::uint8_t get_length( void ) const;
            
            WEB_SOCKET_MESSAGE_EXPORT std::uint64_t get_extended_length( void ) const;
            
            WEB_SOCKET_MESSAGE_EXPORT bool get_mask_flag( void ) const;
            
            WEB_SOCKET_MESSAGE_EXPORT bool get_final_frame_flag( void ) const;
            
            WEB_SOCKET_MESSAGE_EXPORT std::tuple< bool, bool, bool > get_reserved_flags( void ) const;
            
            //Setters
            WEB_SOCKET_MESSAGE_EXPORT void set_data( const Bytes& value );
            
            WEB_SOCKET_MESSAGE_EXPORT void set_data( const std::string& value );
            
            WEB_SOCKET_MESSAGE_EXPORT void set_opcode( const OpCode value );
            
            WEB_SOCKET_MESSAGE_EXPORT void set_mask( const std::uint32_t value );
            
            WEB_SOCKET_MESSAGE_EXPORT void set_length( const std::uint8_t value );
            
            WEB_SOCKET_MESSAGE_EXPORT void set_extended_length( const std::uint64_t value );
            
            WEB_SOCKET_MESSAGE_EXPORT void set_mask_flag( const bool value );
            
            WEB_SOCKET_MESSAGE_EXPORT void set_final_frame_flag( const bool value );
            
            WEB_SOCKET_MESSAGE_EXPORT void set_reserved_flags( const bool rsv1, const bool rsv2, const bool rsv3 );
            
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
