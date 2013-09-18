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
#include "restbed/resource_settings.h"
#include "restbed/detail/resource_settings_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::string;

//Project Namespaces
using restbed::detail::ResourceSettingsImpl;

//External Namespaces

namespace restbed
{
    ResourceSettings::ResourceSettings( void ) : m_pimpl( new ResourceSettingsImpl )
    {
        //n/a
    }
    
    ResourceSettings::ResourceSettings( const ResourceSettings& original ) : m_pimpl( new ResourceSettingsImpl( *original.m_pimpl ) )
    {
        //n/a
    }
    
    ResourceSettings::~ResourceSettings( void )
    {
        //n/a
    }

    string ResourceSettings::get_property( const string& name ) const
    {
        return m_pimpl->get_property( name );
    }

    map< string, string > ResourceSettings::get_properties( void ) const
    {
        return m_pimpl->get_properties( );
    }
    
    void ResourceSettings::set_property( const string& name, const string& value )
    {
    	m_pimpl->set_property( name, value );
    }
    
    void ResourceSettings::set_properties( const map< string, string >& values )
    {
        m_pimpl->set_properties( values );
    }

    bool ResourceSettings::operator <( const ResourceSettings& rhs ) const
    {
        return *m_pimpl < *rhs.m_pimpl;
    }
    
    bool ResourceSettings::operator >( const ResourceSettings& rhs ) const
    {
        return *m_pimpl > *rhs.m_pimpl;
    }
    
    bool ResourceSettings::operator ==( const ResourceSettings& rhs ) const
    {
        return *m_pimpl == *rhs.m_pimpl;
    }
    
    bool ResourceSettings::operator !=( const ResourceSettings& rhs ) const
    {
        return *m_pimpl != *rhs.m_pimpl;
    }

    ResourceSettings& ResourceSettings::operator =( const ResourceSettings& rhs )
    {
        *m_pimpl = *rhs.m_pimpl;

        return *this;
    }
}
