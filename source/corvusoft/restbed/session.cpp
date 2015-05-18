/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/session.h"
#include "corvusoft/restbed/detail/session_impl.h"

//External Includes

//System Namespaces
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
    
    Session::Session( const Session& original ) : m_pimpl( new SessionImpl( *original.m_pimpl ) )
    {
        return;
    }
    
    Session::~Session( void )
    {
        return;
    }

    Session& Session::operator =( const Session& value )
    {
        *m_pimpl = *value.m_pimpl;
        
        return *this;
    }
}
