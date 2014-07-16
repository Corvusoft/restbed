/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/method.h"
#include "corvusoft/restbed/detail/method_impl.h"

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
    
    Method::Method( const MethodImpl& implementation ) : m_pimpl( new MethodImpl( implementation ) )
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
    
    Method& Method::operator =( const Method& value )
    {
        *m_pimpl = *value.m_pimpl;
        
        return *this;
    }
    
    bool Method::operator <( const Method& value ) const
    {
        return *m_pimpl < *value.m_pimpl;
    }
    
    bool Method::operator >( const Method& value ) const
    {
        return *m_pimpl > *value.m_pimpl;
    }
    
    bool Method::operator ==( const Method& value ) const
    {
        return *m_pimpl == *value.m_pimpl;
    }
    
    bool Method::operator !=( const Method& value ) const
    {
        return *m_pimpl != *value.m_pimpl;
    }
    
    Method::Method( void ) : m_pimpl( nullptr )
    {
        //n/a
    }
}
