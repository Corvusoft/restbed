/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/detail/session_impl.h"

//External Includes

//System Namespaces

//Project Namespaces
using restbed::detail::SessionImpl;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        SessionImpl::SessionImpl( void )
        {
            return;
        }
        
        SessionImpl::SessionImpl( const SessionImpl& original )
        {
            return;
        }
        
        SessionImpl::~SessionImpl( void )
        {
            return;
        }

        SessionImpl& SessionImpl::operator =( const SessionImpl& value )
        {            
            return *this;
        }
    }
}
