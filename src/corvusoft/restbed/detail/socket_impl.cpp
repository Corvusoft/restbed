/*
 * Copyright 2013-2026, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <ciso646>

//Project Includes
#include "corvusoft/restbed/logger.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"

//External Includes
#include <asio/read.hpp>
#include <asio/write.hpp>
#include <asio/connect.hpp>
#include <asio/read_until.hpp>
#include <asio/bind_executor.hpp>


//System Namespaces
using std::get;
using std::bind;
using std::size_t;
using std::string;
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
using restbed::detail::SocketImpl;

//External Namespaces
using asio::ip::tcp;
using asio::io_context;
using asio::steady_timer;

#ifdef BUILD_SSL
    using asio::ssl::stream;
#endif

namespace restbed
{
    namespace detail
    {
        SocketImpl::SocketImpl( asio::io_context& context, const shared_ptr< tcp::socket >& socket, const shared_ptr< Logger >& logger ) : m_error_handler( nullptr ),
            m_is_open( socket->is_open( ) ),
            m_pending_writes( ),
            m_logger( logger ),
            m_timeout( 0 ),
            m_io_context( context ),
            m_timer( make_shared< asio::steady_timer >( m_io_context ) ),
            m_strand( make_shared< asio::strand< asio::io_context::executor_type > > ( asio::make_strand( m_io_context ) ) ),
            m_socket( socket )
#ifdef BUILD_SSL
            , m_ssl_socket( nullptr )
#endif
#ifdef BUILD_IPC
            , m_ipc_socket( nullptr )
            , m_path( "" )
#endif
        {
            return;
        }
#ifdef BUILD_SSL
        SocketImpl::SocketImpl( asio::io_context& context, const shared_ptr< asio::ssl::stream< tcp::socket > >& socket, const shared_ptr< Logger >& logger ) : m_error_handler( nullptr ),
            m_is_open( socket->lowest_layer( ).is_open( ) ),
            m_pending_writes( ),
            m_logger( logger ),
            m_timeout( 0 ),
            m_io_context( context ),
            m_timer( make_shared< asio::steady_timer >( m_io_context ) ),
            m_strand( make_shared< asio::strand< asio::io_context::executor_type > > ( asio::make_strand( m_io_context ) ) ),
            m_socket( nullptr ),
            m_ssl_socket( socket )
#ifdef BUILD_IPC
            , m_ipc_socket( nullptr )
            , m_path( "" )
#endif
        {
            return;
        }
#endif
#ifdef BUILD_IPC
        SocketImpl::SocketImpl( asio::io_context& context, const shared_ptr< asio::local::stream_protocol::socket >& socket, const string& path, const shared_ptr< Logger >& logger ) : m_error_handler( nullptr ),
            m_is_open( socket->is_open( ) ),
            m_pending_writes( ),
            m_logger( logger ),
            m_timeout( 0 ),
            m_io_context( context ),
            m_timer( make_shared< asio::steady_timer >( m_io_context ) ),
            m_strand( make_shared< asio::strand< asio::io_context::executor_type > > ( asio::make_strand( m_io_context ) ) ),
            m_socket( nullptr )
#ifdef BUILD_SSL
            , m_ssl_socket( nullptr )
#endif
            , m_ipc_socket( socket )
            , m_path( path )
        {
            return;
        }
#endif

        void SocketImpl::close( void )
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

#ifdef BUILD_SSL

            if ( m_ssl_socket not_eq nullptr )
            {
                m_ssl_socket->lowest_layer( ).close( );
            }

#endif
#ifdef BUILD_IPC

            if ( m_ipc_socket not_eq nullptr )
            {
                m_ipc_socket->close( );
            }

#endif
        }

        bool SocketImpl::is_open( void ) const
        {
            return m_is_open;
        }

        bool SocketImpl::is_closed( void ) const
        {
            return not m_is_open;
        }

        void SocketImpl::sleep_for( const milliseconds& delay, const function< void ( const error_code& ) >& callback )
        {
            m_strand->post( [ this, self = shared_from_this( ), delay, callback ]
            {
                m_timer->cancel( );
                m_timer->expires_after( delay );
                m_timer->async_wait( asio::bind_executor( *m_strand, callback ) );
            }, asio::get_associated_allocator( m_strand ) );
        }

        void SocketImpl::start_write( const Bytes& data, const std::function< void ( const std::error_code&, std::size_t ) >& callback )
        {
            m_strand->post( [this, self = shared_from_this(), data, callback] { write_helper( data, callback ); }, asio::get_associated_allocator( m_strand ) );
        }

        void SocketImpl::start_read( const std::size_t length, const function< void ( const Bytes ) > success, const function< void ( const error_code ) > failure )
        {
            m_strand->post( [this, self = shared_from_this(), length, success, failure]
            {
                read( length, success, failure );
            }, asio::get_associated_allocator( m_strand ) );
        }

        void SocketImpl::start_read( const shared_ptr< asio::streambuf >& data, const size_t length, const function< void ( const error_code&, size_t ) >& callback )
        {
            m_strand->post( [this, self = shared_from_this(), data, length, callback]
            {
                read( data, length, callback );
            }, asio::get_associated_allocator( m_strand ) );
        }

        void SocketImpl::start_read( const shared_ptr< asio::streambuf >& data, const string& delimiter, const function< void ( const error_code&, size_t ) >& callback )
        {
            m_strand->post( [this, self = shared_from_this(), data, delimiter, callback]
            {
                read( data, delimiter, callback );
            }, asio::get_associated_allocator( m_strand ) );
        }

        asio::basic_socket< tcp >& SocketImpl::tcp_layer( void )
        {
#ifdef BUILD_SSL

            if ( m_socket == nullptr )
            {
                return m_ssl_socket->lowest_layer( );
            }

#endif
            return *m_socket;
        }

        string SocketImpl::format_endpoint( const tcp::endpoint& endpoint )
        {
            const auto address = endpoint.address( );
            auto result = address.is_v4( ) ? address.to_string( ) + ":" : "[" + address.to_string( ) + "]:";
            result += ::to_string( endpoint.port( ) );

            return result;
        }

        string SocketImpl::get_local_endpoint( void )
        {
#ifdef BUILD_IPC

            if ( m_ipc_socket not_eq nullptr )
            {
                return m_path;
            }

#endif
            error_code error;
            const auto endpoint = tcp_layer( ).local_endpoint( error );

            if ( error )
            {
                m_is_open = false;
            }

            return format_endpoint( endpoint );
        }

        string SocketImpl::get_remote_endpoint( void )
        {
#ifdef BUILD_IPC

            if ( m_ipc_socket not_eq nullptr )
            {
                return m_path;
            }

#endif
            error_code error;
            const auto endpoint = tcp_layer( ).remote_endpoint( error );

            if ( error )
            {
                m_is_open = false;
            }

            return format_endpoint( endpoint );
        }

        void SocketImpl::set_timeout( const milliseconds& value )
        {
            m_timeout = value;
        }

        void SocketImpl::set_keep_alive( const uint32_t start, const uint32_t interval, const uint32_t cnt )
        {
#ifdef BUILD_IPC

            if ( m_ipc_socket not_eq nullptr )
            {
                return;
            }

#endif
            ( void ) cnt;
            ( void ) start;
            ( void ) interval;

            auto& socket = tcp_layer( );

#ifdef _WIN32
            DWORD val = 1;
            setsockopt( socket.native_handle(), SOL_SOCKET, SO_KEEPALIVE, reinterpret_cast< const char* >( &val ), sizeof( val ) );

#ifdef TCP_KEEPIDLE
            DWORD start_val = start;
            setsockopt( socket.native_handle(), IPPROTO_TCP, TCP_KEEPIDLE,
                        reinterpret_cast< const char* >( &start_val ), sizeof( start_val ) );
#endif
#ifdef TCP_KEEPINTVL
            DWORD interval_val = interval;
            setsockopt( socket.native_handle(), IPPROTO_TCP, TCP_KEEPINTVL,
                        reinterpret_cast< const char* >( &interval_val ), sizeof( interval_val ) );
#endif
#ifdef TCP_KEEPCNT
            DWORD cnt_val = cnt;
            setsockopt( socket.native_handle(), IPPROTO_TCP, TCP_KEEPCNT,
                        reinterpret_cast< const char* >( &cnt_val ), sizeof( cnt_val ) );
#endif
#else
            uint32_t val = 1;
            setsockopt( socket.native_handle(), SOL_SOCKET, SO_KEEPALIVE, &val, sizeof( uint32_t ) );
#ifdef __APPLE__
            setsockopt( socket.native_handle(), IPPROTO_TCP, TCP_KEEPALIVE, &start, sizeof( uint32_t ) );
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
            setsockopt( socket.native_handle(), IPPROTO_TCP, SO_KEEPALIVE, &start, sizeof( uint32_t ) );
#else
            setsockopt( socket.native_handle(), SOL_TCP, TCP_KEEPIDLE, &start, sizeof( uint32_t ) );
            setsockopt( socket.native_handle(), SOL_TCP, TCP_KEEPINTVL, &interval, sizeof( uint32_t ) );
            setsockopt( socket.native_handle(), SOL_TCP, TCP_KEEPCNT, &cnt, sizeof( uint32_t ) );
#endif
#endif
        }

        SocketImpl::SocketImpl( asio::io_context& context ) : m_error_handler( nullptr ),
            m_is_open( false ),
            m_pending_writes( ),
            m_logger( nullptr ),
            m_timeout( 0 ),
            m_io_context( context ),
            m_timer( make_shared< asio::steady_timer >( m_io_context ) ),
            m_strand( make_shared< asio::strand< asio::io_context::executor_type > > ( asio::make_strand( m_io_context ) ) ),
            m_socket( nullptr )
#ifdef BUILD_SSL
            , m_ssl_socket( nullptr )
#endif
#ifdef BUILD_IPC
            , m_ipc_socket( nullptr )
            , m_path( "" )
#endif
        {
            return;
        }

        void SocketImpl::connection_timeout_handler( const shared_ptr< SocketImpl > socket, const error_code& error )
        {
            if ( error or socket == nullptr or socket->m_timer->expiry( ) > steady_clock::now( ) )
            {
                return;
            }

            socket->close( );

            if ( m_error_handler not_eq nullptr )
            {
                m_error_handler( 408, runtime_error( "The socket timed out waiting for the request." ), nullptr );
            }
        }

        void SocketImpl::write( void )
        {
            if ( m_is_open )
            {
                m_timer->cancel( );
                m_timer->expires_after( m_timeout );
                m_timer->async_wait( asio::bind_executor( *m_strand, bind( &SocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) ) );

                with_active_stream( [ this, self = shared_from_this() ]( auto & stream )
                {
                    asio::async_write( stream, asio::buffer( get<0>( m_pending_writes.front() ).data( ), get<0>( m_pending_writes.front() ).size( ) ), asio::bind_executor( *m_strand, [ this, self ]( const error_code & error, size_t length )
                    {
                        m_timer->cancel( );
                        auto callback = get<2>( m_pending_writes.front() );
                        auto& retries = get<1>( m_pending_writes.front() );
                        auto& buffer = get<0>( m_pending_writes.front() );

                        if ( length < buffer.size() &&  retries < MAX_WRITE_RETRIES &&  error not_eq asio::error::operation_aborted )
                        {
                            ++retries;
                            buffer.erase( buffer.begin(), buffer.begin() + length );
                        }
                        else
                        {
                            m_pending_writes.pop();
                        }

                        if ( error not_eq asio::error::operation_aborted )
                        {
                            callback( error, length );
                        }

                        if ( !m_pending_writes.empty() )
                        {
                            write();
                        }
                    } ) );
                } );
            }
            else
            {
                while ( !m_pending_writes.empty() )
                {
                    m_pending_writes.pop();
                }
            }
        }

        void SocketImpl::write_helper( const Bytes& data, const function< void ( const error_code&, size_t ) >& callback )
        {
            const uint8_t retries = 0;
            m_pending_writes.push( make_tuple( data, retries, callback ) );

            if ( m_pending_writes.size() == 1 )
            {
                write();
            }
        }

        void SocketImpl::read( const std::size_t length, const function< void ( const Bytes ) > success, const function< void ( const error_code ) > failure )
        {
            m_timer->cancel( );
            m_timer->expires_after( m_timeout );
            m_timer->async_wait( asio::bind_executor( *m_strand, bind( &SocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) ) );

            auto data = make_shared< asio::streambuf >( );
            with_active_stream( [ this, self = shared_from_this(), data, length, success, failure ]( auto & stream )
            {
                asio::async_read( stream, *data, asio::transfer_exactly( length ), asio::bind_executor( *m_strand, [ this, self, data, success, failure ]( const error_code code, const size_t length )
                {
                    m_timer->cancel( );

                    if ( code )
                    {
                        m_is_open = false;

                        if ( code not_eq asio::error::operation_aborted )
                        {
                            failure( code );
                        }
                    }
                    else
                    {
                        Bytes buf( length );
                        asio::buffer_copy( asio::buffer( buf ), data->data( ) );
                        success( buf );
                    }
                } ) );
            } );
        }

        void SocketImpl::read( const shared_ptr< asio::streambuf >& data, const size_t length, const function< void ( const error_code&, size_t ) >& callback )
        {
            m_timer->cancel( );
            m_timer->expires_after( m_timeout );
            m_timer->async_wait( asio::bind_executor( *m_strand, bind( &SocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) ) );

            with_active_stream( [ this, self = shared_from_this(), data, length, callback ]( auto & stream )
            {
                asio::async_read( stream, *data, asio::transfer_at_least( length ), asio::bind_executor( *m_strand, [ this, self, callback ]( const error_code & error, size_t length )
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
            } );
        }

        void SocketImpl::read( const shared_ptr< asio::streambuf >& data, const string& delimiter, const function< void ( const error_code&, size_t ) >& callback )
        {
            m_timer->cancel( );
            m_timer->expires_after( m_timeout );
            m_timer->async_wait( asio::bind_executor( *m_strand, bind( &SocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) ) );

            with_active_stream( [ this, self = shared_from_this(), data, delimiter, callback ]( auto & stream )
            {
                asio::async_read_until( stream, *data, delimiter, asio::bind_executor( *m_strand, [ this, self, callback ]( const error_code & error, size_t length )
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
            } );
        }
    }
}
