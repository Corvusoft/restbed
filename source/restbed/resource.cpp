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
#include "restbed/request.h"
#include "restbed/response.h"
#include "restbed/resource.h"
#include "restbed/detail/resource_impl.h"

//External Includes

//System Namespaces
using std::string;
using std::function;

//Project Namespaces
using restbed::detail::ResourceImpl;

//External Namespaces

namespace restbed
{
    Resource::Resource( void ) : m_pimpl( new ResourceImpl )
    {
        //n/a
    }
    
    Resource::Resource( const Resource& original ) : m_pimpl( new ResourceImpl( *original.m_pimpl ) )
    {
        //n/a
    }
    
    Resource::~Resource( void )
    {
        //n/a
    }

    string Resource::get_path( void ) const
    {
        return m_pimpl->get_path( );
    }
    
    string Resource::get_content_type( void ) const
    {
        return m_pimpl->get_content_type( );
    }

    function< Response ( Request& ) > Resource::get_method_handler( const Method& method ) const
    {
        return m_pimpl->get_method_handler( method );
    }

    void Resource::set_path( const string& value )
    {
        m_pimpl->set_path( value );
    }

    void Resource::set_content_type( const string& value )
    {
        m_pimpl->set_content_type( value );
    }

    void Resource::set_method_handler( const Method& method, const function< Response ( Request& ) >& callback )
    {
        m_pimpl->set_method_handler( method, callback );
    }

    bool Resource::operator <( const Resource& rhs ) const
    {
        return *m_pimpl < *rhs.m_pimpl;
    }
    
    bool Resource::operator >( const Resource& rhs ) const
    {
        return *m_pimpl > *rhs.m_pimpl;
    }
    
    bool Resource::operator ==( const Resource& rhs ) const
    {
        return *m_pimpl == *rhs.m_pimpl;
    }
    
    bool Resource::operator !=( const Resource& rhs ) const
    {
        return *m_pimpl != *rhs.m_pimpl;
    }

    Resource& Resource::operator =( const Resource& rhs )
    {
        *m_pimpl = *rhs.m_pimpl;

        return *this;
    }
}
