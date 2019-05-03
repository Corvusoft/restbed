/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <future>
#include <ciso646>

//Project Includes
#include "corvusoft/restbed/logger.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"

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
using restbed::detail::SocketImpl;

//External Namespaces
using asio::ip::tcp;
using asio::io_service;
using asio::steady_timer;

#ifdef BUILD_SSL
    using asio::ssl::stream;
#endif

namespace restbed
{
    namespace detail
    {
        SocketImpl::SocketImpl( const shared_ptr< tcp::socket >& socket, const shared_ptr< Logger >& logger ) : m_error_handler( nullptr ),
            m_is_open( socket->is_open( ) ),
            m_logger( logger ),
            m_timeout( 0 ),
            m_io_service( socket->get_io_service( ) ),
            m_timer( make_shared< asio::steady_timer >( m_io_service ) ),
            m_strand( make_shared< io_service::strand > ( m_io_service ) ),
            m_resolver( nullptr ),
            m_socket( socket )
#ifdef BUILD_SSL
            , m_ssl_socket( nullptr )
#endif
        {
            return;
        }
#ifdef BUILD_SSL
        SocketImpl::SocketImpl( const shared_ptr< asio::ssl::stream< tcp::socket > >& socket, const shared_ptr< Logger >& logger ) : m_error_handler( nullptr ),
            m_is_open( socket->lowest_layer( ).is_open( ) ),
            m_logger( logger ),
            m_timeout( 0 ),
            m_io_service( socket->get_io_service( ) ),
            m_timer( make_shared< asio::steady_timer >( m_io_service ) ),
            m_strand( make_shared< io_service::strand > ( m_io_service ) ),
            m_resolver( nullptr ),
            m_socket( nullptr ),
            m_ssl_socket( socket )
        {
            return;
        }
#endif
        
        SocketImpl::~SocketImpl( void )
        {
            return;
        }
        
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
        }
        
        bool SocketImpl::is_open( void ) const
        {
            return m_is_open;
        }
        
        bool SocketImpl::is_closed( void ) const
        {
            return not m_is_open;
        }
        
        void SocketImpl::connect( const string& hostname, const uint16_t port, const function< void ( const error_code& ) >& callback )
        {
            m_resolver = make_shared< tcp::resolver >( m_io_service );
            tcp::resolver::query query( hostname, ::to_string( port ) );
            
            m_resolver->async_resolve( query, [ this, callback ]( const error_code & error, tcp::resolver::iterator endpoint_iterator )
            {
                if ( not error )
                {
#ifdef BUILD_SSL
                    auto& socket = ( m_socket not_eq nullptr ) ? *m_socket : m_ssl_socket->lowest_layer( );
#else
                    auto& socket = *m_socket;
#endif
                    asio::async_connect( socket, endpoint_iterator, [ this, callback ]( const error_code & error, tcp::resolver::iterator )
                    {
#ifdef BUILD_SSL
                    
                        if ( m_ssl_socket not_eq nullptr )
                        {
                            m_ssl_socket->handshake( asio::ssl::stream_base::client );
                        }
                        
#endif
                        m_is_open = true;
                        callback( error );
                    } );
                }
                else
                {
                    callback( error );
                }
            } );
        }
        
        void SocketImpl::sleep_for( const milliseconds& delay, const function< void ( const error_code& ) >& callback )
        {
            m_timer->cancel( );
            m_timer->expires_from_now( delay );
            m_timer->async_wait( callback );
        }

		void SocketImpl::start_write(const Bytes& data, const std::function< void ( const std::error_code&, std::size_t ) >& callback)
		{
			m_strand->post([this, data, callback] { write_helper(data, callback); });
        }

		size_t SocketImpl::start_read(const shared_ptr< asio::streambuf >& data, const string& delimiter, error_code& error)
		{
			return read( data, delimiter,error );
        }
        
		size_t SocketImpl::start_read(const shared_ptr< asio::streambuf >& data, const size_t length, error_code& error)
		{
			return read( data, length, error );
		}

        void SocketImpl::start_read( const std::size_t length, const function< void ( const Bytes ) > success, const function< void ( const error_code ) > failure )
		{
			m_strand->post([this, length, success, failure] {
				read(length, success, failure);
			});
        }
        
