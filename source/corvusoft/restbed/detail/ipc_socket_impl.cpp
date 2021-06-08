/*
 * Copyright 2013-2020, Corvusoft Ltd, All Rights Reserved.
 */
#ifdef BUILD_IPC

//System Includes
#include <future>
#include <ciso646>

//Project Includes
#include "corvusoft/restbed/logger.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"
#include "corvusoft/restbed/detail/ipc_socket_impl.hpp"

//External Includes
#include <asio/read.hpp>
#include <asio/write.hpp>
#include <asio/connect.hpp>
#include <asio/read_until.hpp>

//System Namespaces
using std::get;
using std::bind;
using std::size_t;
using std::string;
using std::promise;
using std::function;
using std::to_string;
using std::error_code;
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;
using std::placeholders::_1;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

//Project Namespaces
using restbed::detail::IPCSocketImpl;

//External Namespaces
using asio::io_service;
using asio::steady_timer;
using asio::local::stream_protocol;

namespace restbed
{
    namespace detail
    {
        IPCSocketImpl::IPCSocketImpl( asio::io_context& context, const shared_ptr< stream_protocol::socket >& socket, const shared_ptr< Logger >& logger ) : SocketImpl( context ),
            m_error_handler( nullptr ),
            m_is_open( socket->is_open( ) ),
            m_pending_writes( ),
            m_logger( logger ),
            m_timeout( 0 ),
            m_io_service( context ),
            m_timer( make_shared< asio::steady_timer >( m_io_service ) ),
            m_strand( make_shared< io_service::strand > ( m_io_service ) ),
            m_socket( socket )
        {
            return;
        }
        
        void IPCSocketImpl::close( void )
        {
            m_is_open = false;
            
            if ( m_timer not_eq nullptr )
            {
                m_timer->cancel( );
            }
            
            if ( m_socket not_eq nullptr )
            {
                m_socket->close( );
            }
        }
        
        bool IPCSocketImpl::is_open( void ) const
        {
            return m_is_open;
        }
        
        bool IPCSocketImpl::is_closed( void ) const
        {
            return not m_is_open;
        }
        
        void IPCSocketImpl::connect( const string&, const uint16_t, const function< void ( const error_code& ) >& callback )
        {          
            m_socket->async_connect( stream_protocol::endpoint("/tmp/restbed.sock"), [ this, callback ]( const error_code & error )
            {
                m_is_open = true;
                callback( error );
            } );
        }
        
        void IPCSocketImpl::sleep_for( const milliseconds& delay, const function< void ( const error_code& ) >& callback )
        {
            m_timer->cancel( );
            m_timer->expires_from_now( delay );
            m_timer->async_wait( callback );
        }

        void IPCSocketImpl::start_write(const Bytes& data, const std::function< void ( const std::error_code&, std::size_t ) >& callback)
        {
            m_strand->post([this, data, callback] { write_helper(data, callback); });
        }

        size_t IPCSocketImpl::start_read(const shared_ptr< asio::streambuf >& data, const string& delimiter, error_code& error)
        {
            return read( data, delimiter,error );
        }
        
        size_t IPCSocketImpl::start_read(const shared_ptr< asio::streambuf >& data, const size_t length, error_code& error)
        {
            return read( data, length, error );
        }

        void IPCSocketImpl::start_read( const std::size_t length, const function< void ( const Bytes ) > success, const function< void ( const error_code ) > failure )
        {
            m_strand->post([this, length, success, failure] {
                read(length, success, failure);
            });
        }
        
        void IPCSocketImpl::start_read(const shared_ptr< asio::streambuf >& data, const size_t length, const function< void ( const error_code&, size_t ) >& callback)
        {
            m_strand->post([this, data, length, callback] 
            {
                read(data, length, callback);
            });
        }

        void IPCSocketImpl::start_read(const shared_ptr< asio::streambuf >& data, const string& delimiter, const function< void ( const error_code&, size_t ) >& callback)
        {
            m_strand->post([this, data, delimiter, callback] 
            {
                read(data, delimiter, callback);
            });
        }

