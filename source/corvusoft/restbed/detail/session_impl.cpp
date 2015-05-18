/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/detail/session_impl.h"

//External Includes
#include <corvusoft/framework/unique_id>

//System Namespaces
using std::string;
using std::function;
using std::shared_ptr;

//Project Namespaces
using restbed::detail::SessionImpl;

//External Namespaces
using asio::ip::tcp;
using asio::error_code;
using framework::UniqueId;

namespace restbed
{
    namespace detail
    {
        SessionImpl::SessionImpl( void ) : m_id( UniqueId::generate( ).to_string( ) ),
            m_socket( nullptr )
        {
            return;
        }
        
        SessionImpl::~SessionImpl( void )
        {
            return;
        }

        void SessionImpl::fetch( const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            //asio::error_code code;
            //asio::streambuf* buffer = new asio::streambuf; //when is this deleted?
            //asio::async_read_until( *socket, *buffer, "\r\n\r\n", code, parse_status_and_headers );
            //if ( code )
            //{
            //    throw asio::system_error( code );
            //}
        }

        const string& SessionImpl::get_id( void ) const
        {
            return m_id;
        }

        void SessionImpl::set_socket( const std::shared_ptr< tcp::socket >& value )
        {
            m_socket = value;
        }
    }
}