		void SocketImpl::start_read(const shared_ptr< asio::streambuf >& data, const size_t length, const function< void ( const error_code&, size_t ) >& callback)
		{
			m_strand->post([this, data, length, callback] 
			{
				read(data, length, callback);
			});
		}

		void SocketImpl::start_read(const shared_ptr< asio::streambuf >& data, const string& delimiter, const function< void ( const error_code&, size_t ) >& callback)
		{
			m_strand->post([this, data, delimiter, callback] 
			{
				read(data, delimiter, callback);
			});
        }

        string SocketImpl::get_local_endpoint( void )
        {
            error_code error;
            tcp::endpoint endpoint;
#ifdef BUILD_SSL
            
            if ( m_socket not_eq nullptr )
            {
#endif
                endpoint = m_socket->local_endpoint( error );
#ifdef BUILD_SSL
            }
            else
            {
                endpoint = m_ssl_socket->lowest_layer( ).local_endpoint( error );
            }
            
#endif
            
            if ( error )
            {
                m_is_open = false;
            }
            
            auto address = endpoint.address( );
            auto local = address.is_v4( ) ? address.to_string( ) + ":" : "[" + address.to_string( ) + "]:";
            local += ::to_string( endpoint.port( ) );
            
            return local;
        }
        
        string SocketImpl::get_remote_endpoint( void )
        {
            error_code error;
            tcp::endpoint endpoint;
#ifdef BUILD_SSL
            
            if ( m_socket not_eq nullptr )
            {
#endif
                endpoint = m_socket->remote_endpoint( error );
#ifdef BUILD_SSL
            }
            else
            {
                endpoint = m_ssl_socket->lowest_layer( ).remote_endpoint( error );
            }
            
#endif
            
            if ( error )
            {
                m_is_open = false;
            }
            
            auto address = endpoint.address( );
            auto remote = address.is_v4( ) ? address.to_string( ) + ":" : "[" + address.to_string( ) + "]:";
            remote += ::to_string( endpoint.port( ) );
            
            return remote;
        }
        
        void SocketImpl::set_timeout( const milliseconds& value )
        {
            m_timeout = value;
        }
        
        void SocketImpl::connection_timeout_handler( const shared_ptr< SocketImpl > socket, const error_code& error )
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

