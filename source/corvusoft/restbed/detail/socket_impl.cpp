/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/detail/socket_impl.hpp"

//External Includes


//System Namespaces
using std::size_t;
using std::string;
using std::function;
using std::to_string;
using std::shared_ptr;
using std::make_shared;
using std::chrono::microseconds;

//Project Namespaces
using restbed::detail::SocketImpl;

//External Namespaces
using asio::ip::tcp;
using asio::error_code;
using asio::ssl::stream;
using asio::steady_timer;
using framework::Bytes;

namespace restbed
{
    namespace detail
    {
        SocketImpl::SocketImpl( const shared_ptr< tcp::socket >& socket ) : m_is_open( socket->is_open( ) ),
            m_timer( nullptr ),
            m_socket( socket ),
            m_ssl_socket( nullptr )
        {
        	return;
        }

        SocketImpl::SocketImpl( const shared_ptr< asio::ssl::stream< tcp::socket > >& socket ) : m_is_open( socket->lowest_layer( ).is_open( ) ),
            m_timer( nullptr ),
            m_socket( nullptr ),
            m_ssl_socket( socket )
        {
        	return;
        }

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

	    	if ( m_ssl_socket not_eq nullptr )
	    	{
	    		m_ssl_socket->lowest_layer( ).close( );
	    	}
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

	    	return ( m_socket == nullptr or not m_socket->is_open( ) ) and ( m_ssl_socket == nullptr or not m_ssl_socket->lowest_layer( ).is_open( ) );
	    }

	    void SocketImpl::wait( const microseconds& delay, const function< void ( const error_code & ) >& callback )
	    {
	    	if ( m_socket not_eq nullptr )
	    	{
	    		m_timer = make_shared< asio::steady_timer >( m_socket->get_io_service( ) );
	    	}
	    	else
	    	{
	    		m_timer = make_shared< asio::steady_timer >( m_ssl_socket->lowest_layer( ).get_io_service( ) );
	    	}

            m_timer->expires_from_now( delay );
            m_timer->async_wait( callback );
	    }

        void SocketImpl::write( const Bytes& data, const function< void ( const asio::error_code&, size_t ) >& callback )
        {
        	if ( m_socket not_eq nullptr )
        	{
                asio::async_write( *m_socket, asio::buffer( data.data( ), data.size( ) ), callback );
            }
            else
            {
            	asio::async_write( *m_ssl_socket, asio::buffer( data.data( ), data.size( ) ), callback );
            }
        }

        void SocketImpl::read( const shared_ptr< asio::streambuf >& data, const size_t length, const function< void ( const asio::error_code&, size_t ) >& callback )
        {
        	if ( m_socket not_eq nullptr )
        	{
                asio::async_read( *m_socket, *data, asio::transfer_at_least( length ), callback );
        	}
        	else
        	{
        		asio::async_read( *m_ssl_socket, *data, asio::transfer_at_least( length ), callback );
        	}
        }

        void SocketImpl::read( const shared_ptr< asio::streambuf >& data, const string& delimiter, const function< void ( const asio::error_code&, size_t ) >& callback )
        {
        	if ( m_socket not_eq nullptr )
        	{
                asio::async_read_until( *m_socket, *data, delimiter, callback );
        	}
        	else
        	{
        		asio::async_read_until( *m_ssl_socket, *data, delimiter, callback );
        	}
        }

        string SocketImpl::get_local_endpoint( void ) const
        {
        	tcp::endpoint endpoint;

        	if ( m_socket not_eq nullptr )
        	{
        		endpoint = m_socket->local_endpoint( ); 
        	}
        	else
        	{
        		endpoint = m_ssl_socket->lowest_layer( ).local_endpoint( );
        	}

            auto address = endpoint.address( );
            auto local = address.is_v4( ) ? address.to_string( ) : "[" + address.to_string( ) + "]:";
            local += ::to_string( endpoint.port( ) );

            return local;
        }

        string SocketImpl::get_remote_endpoint( void ) const
        {
        	tcp::endpoint endpoint;

        	if ( m_socket not_eq nullptr )
        	{
        		endpoint = m_socket->remote_endpoint( ); 
        	}
        	else
        	{
        		endpoint = m_ssl_socket->lowest_layer( ).remote_endpoint( );
        	}

            auto address = endpoint.address( );
            auto remote = address.is_v4( ) ? address.to_string( ) : "[" + address.to_string( ) + "]:";
            remote += ::to_string( endpoint.port( ) );

            return remote;
        }
    }
}
