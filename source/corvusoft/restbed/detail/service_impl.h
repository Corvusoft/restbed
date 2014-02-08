/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_DETAIL_SERVICE_IMPL_H
#define _RESTBED_DETAIL_SERVICE_IMPL_H 1

//System Includes
#include <list>
#include <thread>
#include <memory>
#include <string>
#include <utility>
#include <cstdarg>
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
    class Service;
    class Request;
    class Resource;
    class Settings;

    enum Mode : int;
    enum LogLevel : int;
    
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

                void stop( void );

                void publish( const Resource& value );

                void suppress( const Resource& value );

                virtual void error_handler( const Request& request, Response& response );

                virtual void log_handler( const LogLevel level, const std::string& format, ... );

                virtual void authentication_handler( const Request& request, Response& response );

                //Getters
                
                //Setters
                void set_error_handler( std::function< void ( const Request&, Response& ) > value );

                void set_authentication_handler( std::function< void ( const Request&, Response& ) > value );

                void set_log_handler( Service* service, void (Service::*value)( const LogLevel, const std::string&, ... ) );
                
                //Operators
                bool operator <( const ServiceImpl& rhs ) const;
                
                bool operator >( const ServiceImpl& rhs ) const;
                
                bool operator ==( const ServiceImpl& rhs ) const;
                
                bool operator !=( const ServiceImpl& rhs ) const;

                ServiceImpl& operator =( const ServiceImpl& rhs );

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

                std::string build_log_label( const LogLevel level ) const;

                Resource resolve_resource_route( const Request& request ) const;

                Response invoke_method_handler( const Request& request, const Resource& resource  ) const;

                static Response resource_not_found_handler( const Request& );

                //Getters
                
                //Setters
                
                //Operators

                //Properties
                Mode m_mode;

                uint16_t m_port;
            
                std::string m_root;

                int m_maximum_connections;

                std::list< Resource > m_resources;

                std::shared_ptr< std::thread > m_thread;

                std::shared_ptr< asio::io_service::work > m_work;

                std::shared_ptr< asio::io_service > m_io_service;

                std::shared_ptr< asio::ip::tcp::acceptor > m_acceptor;

                std::function< void ( const Request&, Response& ) > m_error_handler;

                std::function< void ( const Request&, Response& ) > m_authentication_handler;

                std::pair< Service*, void (Service::*)( const LogLevel, const std::string&, ... ) > m_log_handler;
        };
    }
}

#endif  /* _RESTBED_DETAIL_SERVICE_IMPL_H */
