/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <string>
#include <memory>
#include <istream>
#include <functional>
#include <system_error>

//Project Includes
#include "corvusoft/restbed/byte.hpp"

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Session;
    class Request;
    class Response;
    class Resource;
    class Settings;
    class SessionManager;
    
    namespace detail
    {
        //Forward Declarations
        class WebSocketManagerImpl;
        
        class SessionImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                SessionImpl( void );
                
                SessionImpl( const SessionImpl& original ) = delete;
                
                virtual ~SessionImpl( void );
                
                //Functionality
                void fetch_body( const std::size_t length, const std::shared_ptr< Session > session, const std::function< void ( const std::shared_ptr< Session >, const Bytes& ) >& callback ) const;
                
                void transmit( const Response& response, const std::function< void ( const std::error_code&, std::size_t ) >& callback ) const;
                
                //Getters
                const std::function< void ( const int, const std::exception&, const std::shared_ptr< Session > ) > get_error_handler( void );
                
                //Setters
                
                //Operators
                SessionImpl& operator =( const SessionImpl& value ) = delete;
                
                //Properties
                std::string m_id;
                
                std::shared_ptr< const Request > m_request;
                
                std::shared_ptr< const Resource > m_resource;
                
                std::shared_ptr< const Settings > m_settings;
                
                std::shared_ptr< SessionManager > m_manager;
                
                std::shared_ptr< WebSocketManagerImpl > m_web_socket_manager;
                
                std::multimap< std::string, std::string > m_headers;
                
                std::map< std::string, const ContextValue > m_context;
                
                std::function< void ( const int, const std::exception&, const std::shared_ptr< Session > ) > m_error_handler;
                
                std::function< void (  const std::error_code& error, std::size_t length, const std::shared_ptr< Session > ) > m_keep_alive_callback;
                
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
                
                //Properties
                bool m_error_handler_invoked;
        };
    }
}
