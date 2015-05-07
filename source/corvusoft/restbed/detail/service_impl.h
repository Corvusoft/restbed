/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_SERVICE_IMPL_H
#define _RESTBED_DETAIL_SERVICE_IMPL_H 1

//System Includes
#include <list>
#include <thread>
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
    class Service;
    class Request;
    class Resource;
    class Settings;
    
    enum Mode :
    int;

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
                
                ServiceImpl( const ServiceImpl& original );
                
                virtual ~ServiceImpl( void );
                
                //Functionality
                void start( void );
            
                void start( const Mode& value );
                
                void stop( void );
                
                void publish( const Resource& value );
                
                void suppress( const Resource& value );
                
                //Getters
                
                //Setters
                void set_log_handler( const std::shared_ptr< Logger >& value );
                
                void set_authentication_handler( std::function< void ( const Request&, Response& ) > value );
                
                void set_error_handler( std::function< void ( const int, const Request&, Response& ) > value );
                
                //Operators                
                ServiceImpl& operator =( const ServiceImpl& value );
                
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
                
                //Functionality
                void listen( void );
                
                void start_synchronous( void );
                
                void start_asynchronous( void );
                
                void router( std::shared_ptr< asio::ip::tcp::socket > socket, const asio::error_code& error );
                
                Resource resolve_resource_route( const Request& request ) const;
                
                Response invoke_method_handler( const Request& request, const Resource& resource  ) const;
                
                void log( const Logger::Level level, const std::string& message );
                
                void authentication_handler( const Request& request, Response& response );
                
                void error_handler( const int status_code, const Request& request, Response& response );

                void set_socket_timeout( std::shared_ptr< asio::ip::tcp::socket > socket );

                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                Mode m_mode;
                
                uint16_t m_port;
                
                std::string m_root;
                
                int m_maximum_connections;

                long long m_connection_timeout;

                std::list< Resource > m_resources;
                
                std::shared_ptr< Logger > m_log_handler;
                
                std::shared_ptr< std::thread > m_thread;
                
                std::shared_ptr< asio::io_service::work > m_work;
                
                std::shared_ptr< asio::io_service > m_io_service;
                
                std::shared_ptr< asio::ip::tcp::acceptor > m_acceptor;
                
                std::function< void ( const Request&, Response& ) > m_authentication_handler;
                
                std::function< void ( const int, const Request&, Response& ) > m_error_handler;
        };
    }
}

#endif  /* _RESTBED_DETAIL_SERVICE_IMPL_H */
