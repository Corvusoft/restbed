/*
 * Copyright 2013-2025, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <string>
#include <memory>
#include <functional>
#include <system_error>

//Project Includes
#include <corvusoft/restbed/web_socket_message.hpp>

//External Includes

//Windows DLL Exports
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#ifdef WIN_DLL_EXPORT
		#define WEB_SOCKET_EXPORT __declspec(dllexport)
	#else
		#define WEB_SOCKET_EXPORT __declspec(dllimport)
	#endif
#else
	#define WEB_SOCKET_EXPORT __attribute__((visibility ("default")))
#endif

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Logger;
    class Session;
    
    namespace detail
    {
        class SocketImpl;
        class WebSocketImpl;
        class WebSocketManagerImpl;
    }
    
    class WebSocket : public std::enable_shared_from_this< WebSocket >
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            WEB_SOCKET_EXPORT WebSocket( void );
            
            WEB_SOCKET_EXPORT ~WebSocket( void );
            
            //Functionality
            WEB_SOCKET_EXPORT bool is_open( void ) const;
            
            WEB_SOCKET_EXPORT bool is_closed( void ) const;
            
            WEB_SOCKET_EXPORT void close( void );
            
            WEB_SOCKET_EXPORT void send( const Bytes& body, const std::function< void ( const std::shared_ptr< WebSocket > ) > callback = nullptr );
            
            WEB_SOCKET_EXPORT void send( const std::string& body, const std::function< void ( const std::shared_ptr< WebSocket > ) > callback = nullptr );
            
            WEB_SOCKET_EXPORT void send( const WebSocketMessage::OpCode opcode, const std::function< void ( const std::shared_ptr< WebSocket > ) > callback = nullptr );
            
            WEB_SOCKET_EXPORT void send( const std::shared_ptr< WebSocketMessage > message, const std::function< void ( const std::shared_ptr< WebSocket > ) > callback = nullptr );
            
            //Getters
            WEB_SOCKET_EXPORT std::string get_key( void ) const;
            
            WEB_SOCKET_EXPORT std::shared_ptr< Logger > get_logger( void ) const;
            
            WEB_SOCKET_EXPORT std::shared_ptr< detail::SocketImpl > get_socket( void ) const;
            
            WEB_SOCKET_EXPORT std::function< void ( const std::shared_ptr< WebSocket > ) > get_open_handler( void ) const;
            
            WEB_SOCKET_EXPORT std::function< void ( const std::shared_ptr< WebSocket > ) > get_close_handler( void ) const;
            
            WEB_SOCKET_EXPORT std::function< void ( const std::shared_ptr< WebSocket >, const std::error_code ) > get_error_handler( void ) const;
            
            WEB_SOCKET_EXPORT std::function< void ( const std::shared_ptr< WebSocket >, const std::shared_ptr< WebSocketMessage > ) > get_message_handler( void ) const;
            
            //Setters
            WEB_SOCKET_EXPORT void set_key( const std::string& value );
            
            WEB_SOCKET_EXPORT void set_logger( const std::shared_ptr< Logger >& value );
            
            WEB_SOCKET_EXPORT void set_socket( const std::shared_ptr< detail::SocketImpl >& value );
            
            WEB_SOCKET_EXPORT void set_open_handler( const std::function< void ( const std::shared_ptr< WebSocket > ) >& value );
            
            WEB_SOCKET_EXPORT void set_close_handler( const std::function< void ( const std::shared_ptr< WebSocket > ) >& value );
            
            WEB_SOCKET_EXPORT void set_error_handler( const std::function< void ( const std::shared_ptr< WebSocket >, const std::error_code ) >& value );
            
            WEB_SOCKET_EXPORT void set_message_handler( const std::function< void ( const std::shared_ptr< WebSocket >, const std::shared_ptr< WebSocketMessage > ) >& value );
            
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
            friend Session;
            friend detail::WebSocketManagerImpl;
            
            //Definitions
            
            //Constructors
            WebSocket( const WebSocket& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            WebSocket& operator =( const WebSocket& value ) = delete;
            
            //Properties
            std::unique_ptr< detail::WebSocketImpl > m_pimpl;
    };
}
