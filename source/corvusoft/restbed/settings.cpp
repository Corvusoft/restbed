/*
 * Copyright (c) 2013 Corvusoft
 */

//System Includes

//Project Includes
#include "restbed/settings.h"
#include "restbed/detail/settings_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::string;

//Project Namespaces
using restbed::detail::SettingsImpl;

//External Namespaces

namespace restbed
{
    Settings::Settings( void ) : m_pimpl( new SettingsImpl )
    {
        //n/a
    }
    
    Settings::Settings( const Settings& original ) : m_pimpl( new SettingsImpl( *original.m_pimpl ) )
    {
        //n/a
    }
    
    Settings::~Settings( void )
    {
        //n/a
    }

    uint16_t Settings::get_port( void ) const
    {
        return m_pimpl->get_port( );
    }

    string Settings::get_root( void ) const
    {
        return m_pimpl->get_root( );
    }

    string Settings::get_property( const string& name ) const
    {
        return m_pimpl->get_property( name );
    }

    map< string, string > Settings::get_properties( void ) const
    {
        return m_pimpl->get_properties( );
    }

    void Settings::set_port( const uint16_t value )
    {
        m_pimpl->set_port( value );
    }
    
    void Settings::set_root( const string& value )
    {
        m_pimpl->set_root( value );
    }
    
    void Settings::set_property( const string& name, const string& value )
    {
    	m_pimpl->set_property( name, value );
    }
    
    void Settings::set_properties( const map< string, string >& values )
    {
        m_pimpl->set_properties( values );
    }

    Settings& Settings::operator =( const Settings& rhs )
    {
        *m_pimpl = *rhs.m_pimpl;

        return *this;
    }

    bool Settings::operator <( const Settings& rhs ) const
    {
        return *m_pimpl < *rhs.m_pimpl;
    }
    
    bool Settings::operator >( const Settings& rhs ) const
    {
        return *m_pimpl > *rhs.m_pimpl;
    }
    
    bool Settings::operator ==( const Settings& rhs ) const
    {
        return *m_pimpl == *rhs.m_pimpl;
    }
    
    bool Settings::operator !=( const Settings& rhs ) const
    {
        return *m_pimpl != *rhs.m_pimpl;
    }
}
