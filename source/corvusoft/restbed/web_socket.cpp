/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <ciso646>

//Project Includes
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/web_socket.hpp"
#include "corvusoft/restbed/web_socket_message.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"
#include "corvusoft/restbed/detail/web_socket_impl.hpp"
#include "corvusoft/restbed/detail/web_socket_manager_impl.hpp"

//External Includes

//System Namespaces
using std::bind;
using std::string;
using std::function;
using std::error_code;
using std::shared_ptr;
using std::make_shared;
using std::placeholders::_1;

//Project Namespaces
using restbed::detail::SocketImpl;
using restbed::detail::WebSocketImpl;
using restbed::detail::WebSocketManagerImpl;

//External Namespaces

namespace restbed
{
    WebSocket::WebSocket( void ) : m_pimpl( new WebSocketImpl )
    {
        return;
    }

    WebSocket::~WebSocket( void )
    {
        try
        {
            close( );
        }
        catch ( ... )
        {
            //m_logger->log( failure );
        }
    }

    bool WebSocket::is_open( void ) const
    {
        return m_pimpl->m_socket not_eq nullptr and m_pimpl->m_socket->is_open( );
    }

    bool WebSocket::is_closed( void ) const
    {
        return m_pimpl->m_socket not_eq nullptr and m_pimpl->m_socket->is_closed( );
    }

    void WebSocket::close( void )
    {
        m_pimpl->m_manager->destroy( shared_from_this( ) );
        m_pimpl->m_socket->close( ); //test status before invocation.
    }

    void WebSocket::send( const shared_ptr< WebSocketMessage > message, const function< void ( const shared_ptr< WebSocket > ) > callback )
    {
        const auto data = m_pimpl->m_manager->to_bytes( message );

        m_pimpl->m_socket->write( data, [ this, callback ]( const error_code & code, size_t )
        {
            if ( code )
            {
                if ( m_pimpl->m_error_handler not_eq nullptr  )
                {
                    m_pimpl->m_error_handler( shared_from_this( ), code );
                }

                return;
            }

            if ( callback not_eq nullptr )
            {
                callback( shared_from_this( ) );
            }
        } );
    }

    string WebSocket::get_key( void ) const
    {
        return m_pimpl->m_key;
    }

    shared_ptr< Logger > WebSocket::get_logger( void ) const
    {
        return m_pimpl->m_logger;
    }

    shared_ptr< SocketImpl > WebSocket::get_socket( void ) const
    {
        return m_pimpl->m_socket;
    }

    shared_ptr< WebSocketManagerImpl > WebSocket::get_manager( void ) const
    {
        return m_pimpl->m_manager;
    }

    function< void ( const shared_ptr< WebSocket > ) > WebSocket::get_open_handler( void ) const
    {
        return m_pimpl->m_open_handler;
    }

    function< void ( const shared_ptr< WebSocket > ) > WebSocket::get_close_handler( void ) const
    {
        return m_pimpl->m_close_handler;
    }

    function< void ( const shared_ptr< WebSocket >, const error_code ) > WebSocket::get_error_handler( void ) const
    {
        return m_pimpl->m_error_handler;
    }

    function< void ( const shared_ptr< WebSocket >, const shared_ptr< WebSocketMessage > ) > WebSocket::get_message_handler( void ) const
    {
        return m_pimpl->m_message_handler;
    }

    void WebSocket::set_key( const string& value )
    {
        m_pimpl->m_key = value;
    }

    void WebSocket::set_logger( const shared_ptr< Logger >& value )
    {
        m_pimpl->m_logger = value;
    }

    void WebSocket::set_socket( const shared_ptr< SocketImpl >& value )
    {
        m_pimpl->m_socket = value;
    }

    void WebSocket::set_manager( const shared_ptr< WebSocketManagerImpl >& value )
    {
        m_pimpl->m_manager = value;
    }

    void WebSocket::set_open_handler( const function< void ( const shared_ptr< WebSocket > ) >& value )
    {
        m_pimpl->m_open_handler = value;
    }

    void WebSocket::set_close_handler( const function< void ( const shared_ptr< WebSocket > ) >& value )
    {
        //we need to remove the socket from the manager!
        //wrap the close handler.
        m_pimpl->m_close_handler = bind( value, shared_from_this( ) );
    }

    void WebSocket::set_error_handler( const function< void ( const shared_ptr< WebSocket >, const error_code ) >& value )
    {
        m_pimpl->m_error_handler = [ value, this ]( const shared_ptr< WebSocket > socket, const error_code code )
        {
            if ( m_pimpl->m_error_handler_invoked == false )
            {
                value( socket, code );
            }
        };
    }

    void WebSocket::set_message_handler( const function< void ( const shared_ptr< WebSocket >, const shared_ptr< WebSocketMessage > ) >& value )
    {
        m_pimpl->m_message_handler = value;
        m_pimpl->m_manager->listen( shared_from_this( ) );
    }
}
