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
#include "restbed/detail/helpers/string.h"
#include "restbed/detail/resource_settings_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::string;

//Project Namespaces
using restbed::detail::helpers::String;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        ResourceSettingsImpl::ResourceSettingsImpl( void ) : m_properties( )
        {
            //n/a
        }
        
        ResourceSettingsImpl::ResourceSettingsImpl( const ResourceSettingsImpl& original ) : m_properties( original.m_properties )
        {
            //n/a
        }
        
        ResourceSettingsImpl::~ResourceSettingsImpl( void )
        {
            //n/a
        }

        string ResourceSettingsImpl::get_property( const string& name ) const
        {
            string property = String::empty;

            const string key = String::uppercase( name );

            const auto& iterator = m_properties.find( key );

            if ( iterator not_eq m_properties.end( ) )
            {
                property = m_properties.at( key );
            }

            return property;
        }

        map< string, string > ResourceSettingsImpl::get_properties( void ) const
        {
            return m_properties;
        }
        
        void ResourceSettingsImpl::set_property( const string& name, const string& value )
        {
            const string key = String::uppercase( name );

            m_properties[ key ] = value;
        }
        
        void ResourceSettingsImpl::set_properties( const map< string, string >& values )
        {
            for ( const auto& value : values )
            {
                set_property( value.first, value.second );
            }
        }

        bool ResourceSettingsImpl::operator <( const ResourceSettingsImpl& rhs ) const
        {
            return m_properties.size( ) < rhs.m_properties.size( );
        }
        
        bool ResourceSettingsImpl::operator >( const ResourceSettingsImpl& rhs ) const
        {
            return m_properties.size( ) > rhs.m_properties.size( );
        }
        
        bool ResourceSettingsImpl::operator ==( const ResourceSettingsImpl& rhs ) const
        {
            return m_properties == rhs.m_properties;
        }
        
        bool ResourceSettingsImpl::operator !=( const ResourceSettingsImpl& rhs ) const
        {
            return m_properties not_eq rhs.m_properties;
        }

        ResourceSettingsImpl& ResourceSettingsImpl::operator =( const ResourceSettingsImpl& rhs )
        {
            m_properties = rhs.m_properties;

            return *this;
        }
    }
}
