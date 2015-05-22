/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <regex>
#include <utility>
#include <stdexcept>
#include <iostream> //debug

//Project Includes
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/session.h"
#include "corvusoft/restbed/detail/session_impl.h"
#include "corvusoft/restbed/detail/session_builder_impl.h"
#include "corvusoft/restbed/detail/request_builder_impl.h"

//External Includes
#include <corvusoft/framework/uri>
#include <corvusoft/framework/string>

//System Namespaces
using std::map;
using std::regex;
using std::smatch;
using std::string;
using std::getline;
using std::istream;
using std::function;
using std::multimap;
using std::make_pair;
using std::ssub_match;
using std::shared_ptr;
using std::make_shared;
using std::regex_match;
using std::runtime_error;
using std::placeholders::_1;

//Project Namespaces
using restbed::detail::SessionImpl;

//External Namespaces
using asio::buffer;
using asio::ip::tcp;
using asio::error_code;
using framework::Uri;
using framework::String;

namespace restbed
{
    namespace detail
    {
        SessionImpl::SessionImpl( void ) : m_id( String::empty ),
            m_request( nullptr ),
            m_buffer( nullptr ),
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
            m_buffer = make_shared< asio::streambuf >( ); //pass as argument!

            asio::async_read_until( *m_socket,
                                    *m_buffer,
                                    "\r\n\r\n",
                                    bind( &SessionImpl::parse_request, this, callback, session, _1 ) );
        }

        const string& SessionImpl::get_id( void ) const
        {
            return m_id;
        }

        void SessionImpl::set_id( const string& value )
        {
            m_id = value;
        }

        void SessionImpl::set_request( const shared_ptr< Request >& value )
        {
            m_request = value;
        }

        void SessionImpl::set_socket( const std::shared_ptr< tcp::socket >& value )
        {
            m_socket = value;
        }

        void SessionImpl::parse_request( const function< void ( const shared_ptr< Session >& ) >& callback, const std::shared_ptr< Session >& session, const asio::error_code& error )
        {
            if ( error )
            {
                throw runtime_error( "" ); //throw asio::system_error( code );
            }

            istream stream( m_buffer.get( ) );
            const auto request = make_shared< RequestBuilderImpl >( stream );

            auto builder = std::dynamic_pointer_cast< SessionBuilderImpl >( session );
            builder->set_request( request );

            callback( builder );
        }
    }
}
