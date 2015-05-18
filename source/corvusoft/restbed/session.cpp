/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/session.h"
#include "corvusoft/restbed/detail/session_impl.h"

//External Includes

//System Namespaces
using std::string;
using std::function;
using std::shared_ptr;

//Project Namespaces
using restbed::detail::SessionImpl;

//External Namespaces

namespace restbed
{
    Session::Session( void ) : m_pimpl( new SessionImpl )
    {
        return;
    }
    
    Session::~Session( void )
    {
        return;
    }

    void Session::fetch( const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->fetch( callback, shared_ptr< Session >( this ) );
    }

    string Session::get_id( void ) const
    {
        return m_pimpl->get_id( );
    }
}
