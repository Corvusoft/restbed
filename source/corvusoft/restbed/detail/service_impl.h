/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_SERVICE_IMPL_H
#define _RESTBED_DETAIL_SERVICE_IMPL_H 1

//System Includes
#include <memory>
#include <string>
#include <functional>

//Project Includes

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
    class Service;
    class Resource;
    class Settings;
    class SessionManager;

    namespace detail
    {
        //Forward Declarations
        
        class ServiceImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                ServiceImpl( const Settings& settings );
                
                virtual ~ServiceImpl( void );
                
                //Functionality
                void stop( void );

                void start( void );
                
                void publish( const std::shared_ptr< Resource >& value );
                
                void suppress( const std::shared_ptr< Resource >& value );
                
                //Getters
                
                //Setters
                void set_log_handler( const std::shared_ptr< Logger >& value );
                
                void set_authentication_handler( const std::function< void ( const std::shared_ptr< Session >&,
                                                                             const std::function< void ( const std::shared_ptr< Session >& ) >& ) >& value );
                
                void set_error_handler( const std::function< void ( const int, const std::shared_ptr< Session >& ) >& value );
                
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
                ServiceImpl( const ServiceImpl& original ) = delete;
                
                //Functionality
                void listen( void );

                void resource_router( const std::shared_ptr< Session >& session );
                
                void create_session( const std::shared_ptr< asio::ip::tcp::socket >& socket, const asio::error_code& error );

                void log( const Logger::Level level, const std::string& message );
                
                void authenticate( const std::shared_ptr< Session >& session,
                                   const std::function< void ( const std::shared_ptr< Session >& ) >& callback );
                
                void error( const int status_code, const std::shared_ptr< Session >& session );

                // void set_socket_timeout( std::shared_ptr< asio::ip::tcp::socket > socket );

                //Getters
                
                //Setters
                
                //Operators
                ServiceImpl& operator =( const ServiceImpl& value ) = delete;
                
                //Properties
                uint16_t m_port;
                
                std::string m_root;
                
                // int m_maximum_connections;

                // long long m_connection_timeout;

                std::map< std::string, Resource > m_resources;
                
                std::shared_ptr< Logger > m_log_handler;
                
                std::shared_ptr< asio::io_service > m_io_service;

                std::shared_ptr< SessionManager > m_session_manager;
                
                std::shared_ptr< asio::ip::tcp::acceptor > m_acceptor;
                
                std::function< void ( const std::shared_ptr< Session >&, const std::function< void ( const std::shared_ptr< Session >& ) >& ) > m_authentication_handler;
                
                std::function< void ( const int, const std::shared_ptr< Session >& ) > m_error_handler;
        };
    }
}

#endif  /* _RESTBED_DETAIL_SERVICE_IMPL_H */
