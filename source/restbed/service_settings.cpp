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
#include "restbed/service_settings.h"
#include "restbed/detail/service_settings_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::string;

//Project Namespaces
using restbed::detail::ServiceSettingsImpl;

//External Namespaces

namespace restbed
{
    ServiceSettings::ServiceSettings( void ) : m_pimpl( new ServiceSettingsImpl )
    {
        //n/a
    }
    
    ServiceSettings::ServiceSettings( const ServiceSettings& original ) : m_pimpl( new ServiceSettingsImpl( *original.m_pimpl ) )
    {
        //n/a
    }
    
    ServiceSettings::~ServiceSettings( void )
    {
        //n/a
    }

    uint16_t ServiceSettings::get_port( void ) const
    {
        return m_pimpl->get_port( );
    }

    string ServiceSettings::get_root( void ) const
    {
        return m_pimpl->get_root( );
    }

    void ServiceSettings::set_port( const uint16_t value )
    {
        m_pimpl->set_port( value );
    }
    
    void ServiceSettings::set_root( const string& value )
    {
        m_pimpl->set_root( value );
    }

    bool ServiceSettings::operator <( const ServiceSettings& rhs ) const
    {
        return *m_pimpl < *rhs.m_pimpl;
    }
    
    bool ServiceSettings::operator >( const ServiceSettings& rhs ) const
    {
        return *m_pimpl > *rhs.m_pimpl;
    }
    
    bool ServiceSettings::operator ==( const ServiceSettings& rhs ) const
    {
        return *m_pimpl == *rhs.m_pimpl;
    }
    
    bool ServiceSettings::operator !=( const ServiceSettings& rhs ) const
    {
        return *m_pimpl != *rhs.m_pimpl;
    }

    ServiceSettings& ServiceSettings::operator =( const ServiceSettings& rhs )
    {
        *m_pimpl = *rhs.m_pimpl;

        return *this;
    }
}
