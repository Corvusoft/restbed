/*
 * Copyright 2013-2026, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <memory>
#include <string>
#include <cstddef>
#include <cstdint>
#include <functional>

//Project Includes
#include "corvusoft/restbed/byte.hpp"
#include "corvusoft/restbed/logger.hpp"

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class WebSocket;
    class WebSocketMessage;
    
    namespace detail
    {
        //Forward Declarations
        class SocketImpl;
        class WebSocketManagerImpl;
        
        class WebSocketImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                WebSocketImpl( void );
                
                virtual ~WebSocketImpl( void );
                
                //Functionality
                void log( const Logger::Level level, const std::string& message ) const;
                
                void listen( const std::shared_ptr< WebSocket > socket );
                
                static std::size_t frame_header_remainder( const std::uint8_t length_indicator, const bool masked );
                
                static std::uint64_t payload_length( const std::uint8_t length_indicator, const std::uint64_t extended_length );
                
                static bool payload_length_within_limit( const std::uint8_t length_indicator, const std::uint64_t extended_length, const std::size_t max_frame_size = 0 );
                
                void parse_flags( const Bytes data, const std::shared_ptr< WebSocket > socket );
                
                void parse_payload( const Bytes data, Bytes packet, const std::shared_ptr< WebSocket > socket );
                
                void parse_length_and_mask( const Bytes data, Bytes packet, const std::shared_ptr< WebSocket > socket );
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                std::string m_key = "";
                
                bool m_error_handler_invoked = false;
                
                std::shared_ptr< Logger > m_logger = nullptr;
                
                std::shared_ptr< SocketImpl > m_socket = nullptr;
                
                std::shared_ptr< WebSocketManagerImpl > m_manager = nullptr;
                
                std::function< void ( const std::shared_ptr< WebSocket > ) > m_open_handler = nullptr;
                
                std::function< void ( const std::shared_ptr< WebSocket > ) > m_close_handler = nullptr;
                
                std::function< void ( const std::shared_ptr< WebSocket >, const std::error_code ) > m_error_handler = nullptr;
                
                std::function< void ( const std::shared_ptr< WebSocket >, const std::shared_ptr< WebSocketMessage > ) > m_message_handler = nullptr;
                
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
                WebSocketImpl( const WebSocketImpl& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                WebSocketImpl& operator =( const WebSocketImpl& value ) = delete;
                
                //Properties
        };
    }
}
