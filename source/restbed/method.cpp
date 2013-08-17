/*
 * Site: restbed.net
 * Author: Ben Crowhurst
 *
 * Copyright (c) 2013 Restbed Core Development Team and Community Contributors
 *
 * This file is part of Restbed.
 *
 * AppOn is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AppOn is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with AppOn.  If not, see <http://www.gnu.org/licenses/>.
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
