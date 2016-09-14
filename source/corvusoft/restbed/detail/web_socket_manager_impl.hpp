/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_DETAIL_WEB_SOCKET_MANAGER_IMPL_H
#define _RESTBED_DETAIL_WEB_SOCKET_MANAGER_IMPL_H 1

//System Includes
#include <map>
#include <memory>
#include <functional>

//Project Includes
#include "corvusoft/restbed/byte.hpp"

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
    class WebSocketMessage;

    namespace detail
    {
        //Forward Declarations
        class SocketImpl;

        class WebSocketManagerImpl : public std::enable_shared_from_this< WebSocketManagerImpl >
        {
            public:
                //Friends

                //Definitions

                //Constructors
                WebSocketManagerImpl( void );

                virtual ~WebSocketManagerImpl( void );

                //Functionality
                std::shared_ptr< WebSocketMessage > parse( const Bytes& packet );

                Bytes compose( const std::shared_ptr< WebSocketMessage >& message );

                std::shared_ptr< WebSocket > create( const std::shared_ptr< Session >& session );

                std::shared_ptr< WebSocket > read( const std::string& key );

                std::shared_ptr< WebSocket > update( const std::shared_ptr< WebSocket >& socket );

                void destroy( const std::shared_ptr< WebSocket >& socket );

                //Getters
                std::shared_ptr< Logger > get_logger( void ) const;

                //Setters
                void set_logger( const std::shared_ptr< Logger >& value );

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

                std::map< std::string, std::shared_ptr< WebSocket > > m_sockets;
        };
    }
}

#endif  /* _RESTBED_DETAIL_WEB_SOCKET_MANAGER_IMPL_H */
