/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_DETAIL_WEB_SOCKET_IMPL_H
#define _RESTBED_DETAIL_WEB_SOCKET_IMPL_H 1

//System Includes
#include <memory>
#include <string>
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

#endif  /* _RESTBED_DETAIL_WEB_SOCKET_IMPL_H */
