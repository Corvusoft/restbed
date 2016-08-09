/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_WEB_SOCKET_H
#define _RESTBED_WEB_SOCKET_H 1

//System Includes
#include <string>
#include <memory>
#include <functional>
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
    class Session;
    class WebSocketMessage;
    
    namespace detail
    {
        struct WebSocketImpl;
        class WebSocketManagerImpl;
    }
    
    class WebSocket : public std::enable_shared_from_this< WebSocket >
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            WebSocket( void );
            
            virtual ~WebSocket( void );
            
            //Functionality
            bool is_open( void ) const;
            
            bool is_closed( void ) const;
            
            void close( void );
            
            void send( const std::shared_ptr< WebSocketMessage > message, const std::function< void ( const std::shared_ptr< WebSocket > ) > callback = nullptr );
            
            //Getters
            //ContextValue get( const std::string& name );
            
            //Setters
            void set_open_handler( const std::function< void ( const std::shared_ptr< WebSocket > ) >& value );
            
            void set_close_handler( const std::function< void ( const std::shared_ptr< WebSocket > ) >& value );
            
            void set_error_handler( const std::function< void ( const std::shared_ptr< WebSocket >, const std::error_code ) >& value );
            
            void set_message_handler( const std::function< void ( const std::shared_ptr< WebSocket >, const std::shared_ptr< WebSocketMessage > ) >& value );
            
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
            static void parse_flags( const Bytes data, const std::shared_ptr< WebSocket > socket ); //hide me! and friends!
            
            static void parse_payload( const Bytes data, const std::shared_ptr< WebSocket > socket, const std::shared_ptr< WebSocketMessage > message );
            
            static void parse_length_and_mask( const Bytes data, const std::shared_ptr< WebSocket > socket, const std::shared_ptr< WebSocketMessage > message );
            
            //Getters
            
            //Setters
            
            //Operators
            WebSocket& operator =( const WebSocket& value ) = delete;
            
            //Properties
            std::unique_ptr< detail::WebSocketImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_WEB_SOCKET_H */
