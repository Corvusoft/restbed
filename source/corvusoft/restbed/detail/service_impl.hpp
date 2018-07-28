/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <set>
#include <map>
#include <chrono>
#include <future>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
#include <functional>
#include <system_error>

//Project Includes

//External Includes
#include <asio/ip/tcp.hpp>
#include <asio/signal_set.hpp>
#include <asio/io_service.hpp>

#ifdef BUILD_SSL
    #include <asio/ssl.hpp>
#endif

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Uri;
    class Rule;
    class Logger;
    class Session;
    class Resource;
    class Settings;
    class SessionManager;
    class SSLSettings;
    
    namespace detail
    {
        //Forward Declarations
        class WebSocketManagerImpl;
        
        class ServiceImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                ServiceImpl( void );
                
                virtual ~ServiceImpl( void );
                
                //Functionality
                void http_start( void );
                
                void http_listen( void ) const;
#ifdef BUILD_SSL
                void https_start( void );
                
                void https_listen( void ) const;
                
                void create_ssl_session( const std::shared_ptr< asio::ssl::stream< asio::ip::tcp::socket > >& socket, const std::error_code& error ) const;
#endif
                void setup_signal_handler( );
                
                void signal_handler( const std::error_code& error, const int signal_number ) const;
                
                std::string sanitise_path( const std::string& path ) const;
                
                void not_found( const std::shared_ptr< Session > session ) const;
                
                bool has_unique_paths( const std::set< std::string >& paths ) const;
                
                void log( const Logger::Level level, const std::string& message ) const;
                
                void method_not_allowed( const std::shared_ptr< Session > session ) const;
                
                void method_not_implemented( const std::shared_ptr< Session > session ) const;
                
                void failed_filter_validation( const std::shared_ptr< Session > session ) const;
                
                void router( const std::shared_ptr< Session > session ) const;
                
                void create_session( const std::shared_ptr< asio::ip::tcp::socket >& socket, const std::error_code& error ) const;
                
                void extract_path_parameters( const std::string& sanitised_path, const std::shared_ptr< const Request >& request ) const;
                
                std::function< void ( const std::shared_ptr< Session > ) > find_method_handler( const std::shared_ptr< Session > session ) const;
                
                void authenticate( const std::shared_ptr< Session > session ) const;
                
                bool resource_router( const std::shared_ptr< Session > session, const std::pair< std::string, std::shared_ptr< const Resource > >& route ) const;
                
                static void default_error_handler( const int status, const std::exception& error, const std::shared_ptr< Session > session );
                
                static void discard_request( std::istream& stream );
                
                static const std::map< std::string, std::string > parse_request_line( std::istream& stream );
                
                static const std::multimap< std::string, std::string > parse_request_headers( std::istream& stream );
                
                void parse_request( const std::error_code& error, std::size_t length, const std::shared_ptr< Session > session ) const;
                
                //Getters
                const std::shared_ptr< const Uri > get_http_uri( void ) const;
                
                const std::shared_ptr< const Uri > get_https_uri( void ) const;
                
                const std::function< void ( const int, const std::exception&, const std::shared_ptr< Session > ) > get_error_handler( const std::shared_ptr< Session >& session ) const;
                
                //Setters
                
                //Operators
                
                //Properties
                std::chrono::steady_clock::time_point m_uptime;
                
                std::shared_ptr< Logger > m_logger;
                
                std::set< std::string > m_supported_methods;
                
                std::shared_ptr< const Settings > m_settings;
                
                std::shared_ptr< asio::io_service > m_io_service;
                
                std::shared_ptr< asio::signal_set > m_signal_set;
                
                std::shared_ptr< SessionManager > m_session_manager;
                
                std::shared_ptr< WebSocketManagerImpl > m_web_socket_manager;
                
                std::vector< std::shared_ptr< Rule > > m_rules;
                
                std::unique_ptr< std::future<void > > m_workers_stopped;
#ifdef BUILD_SSL
                std::shared_ptr< const SSLSettings > m_ssl_settings;
                
                std::shared_ptr< asio::ssl::context > m_ssl_context;
                
                std::shared_ptr< asio::ip::tcp::acceptor > m_ssl_acceptor;
#endif
                std::shared_ptr< asio::ip::tcp::acceptor > m_acceptor;
                
                std::map< std::string, std::string > m_resource_paths;
                
                std::map< std::string, std::shared_ptr< const Resource > > m_resource_routes;
                
                std::function< void ( void ) > m_ready_handler;
                
                std::map< int, std::function< void ( const int ) > > m_signal_handlers;
                
                std::function< void ( const std::shared_ptr< Session > ) > m_not_found_handler;
                
                std::function< void ( const std::shared_ptr< Session > ) > m_method_not_allowed_handler;
                
                std::function< void ( const std::shared_ptr< Session > ) > m_method_not_implemented_handler;
                
                std::function< void ( const std::shared_ptr< Session > ) > m_failed_filter_validation_handler;
                
                std::function< void ( const int, const std::exception&, const std::shared_ptr< Session > ) > m_error_handler;
                
                std::function< void ( const std::shared_ptr< Session >, const std::function< void ( const std::shared_ptr< Session > ) >& ) > m_authentication_handler;
                
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
                
                //Getters
                
                //Setters
                
                //Operators
                ServiceImpl& operator =( const ServiceImpl& value ) = delete;
                
                //Properties
        };
    }
}
