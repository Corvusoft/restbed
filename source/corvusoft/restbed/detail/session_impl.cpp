/*
 * Copyright (c) 2013 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/detail/session_impl.h"

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    namespace detail
    {
        SessionImpl::SessionImpl( void )
        {
            //n/a
        }
        
        SessionImpl::SessionImpl( const SessionImpl& original )
        {
            //n/a
        }
        
        SessionImpl::~SessionImpl( void )
        {
            //n/a
        }

        bool SessionImpl::operator <( const SessionImpl& rhs ) const
        {
            return true;
        }
        
        bool SessionImpl::operator >( const SessionImpl& rhs ) const
        {
            return true;
        }
        
        bool SessionImpl::operator ==( const SessionImpl& rhs ) const
        {
            return true;        }
        
        bool SessionImpl::operator !=( const SessionImpl& rhs ) const
        {
            return true;
        }

        SessionImpl& SessionImpl::operator =( const SessionImpl& rhs )
        {
            return *this;
        }
    }
}
