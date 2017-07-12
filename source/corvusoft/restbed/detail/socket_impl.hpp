/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_DETAIL_SOCKET_IMPL_H
#define _RESTBED_DETAIL_SOCKET_IMPL_H 1

//System Includes
#include <chrono>
#include <string>
#include <memory>
#include <cstdint>
#include <stdexcept>
#include <functional>
#include <system_error>

//Project Includes
#include "corvusoft/restbed/byte.hpp"

//External Includes
#include <asio/ip/tcp.hpp>
#include <asio/streambuf.hpp>
#include <asio/steady_timer.hpp>
#include <asio/io_service.hpp>
#include <asio/io_service_strand.hpp>


#ifdef BUILD_SSL
    #include <asio/ssl.hpp>
#endif

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Logger;
    class Session;
    
    namespace detail
    {
        //Forward Declarations
        
        class SocketImpl : public std::enable_shared_from_this<SocketImpl>
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                SocketImpl( const std::shared_ptr< asio::ip::tcp::socket >& socket, const std::shared_ptr< Logger >& logger = nullptr );
#ifdef BUILD_SSL
                SocketImpl( const std::shared_ptr< asio::ssl::stream< asio::ip::tcp::socket > >& socket, const std::shared_ptr< Logger >& logger = nullptr );
#endif
                virtual ~SocketImpl( void );
                
                //Functionality
                void close( void );
                
                bool is_open( void ) const;
                
                bool is_closed( void ) const;
                
                void connect(  const std::string& hostname, const uint16_t port, const std::function< void ( const std::error_code& ) >& callback );
                
                void sleep_for( const std::chrono::milliseconds& delay, const std::function< void ( const std::error_code& ) >& callback );
                
                void write( const Bytes& data, const std::function< void ( const std::error_code&, std::size_t ) >& callback );
                
                size_t read( const std::shared_ptr< asio::streambuf >& data, const std::size_t length, std::error_code& error );
                
                void read( const std::size_t length, const std::function< void ( const Bytes ) > success, const std::function< void ( const std::error_code ) > failure );
                
                void read( const std::shared_ptr< asio::streambuf >& data, const std::size_t length, const std::function< void ( const std::error_code&, std::size_t ) >& callback );
                
                size_t read( const std::shared_ptr< asio::streambuf >& data, const std::string& delimiter, std::error_code& error );
                
                void read( const std::shared_ptr< asio::streambuf >& data, const std::string& delimiter, const std::function< void ( const std::error_code&, std::size_t ) >& callback );
                
                //Getters
                std::string get_local_endpoint( void );
                
                std::string get_remote_endpoint( void );
                
                //Setters
                void set_timeout( const std::chrono::milliseconds& value );
                
                //Operators
                
                //Properties
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
                SocketImpl( const SocketImpl& original ) = delete;
                
                //Functionality
                void connection_timeout_handler( const std::shared_ptr< SocketImpl > socket, const std::error_code& error );
                
                //Getters
                
                //Setters
                
                //Operators
                SocketImpl& operator =( const SocketImpl& value ) = delete;
                
                //Properties
                bool m_is_open;
                
                std::shared_ptr< Bytes > m_buffer;
                
                std::shared_ptr< Logger > m_logger;
                
                std::chrono::milliseconds m_timeout;
                
                std::shared_ptr< asio::steady_timer > m_timer;
                
                std::shared_ptr< asio::io_service::strand > m_strand;
                
                std::shared_ptr< asio::ip::tcp::resolver > m_resolver;
                
                std::shared_ptr< asio::ip::tcp::socket > m_socket;
                
#ifdef BUILD_SSL
                std::shared_ptr< asio::ssl::stream< asio::ip::tcp::socket > > m_ssl_socket;
#endif
        };
    }
}

#endif  /* _RESTBED_DETAIL_SOCKET_IMPL_H */
