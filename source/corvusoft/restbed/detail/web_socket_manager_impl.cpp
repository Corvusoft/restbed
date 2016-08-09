/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <ciso646>

//Project Includes
#include "corvusoft/restbed/logger.hpp"
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/web_socket.hpp"
#include "corvusoft/restbed/detail/request_impl.hpp"
#include "corvusoft/restbed/detail/session_impl.hpp"
#include "corvusoft/restbed/detail/web_socket_impl.hpp"
#include "corvusoft/restbed/detail/web_socket_manager_impl.hpp"

//External Includes

//System Namespaces
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using restbed::detail::WebSocketManagerImpl;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        WebSocketManagerImpl::WebSocketManagerImpl( const shared_ptr< Logger >& logger ) : m_logger( logger ),
            m_sockets( )
        {
            return;
        }
        
        WebSocketManagerImpl::~WebSocketManagerImpl( void )
        {
            return;
        }
        
        std::shared_ptr< WebSocket > WebSocketManagerImpl::create( const std::shared_ptr< Session >& session )
        {
            auto socket = make_shared< WebSocket >( );
            socket->m_pimpl->m_logger = m_logger;
            socket->m_pimpl->m_socket = session->m_pimpl->m_request->m_pimpl->m_socket;
            
            m_sockets.push_back( socket );
            
            return socket;
        }
    }
}
