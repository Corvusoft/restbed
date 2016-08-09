/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_DETAIL_WEB_SOCKET_IMPL_H
#define _RESTBED_DETAIL_WEB_SOCKET_IMPL_H 1

//System Includes
#include <memory>
#include <string>
#include <functional>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class WebSocketMessage;
    
    namespace detail
    {
        //Forward Declarations
        
        struct WebSocketImpl
        {
            std::string m_id = "";
            
            bool m_error_handler_invoked = false;
            
            std::shared_ptr< Logger > m_logger = nullptr;
            
            std::shared_ptr< SocketImpl > m_socket = nullptr;
            
            std::function< void ( const std::shared_ptr< WebSocket > ) > m_open_handler = nullptr;
            
            std::function< void ( const std::shared_ptr< WebSocket > ) > m_close_handler = nullptr;
            
            std::function< void ( const std::shared_ptr< WebSocket >, const std::error_code ) > m_error_handler = nullptr;
            
            std::function< void ( const std::shared_ptr< WebSocket >, const std::shared_ptr< WebSocketMessage > ) > m_message_handler = nullptr;
        };
    }
}

#endif  /* _RESTBED_DETAIL_WEB_SOCKET_IMPL_H */
