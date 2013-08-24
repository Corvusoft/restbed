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
#include "restbed/string.h"
#include "restbed/detail/settings_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::stoi;
using std::string;
using std::to_string;

//Project Namespaces

//External Namespaces

namespace restbed
{
    namespace detail
    {
        SettingsImpl::SettingsImpl( void ) : m_properties( )
        {
            m_properties[ "ROOT" ] = "/";
            m_properties[ "PORT" ] = "80";
        }
        
        SettingsImpl::SettingsImpl( const SettingsImpl& original ) : m_properties( original.m_properties )
        {
            //n/a
        }
        
        SettingsImpl::~SettingsImpl( void )
        {
            //n/a
        }

        uint16_t SettingsImpl::get_port( void ) const
        {
            return stoi( get_property( "PORT" ) );
        }

        string SettingsImpl::get_root( void ) const
        {
            return get_property( "ROOT" );
        }

        string SettingsImpl::get_property( const string& name ) const
        {
            string property = String::empty;

            const string key = String::to_upper( name );

            const auto& iterator = m_properties.find( key );

            if ( iterator not_eq m_properties.end( ) )
            {
                property = m_properties.at( key );
            }

            return property;
        }

        map< string, string > SettingsImpl::get_properties( void ) const
        {
            return m_properties;
        }

        void SettingsImpl::set_port( const uint16_t value )
        {
            set_property( "PORT", ::to_string( value ) );
        }
        
        void SettingsImpl::set_root( const string& value )
        {
            set_property( "ROOT", value );
        }
        
        void SettingsImpl::set_property( const string& name, const string& value )
        {
            const string key = String::to_upper( name );

            m_properties[ key ] = value;
        }
        
        void SettingsImpl::set_properties( const map< string, string >& values )
        {
            for ( const auto& value : values )
            {
                set_property( value.first, value.second );
            }
        }

        bool SettingsImpl::operator <( const SettingsImpl& rhs ) const
        {
            return m_properties.size( ) < rhs.m_properties.size( );
        }
        
        bool SettingsImpl::operator >( const SettingsImpl& rhs ) const
        {
            return m_properties.size( ) > rhs.m_properties.size( );
        }
        
        bool SettingsImpl::operator ==( const SettingsImpl& rhs ) const
        {
            return m_properties == rhs.m_properties;
        }
        
        bool SettingsImpl::operator !=( const SettingsImpl& rhs ) const
        {
            return m_properties not_eq rhs.m_properties;
        }

        SettingsImpl& SettingsImpl::operator =( const SettingsImpl& rhs )
        {
            m_properties = rhs.m_properties;

            return *this;
        }
    }
}
