/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/detail/session_impl.h"
#include "corvusoft/restbed/detail/session_builder_impl.h"

//External Includes

//System Namespaces
using std::string;
using std::shared_ptr;

//Project Namespaces

//External Namespaces
using asio::ip::tcp;

namespace restbed
{
    namespace detail
    {
        SessionBuilderImpl::SessionBuilderImpl( const string& id ) : Session( id )
        {
            return;
        }
        
        SessionBuilderImpl::~SessionBuilderImpl( void )
        {
            return;
        }
        
        void SessionBuilderImpl::set_socket( const shared_ptr< tcp::socket >& socket )
        {
            m_pimpl->set_socket( socket );
        }
    }
}
