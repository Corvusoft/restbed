/*
 * Copyright (c) 2013 Corvusoft
 */

//System Includes

//Project Includes
#include "restbed/method.h"
#include "restbed/detail/method_impl.h"

//External Includes

//System Namespaces
using std::string;

//Project Namespaces
using restbed::detail::MethodImpl;

//External Namespaces

namespace restbed
{
    Method::Method( const char* value ) : m_pimpl( new MethodImpl( value ) )
    {
        //n/a
    }

    Method::Method( const string& value ) : m_pimpl( new MethodImpl( value ) )
    {
        //n/a
    }
    
    Method::Method( const Method& original ) : m_pimpl( new MethodImpl( *original.m_pimpl ) )
    {
        //n/a
    }
    
    Method::~Method( void )
    {
        //n/a
    }

    string Method::to_string( void ) const
    {
        return m_pimpl->to_string( );
    }
    
    Method Method::parse( const string& value )
    {
        Method method( value );
        
        return method;
    }

    Method& Method::operator =( const Method& rhs )
    {
        *m_pimpl = *rhs.m_pimpl;

        return *this;
    }

    bool Method::operator <( const Method& rhs ) const
    {
        return *m_pimpl < *rhs.m_pimpl;
    }
    
    bool Method::operator >( const Method& rhs ) const
    {
        return *m_pimpl > *rhs.m_pimpl;
    }
    
    bool Method::operator ==( const Method& rhs ) const
    {
        return *m_pimpl == *rhs.m_pimpl;
    }
    
    bool Method::operator !=( const Method& rhs ) const
    {
        return *m_pimpl != *rhs.m_pimpl;
    }
    
    Method::Method( void ) : m_pimpl( nullptr )
    {
        //n/a
    }
}