        string IPCSocketImpl::get_local_endpoint( void )
        {                        
            return "/tmp/restbed.sock";
        }
        
        string IPCSocketImpl::get_remote_endpoint( void )
        {
            return "/tmp/restbed.sock";
        }
        
        void IPCSocketImpl::set_timeout( const milliseconds& value )
        {
            m_timeout = value;
        }

        void IPCSocketImpl::set_keep_alive( const uint32_t, const uint32_t, const uint32_t)
        {
            return;
        }

        shared_ptr< IPCSocketImpl > IPCSocketImpl::shared_from_this( void )
        {
            return std::dynamic_pointer_cast< IPCSocketImpl >( SocketImpl::shared_from_this( ) );
            //return shared_ptr< IPCSocketImpl >( this ); //test for circular reference and memory leak.            
        }
        
        void IPCSocketImpl::connection_timeout_handler( const shared_ptr< IPCSocketImpl > socket, const error_code& error )
        {
            if ( error or socket == nullptr or socket->m_timer->expires_at( ) > steady_clock::now( ) )
            {
                return;
            }
            
            socket->close( );
            
            if ( m_error_handler not_eq nullptr )
            {
                m_error_handler( 408, runtime_error( "The socket timed out waiting for the request." ), nullptr );
            }
        }

        void IPCSocketImpl::write( void )
        {
            if(m_is_open)
            {
                m_timer->cancel( );
                m_timer->expires_from_now( m_timeout );
                m_timer->async_wait( m_strand->wrap( bind( &IPCSocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) ) );

                    asio::async_write( *m_socket, asio::buffer( get<0>(m_pending_writes.front()).data( ), get<0>(m_pending_writes.front()).size( ) ), m_strand->wrap( [ this ]( const error_code & error, size_t length )
                    {
                        m_timer->cancel( );
                        auto callback = get<2>(m_pending_writes.front());
                        auto & retries = get<1>(m_pending_writes.front());
                        auto & buffer = get<0>(m_pending_writes.front());
                        if(length < buffer.size() &&  retries < MAX_WRITE_RETRIES &&  error not_eq asio::error::operation_aborted)
                        {
                            ++retries;
                            buffer.erase(buffer.begin(),buffer.begin() + length);
                        }
                        else
                        {
                            m_pending_writes.pop();
                        }
                        if ( error not_eq asio::error::operation_aborted )
                        {
                            callback( error, length );
                        }
                        if(!m_pending_writes.empty())
                        {
                            write();
                        }
                    } ) );
            }
            else
            {
                while(!m_pending_writes.empty())
                {
                    m_pending_writes.pop();
                }
            }
        }

        void IPCSocketImpl::write( const Bytes& data, const function< void ( const error_code&, size_t ) >& callback )
        {
            const auto buffer = make_shared< Bytes >( data );
            
            m_timer->cancel( );
            m_timer->expires_from_now( m_timeout );
            m_timer->async_wait( m_strand->wrap( bind( &IPCSocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) ) );

            asio::async_write( *m_socket, asio::buffer( buffer->data( ), buffer->size( ) ), m_strand->wrap( [ this, callback, buffer ]( const error_code & error, size_t length )
            {
                m_timer->cancel( );
                
                if ( error )
                {
                    m_is_open = false;
                }
                
                if ( error not_eq asio::error::operation_aborted )
                {
                    callback( error, length );
                }
            } ) );
        }

        void IPCSocketImpl::write_helper(const Bytes& data, const function< void ( const error_code&, size_t ) >& callback)
        {
            const uint8_t retries = 0;
            m_pending_writes.push(make_tuple(data, retries, callback));
            if(m_pending_writes.size() == 1)
            {
                write();
            }
        }
        
