/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_SESSION_IMPL_H
#define _RESTBED_DETAIL_SESSION_IMPL_H 1

//System Includes
#include <map>
#include <string>
#include <memory>
#include <istream>
#include <functional>

//Project Includes
#include "corvusoft/restbed/byte.hpp"
#include "corvusoft/restbed/logger.hpp"

//External Includes
#include <asio.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Logger;
    class Session;
    class Request;
    class Response;
    class Resource;
    class Settings;
    class SessionManager;
    
    namespace detail
    {
        //Forward Declarations
        
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
                void fetch( const std::shared_ptr< Session > session, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
                
                void fetch_body( const std::size_t length, const std::shared_ptr< Session > session, const std::function< void ( const std::shared_ptr< Session >, const Bytes& ) >& callback ) const;
                
                void log( const Logger::Level level, const std::string& message ) const;
                
                void failure( const std::shared_ptr< Session > session, const int, const std::exception& ) const;
                
                void transmit( const Response& response, const std::function< void ( const asio::error_code&, std::size_t ) >& callback ) const;
                
                static const std::map< std::string, std::string > parse_request_line( std::istream& stream );
                
                static const std::multimap< std::string, std::string > parse_request_headers( std::istream& stream );
                
                void parse_request( const asio::error_code& error, const std::shared_ptr< Session > session, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
                
                //Getters
                
                //Setters
                
                //Operators
                SessionImpl& operator =( const SessionImpl& value ) = delete;
                
                //Properties
                std::string m_id;
                
                std::shared_ptr< Logger > m_logger;
                
                std::shared_ptr< const Request > m_request;
                
                std::shared_ptr< const Resource > m_resource;
                
                std::shared_ptr< const Settings > m_settings;
                
                std::shared_ptr< SessionManager > m_manager;
                
                std::multimap< std::string, std::string > m_headers;
                
                std::map< std::string, const ContextValue > m_context;
                
                std::function< void ( const std::shared_ptr< Session > ) > m_router;
                
                std::function< void ( const int, const std::exception&, const std::shared_ptr< Session > ) > m_error_handler;
                
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
        };
    }
}

#endif  /* _RESTBED_DETAIL_SESSION_IMPL_H */
