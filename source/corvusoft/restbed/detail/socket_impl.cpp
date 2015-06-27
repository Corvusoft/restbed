/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/logger.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"

//External Includes

//System Namespaces
using std::size_t;
using std::string;
using std::function;
using std::to_string;
using std::shared_ptr;
using std::make_shared;
using std::chrono::seconds;
using std::chrono::microseconds;

//Project Namespaces
using restbed::detail::SocketImpl;

//External Namespaces
using asio::ip::tcp;
using asio::error_code;
using asio::steady_timer;
using framework::Bytes;

#ifdef BUILD_SSL
    using asio::ssl::stream;
#endif

namespace restbed
{
    namespace detail
    {
        SocketImpl::SocketImpl( const shared_ptr< tcp::socket >& socket, const shared_ptr< Logger >& logger ) : m_is_open( socket->is_open( ) ),
            m_logger( logger ),
            m_timer( nullptr ),
            m_socket( socket )
#ifdef BUILD_SSL
            ,m_ssl_socket( nullptr )
#endif
        {
        	return;
        }
#ifdef BUILD_SSL
        SocketImpl::SocketImpl( const shared_ptr< asio::ssl::stream< tcp::socket > >& socket, const shared_ptr< Logger >& logger ) : m_is_open( socket->lowest_layer( ).is_open( ) ),
            m_logger( logger ),
            m_timer( nullptr ),
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
	    	return not is_closed( );
	    }
	    
	    bool SocketImpl::is_closed( void ) const
	    {
	    	if ( m_is_open )
	    	{
	    		return false;
	    	}

	    	if ( m_socket not_eq nullptr )
	    	{
	    		return not m_socket->is_open( );
	    	}
#ifdef BUILD_SSL
	    	if ( m_ssl_socket not_eq nullptr )
	    	{
	    		return not m_ssl_socket->lowest_layer( ).is_open( );
	    	}
#endif
	    	return true;
	    }

	    void SocketImpl::wait( const microseconds& delay, const function< void ( const error_code & ) >& callback )
	    {
#ifdef BUILD_SSL
	    	if ( m_socket not_eq nullptr )
	    	{
#endif
	    		m_timer = make_shared< asio::steady_timer >( m_socket->get_io_service( ) );
#ifdef BUILD_SSL
	    	}
	    	else
	    	{
	    		m_timer = make_shared< asio::steady_timer >( m_ssl_socket->lowest_layer( ).get_io_service( ) );
	    	}
#endif
            m_timer->expires_from_now( delay );
            m_timer->async_wait( callback );
	    }

        void SocketImpl::write( const Bytes& data, const function< void ( const asio::error_code&, size_t ) >& callback )
        {
#ifdef BUILD_SSL
        	if ( m_socket not_eq nullptr )
        	{
#endif
                asio::async_write( *m_socket, asio::buffer( data.data( ), data.size( ) ), callback );
#ifdef BUILD_SSL
            }
            else
            {
            	asio::async_write( *m_ssl_socket, asio::buffer( data.data( ), data.size( ) ), callback );
            }
#endif
        }

        void SocketImpl::read( const shared_ptr< asio::streambuf >& data, const size_t length, const function< void ( const asio::error_code&, size_t ) >& callback )
        {
#ifdef BUILD_SSL
        	if ( m_socket not_eq nullptr )
        	{
#endif
                asio::async_read( *m_socket, *data, asio::transfer_at_least( length ), callback );
#ifdef BUILD_SSL
        	}
        	else
        	{
        		asio::async_read( *m_ssl_socket, *data, asio::transfer_at_least( length ), callback );
        	}
#endif
        }

        void SocketImpl::read( const shared_ptr< asio::streambuf >& data, const string& delimiter, const function< void ( const asio::error_code&, size_t ) >& callback )
        {
#ifdef BUILD_SSL     	
        	if ( m_socket not_eq nullptr )
        	{
#endif
                asio::async_read_until( *m_socket, *data, delimiter, callback );
#ifdef BUILD_SSL 
        	}
        	else
        	{
        		asio::async_read_until( *m_ssl_socket, *data, delimiter, callback );
        	}
#endif
        }

        string SocketImpl::get_local_endpoint( void ) const
        {
        	tcp::endpoint endpoint;
#ifdef BUILD_SSL 
        	if ( m_socket not_eq nullptr )
        	{
#endif
        		endpoint = m_socket->local_endpoint( ); 
#ifdef BUILD_SSL
        	}
        	else
        	{
        		endpoint = m_ssl_socket->lowest_layer( ).local_endpoint( );
        	}
#endif
            auto address = endpoint.address( );
            auto local = address.is_v4( ) ? address.to_string( ) : "[" + address.to_string( ) + "]:";
            local += ::to_string( endpoint.port( ) );

            return local;
        }

        string SocketImpl::get_remote_endpoint( void ) const
        {
        	tcp::endpoint endpoint;
#ifdef BUILD_SSL 
        	if ( m_socket not_eq nullptr )
        	{
#endif
        		endpoint = m_socket->remote_endpoint( ); 
#ifdef BUILD_SSL
        	}
        	else
        	{
        		endpoint = m_ssl_socket->lowest_layer( ).remote_endpoint( );
        	}
#endif
            auto address = endpoint.address( );
            auto remote = address.is_v4( ) ? address.to_string( ) : "[" + address.to_string( ) + "]:";
            remote += ::to_string( endpoint.port( ) );

            return remote;
        }

        void SocketImpl::set_timeout( const seconds& value )
        {
        	tcp::socket::native_handle_type native_socket;
#ifdef BUILD_SSL 
        	if ( m_socket not_eq nullptr )
        	{
#endif
        		native_socket = m_socket->native_handle( );
#ifdef BUILD_SSL
        	}
        	else
        	{
        		native_socket = m_ssl_socket->lowest_layer( ).native_handle( );
        	}
#endif
            struct timeval timeout;
            timeout.tv_usec = 0;
            timeout.tv_sec = value.count( );
            
            int status = setsockopt( native_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast< char* >( &timeout ), sizeof( timeout ) );
            
            if ( status == -1 and m_logger not_eq nullptr )
            {
                m_logger->log( Logger::Level::WARNING, "Failed to set socket option, send timeout." );
            }
            
            status = setsockopt( native_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast< char* >( &timeout ), sizeof( timeout ) );
            
            if ( status == -1 and m_logger not_eq nullptr )
            {
                m_logger->log( Logger::Level::WARNING, "Failed to set socket option, receive timeout." );
            }
        }
    }
}
