/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/session.h"
#include "corvusoft/restbed/detail/session_impl.h"

//External Includes
#include <corvusoft/framework/unique_id>

//System Namespaces
using std::string;
using std::function;
using std::shared_ptr;
using std::make_shared;
using std::placeholders::_1;

//Project Namespaces
using restbed::detail::SessionImpl;

//External Namespaces
using asio::buffer;
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

        void SessionImpl::fetch( const function< void ( const shared_ptr< Session >& ) >& callback, const std::shared_ptr< Session >& session )
        {
            //just reset the buffer not a new alloc.
            m_buffer = make_shared< asio::streambuf >( );
            asio::async_read_until( *m_socket,
                                    *m_buffer,
                                    "\r\n\r\n",
                                    bind( &SessionImpl::parse_status_and_headers, this, callback, session, _1 ) );
        }

        const string& SessionImpl::get_id( void ) const
        {
            return m_id;
        }

        void SessionImpl::set_socket( const std::shared_ptr< tcp::socket >& value )
        {
            m_socket = value;
        }

        void SessionImpl::parse_status_and_headers( const function< void ( const shared_ptr< Session >& ) >& callback, const std::shared_ptr< Session >& session, const asio::error_code& error )
        {
            //if ( error )
            //{
            //    throw asio::system_error( code );
            //}

            //m_buffer has status/headers
            //m_request

            callback( session );
        }
    }
}
