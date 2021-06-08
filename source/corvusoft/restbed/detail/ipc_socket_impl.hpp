/*
 * Copyright 2013-2020, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

#ifdef BUILD_IPC

//System Includes
#include <queue>
#include <tuple>
#include <chrono>
#include <string>
#include <memory>
#include <cstdint>
#include <stdexcept>
#include <functional>
#include <system_error>

//Project Includes
#include "corvusoft/restbed/byte.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"

//External Includes
#include <asio/streambuf.hpp>
#include <asio/steady_timer.hpp>
#include <asio/io_service.hpp>
#include <asio/io_service_strand.hpp>
#include <asio/local/stream_protocol.hpp>

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
        
        class IPCSocketImpl : virtual public SocketImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                IPCSocketImpl( asio::io_context& context, const std::shared_ptr< asio::local::stream_protocol::socket >& socket, const std::shared_ptr< Logger >& logger = nullptr );

                ~IPCSocketImpl( void ) = default;
                
                //Functionality
                void close( void ) override;
                
                bool is_open( void ) const override;
                
                bool is_closed( void ) const override;
                
                void connect(  const std::string& hostname, const uint16_t port, const std::function< void ( const std::error_code& ) >& callback ) override;
                
                void sleep_for( const std::chrono::milliseconds& delay, const std::function< void ( const std::error_code& ) >& callback ) override;
                
				void start_write(const Bytes& data, const std::function< void ( const std::error_code&, std::size_t ) >& callback) override;
				
				size_t start_read( const std::shared_ptr< asio::streambuf >& data, const std::string& delimiter, std::error_code& error ) override;
				
				size_t start_read( const std::shared_ptr< asio::streambuf >& data, const std::size_t length, std::error_code& error ) override;
                
				void start_read(const std::size_t length, const std::function< void ( const Bytes ) > success, const std::function< void ( const std::error_code ) > failure ) override;
                
				void start_read( const std::shared_ptr< asio::streambuf >& data, const std::size_t length, const std::function< void ( const std::error_code&, std::size_t ) >& callback ) override;
                
				void start_read(const std::shared_ptr< asio::streambuf >& data, const std::string& delimiter, const std::function< void ( const std::error_code&, std::size_t ) >& callback ) override;

                //Getters
                std::string get_local_endpoint( void ) override;
                
                std::string get_remote_endpoint( void ) override;
                
                //Setters
                void set_timeout( const std::chrono::milliseconds& value ) override;

                void set_keep_alive( const uint32_t start, const uint32_t interval, const uint32_t cnt) override;
                
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
                IPCSocketImpl( const IPCSocketImpl& original ) = delete;
                
                //Functionality
                std::shared_ptr< IPCSocketImpl > shared_from_this( void );

                void connection_timeout_handler( const std::shared_ptr< IPCSocketImpl > socket, const std::error_code& error );

                void write( void );
                
                void write( const Bytes& data, const std::function< void ( const std::error_code&, std::size_t ) >& callback );
                
				void write_helper( const Bytes& data, const std::function< void ( const std::error_code&, std::size_t ) >& callback );

                size_t read( const std::shared_ptr< asio::streambuf >& data, const std::size_t length, std::error_code& error );
                
                void read( const std::size_t length, const std::function< void ( const Bytes ) > success, const std::function< void ( const std::error_code ) > failure );
                
                void read( const std::shared_ptr< asio::streambuf >& data, const std::size_t length, const std::function< void ( const std::error_code&, std::size_t ) >& callback );
                
                size_t read( const std::shared_ptr< asio::streambuf >& data, const std::string& delimiter, std::error_code& error );
                
                void read( const std::shared_ptr< asio::streambuf >& data, const std::string& delimiter, const std::function< void ( const std::error_code&, std::size_t ) >& callback );
 
                //Getters
                
                //Setters
                
                //Operators
                IPCSocketImpl& operator =( const IPCSocketImpl& value ) = delete;
                
                //Properties
                bool m_is_open;

		        const uint8_t MAX_WRITE_RETRIES = 5;
                
	            std::queue< std::tuple< Bytes, uint8_t, std::function< void ( const std::error_code&, std::size_t ) > > > m_pending_writes;

                std::shared_ptr< Logger > m_logger;
                
                std::chrono::milliseconds m_timeout;

                asio::io_context &m_io_service;

                std::shared_ptr< asio::steady_timer > m_timer;
                
                std::shared_ptr< asio::io_service::strand > m_strand;
                                
                std::shared_ptr< asio::local::stream_protocol::socket > m_socket;
        };
    }
}

#endif
