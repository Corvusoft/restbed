/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_DETAIL_WEB_SOCKET_MANAGER_IMPL_H
#define _RESTBED_DETAIL_WEB_SOCKET_MANAGER_IMPL_H 1

//System Includes
#include <vector>
#include <memory>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Logger;
    class Session;
    class WebSocket;
    
    namespace detail
    {
        //Forward Declarations
        
        class WebSocketManagerImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                WebSocketManagerImpl( const std::shared_ptr< Logger >& logger = nullptr );
                
                virtual ~WebSocketManagerImpl( void );
                
                //Functionality
                std::shared_ptr< WebSocket > create( const std::shared_ptr< Session >& session );
                
                //std::shared_ptr< WebSocketMessage > create( );
                
                //Getters
                
                //Setters
                
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
                WebSocketManagerImpl( const WebSocketManagerImpl& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                WebSocketManagerImpl& operator =( const WebSocketManagerImpl& value ) = delete;
                
                //Properties
                std::shared_ptr< Logger > m_logger;
                
                std::vector< std::shared_ptr< WebSocket > > m_sockets;
        };
    }
}

#endif  /* _RESTBED_DETAIL_WEB_SOCKET_MANAGER_IMPL_H */
