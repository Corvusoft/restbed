/*
 * Site: restbed.corvusoft.co.uk
 * Author: Ben Crowhurst
 *
 * Copyright (c) 2013 Restbed Core Development Team and Community Contributors
 *
 * This file is part of Restbed.
 *
 * Restbed is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Restbed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with Restbed.  If not, see <http://www.gnu.org/licenses/>.
 */

//System Includes

//Project Includes
#include "restbed/resource_matcher.h"
#include "restbed/detail/resource_matcher_impl.h"

//External Includes

//System Namespaces
using std::string;

//Project Namespaces
using restbed::detail::ResourceMatcherImpl;

//External Namespaces

namespace restbed
{
    ResourceMatcher::ResourceMatcher( const Request& request ) : m_pimpl( new ResourceMatcherImpl( request ) )
    {
        //n/a
    }
    
    ResourceMatcher::ResourceMatcher( const ResourceMatcher& original ) : m_pimpl( new ResourceMatcherImpl( *original.m_pimpl ) )
    {
        //n/a
    }
    
    ResourceMatcher::~ResourceMatcher( void )
    {
        //n/a
    }

    bool ResourceMatcher::operator ( )( const Resource& resource ) const
    {
        return (*m_pimpl)( resource );
    }
}