        void SocketImpl::write( void )
        {
			if(m_is_open)
			{
				m_timer->cancel( );
				m_timer->expires_from_now( m_timeout );
				m_timer->async_wait( m_strand->wrap( bind( &SocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) ) );
#ifdef BUILD_SSL
				if ( m_socket not_eq nullptr )
				{
#endif
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
					
#ifdef BUILD_SSL
				}
				else
				{
					asio::async_write(*m_ssl_socket, asio::buffer( get<0>(m_pending_writes.front()).data( ), get<0>(m_pending_writes.front()).size( ) ), m_strand->wrap( [ this ]( const error_code & error, size_t length )
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
            
#endif
			}
        }

        void SocketImpl::write( const Bytes& data, const function< void ( const error_code&, size_t ) >& callback )
        {
            const auto buffer = make_shared< Bytes >( data );
            
            m_timer->cancel( );
            m_timer->expires_from_now( m_timeout );
            m_timer->async_wait( m_strand->wrap( bind( &SocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) ) );
#ifdef BUILD_SSL
            
            if ( m_socket not_eq nullptr )
            {
#endif
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
#ifdef BUILD_SSL
            }
            else
            {
                asio::async_write( *m_ssl_socket, asio::buffer( buffer->data( ), buffer->size( ) ), m_strand->wrap( [ this, callback, buffer ]( const error_code & error, size_t length )
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
#endif
        }

		void SocketImpl::write_helper(const Bytes& data, const function< void ( const error_code&, size_t ) >& callback)
		{
			m_pending_writes.push(make_tuple(data, 0, callback));
			if(m_pending_writes.size() == 1)
			{
				write();
			}
		}
        
        size_t SocketImpl::read( const shared_ptr< asio::streambuf >& data, const size_t length, error_code& error )
        {
            m_timer->cancel( );
            m_timer->expires_from_now( m_timeout );
            m_timer->async_wait( m_strand->wrap( bind( &SocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) ) );

            size_t size = 0;
            auto finished = std::make_shared<bool>(false);
            auto sharedError = std::make_shared<error_code>();
            auto sharedSize = std::make_shared<size_t>(0);

#ifdef BUILD_SSL

            if ( m_socket not_eq nullptr )
            {
#endif
                asio::async_read( *m_socket, *data, asio::transfer_at_least( length ),
                    [ this, finished, sharedSize, sharedError ]( const error_code & error, size_t size ) {
                        *sharedError = error;
                        *sharedSize = size;
                        *finished = true;
                });
#ifdef BUILD_SSL
            }
            else
            {
                asio::async_read( *m_ssl_socket, *data, asio::transfer_at_least( length ),
                    [ this, finished, sharedSize, sharedError ]( const error_code & error, size_t size ) {
                        *sharedError = error;
                        *sharedSize = size;
                        *finished = true;
                });
            }
#endif

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
        
        void SocketImpl::read( const std::size_t length, const function< void ( const Bytes ) > success, const function< void ( const error_code ) > failure )
        {
            m_timer->cancel( );
            m_timer->expires_from_now( m_timeout );
            m_timer->async_wait( m_strand->wrap( bind( &SocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) ) );
            
#ifdef BUILD_SSL
            
            if ( m_socket not_eq nullptr )
            {
#endif
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
#ifdef BUILD_SSL
            }
            else
            {
                auto data = make_shared< asio::streambuf >( );
                asio::async_read( *m_ssl_socket, *data, asio::transfer_exactly( length ), [ this, data, success, failure ]( const error_code code, const size_t length )
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
            
#endif
        }
        
        void SocketImpl::read( const shared_ptr< asio::streambuf >& data, const size_t length, const function< void ( const error_code&, size_t ) >& callback )
        {
            m_timer->cancel( );
            m_timer->expires_from_now( m_timeout );
            m_timer->async_wait( m_strand->wrap( bind( &SocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) ) );
            
#ifdef BUILD_SSL
            
            if ( m_socket not_eq nullptr )
            {
#endif
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
#ifdef BUILD_SSL
            }
            else
            {
                asio::async_read( *m_ssl_socket, *data, asio::transfer_at_least( length ), m_strand->wrap( [ this, callback ]( const error_code & error, size_t length )
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
            
#endif
        }
        
        size_t SocketImpl::read( const shared_ptr< asio::streambuf >& data, const string& delimiter, error_code& error )
        {
            m_timer->cancel( );
            m_timer->expires_from_now( m_timeout );
            m_timer->async_wait( bind( &SocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) );

            size_t length = 0;
            auto finished = std::make_shared<bool>(false);
            auto sharedError = std::make_shared<error_code>();
            auto sharedLength = std::make_shared<size_t>(0);

#ifdef BUILD_SSL

            if ( m_socket not_eq nullptr )
            {
#endif
                asio::async_read_until( *m_socket, *data, delimiter,
                    [ this, finished, sharedLength, sharedError ]( const error_code & error, size_t length ) {
                        *sharedError = error;
                        *sharedLength = length;
                        *finished = true;
                });
#ifdef BUILD_SSL
            }
            else
            {
                asio::async_read_until( *m_ssl_socket, *data, delimiter,
                    [ this, finished, sharedLength, sharedError ]( const error_code & error, size_t length ) {
                        *sharedError = error;
                        *sharedLength = length;
                        *finished = true;
                });
            }
#endif

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
        
        void SocketImpl::read( const shared_ptr< asio::streambuf >& data, const string& delimiter, const function< void ( const error_code&, size_t ) >& callback )
        {
            m_timer->cancel( );
            m_timer->expires_from_now( m_timeout );
            m_timer->async_wait( m_strand->wrap( bind( &SocketImpl::connection_timeout_handler, this, shared_from_this( ), _1 ) ) );
            
#ifdef BUILD_SSL
            
            if ( m_socket not_eq nullptr )
            {
#endif
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
#ifdef BUILD_SSL
            }
            else
            {
                asio::async_read_until( *m_ssl_socket, *data, delimiter, m_strand->wrap( [ this, callback ]( const error_code & error, size_t length )
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
            
#endif
        }
    }
}
