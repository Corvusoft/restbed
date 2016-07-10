/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include <corvusoft/restbed/uri.hpp>
#include <corvusoft/restbed/response.hpp>
#include <corvusoft/restbed/detail/socket_impl.hpp>
#include <corvusoft/restbed/detail/request_impl.hpp>

//External Includes

//System Namespaces

//Project Namespaces
using restbed::detail::RequestImpl;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        RequestImpl::RequestImpl( void ) : m_body( ),
            m_port( 80 ),
            m_version( 1.1 ),
            m_host( "" ),
            m_path( "/" ),
            m_method( "GET" ),
            m_protocol( "HTTP" ),
            m_uri( nullptr ),
            m_response( nullptr ),
            m_headers( ),
            m_path_parameters( ),
            m_query_parameters( ),
            m_io_service( nullptr ),
            m_socket( nullptr ),
            m_buffer( nullptr )
        {
            return;
        }
        
        RequestImpl::~RequestImpl( void )
        {
            return;
        }
        
    }
}