        size_t IPCSocketImpl::read( const shared_ptr< asio::streambuf >& data, const size_t length, error_code& error )
        {
            m_timer->cancel( );
            m_timer->expires_from_now( m_timeout );
            m_timer->async_wait( m_strand->wrap( bind( &IPCSocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) ) );

            size_t size = 0;
            auto finished = std::make_shared<bool>(false);
            auto sharedError = std::make_shared<error_code>();
            auto sharedSize = std::make_shared<size_t>(0);

            asio::async_read( *m_socket, *data, asio::transfer_at_least( length ),
                [ finished, sharedSize, sharedError ]( const error_code & error, size_t size ) {
                    *sharedError = error;
                    *sharedSize = size;
                    *finished = true;
            });

            while (!*finished)
                m_io_service.run_one();
            error = *sharedError;
            size = *sharedSize;
            m_timer->cancel( );

            if ( error )
            {
                m_is_open = false;
            }

            return size;
        }
        
        void IPCSocketImpl::read( const std::size_t length, const function< void ( const Bytes ) > success, const function< void ( const error_code ) > failure )
        {
            m_timer->cancel( );
            m_timer->expires_from_now( m_timeout );
            m_timer->async_wait( m_strand->wrap( bind( &IPCSocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) ) );
            
            auto data = make_shared< asio::streambuf >( );
            asio::async_read( *m_socket, *data, asio::transfer_exactly( length ), [ this, data, success, failure ]( const error_code code, const size_t length )
            {
                m_timer->cancel( );
                
                if ( code )
                {
                    m_is_open = false;
                    failure( code );
                }
                else
                {
                    const auto data_ptr = asio::buffer_cast< const Byte* >( data->data( ) );
                    success( Bytes( data_ptr, data_ptr + length ) );
                }
            } );
        }
        
        void IPCSocketImpl::read( const shared_ptr< asio::streambuf >& data, const size_t length, const function< void ( const error_code&, size_t ) >& callback )
        {
            m_timer->cancel( );
            m_timer->expires_from_now( m_timeout );
            m_timer->async_wait( m_strand->wrap( bind( &IPCSocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) ) );
            
            asio::async_read( *m_socket, *data, asio::transfer_at_least( length ), m_strand->wrap( [ this, callback ]( const error_code & error, size_t length )
            {
                m_timer->cancel( );
                
                if ( error )
                {
                    m_is_open = false;
                }
                
                if ( error not_eq asio::error::operation_aborted )
                {
                    callback( error, length );
                }
            } ) );
        }
        
        size_t IPCSocketImpl::read( const shared_ptr< asio::streambuf >& data, const string& delimiter, error_code& error )
        {
            m_timer->cancel( );
            m_timer->expires_from_now( m_timeout );
            m_timer->async_wait( bind( &IPCSocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) );

            size_t length = 0;
            auto finished = std::make_shared<bool>(false);
            auto sharedError = std::make_shared<error_code>();
            auto sharedLength = std::make_shared<size_t>(0);

            asio::async_read_until( *m_socket, *data, delimiter,
                [ finished, sharedLength, sharedError ]( const error_code & error, size_t length ) {
                    *sharedError = error;
                    *sharedLength = length;
                    *finished = true;
            });

            while (!*finished)
                m_io_service.run_one();
            error = *sharedError;
            length = *sharedLength;
            m_timer->cancel( );

            if ( error )
            {
                m_is_open = false;
            }

            return length;
        }
        
        void IPCSocketImpl::read( const shared_ptr< asio::streambuf >& data, const string& delimiter, const function< void ( const error_code&, size_t ) >& callback )
        {
            m_timer->cancel( );
            m_timer->expires_from_now( m_timeout );
            m_timer->async_wait( m_strand->wrap( bind( &IPCSocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) ) );
            
            asio::async_read_until( *m_socket, *data, delimiter, m_strand->wrap( [ this, callback ]( const error_code & error, size_t length )
            {
                m_timer->cancel( );
                
                if ( error )
                {
                    m_is_open = false;
                }
                
                if ( error not_eq asio::error::operation_aborted )
                {
                    callback( error, length );
                }
            } ) );
        }
    }
}

#endif
