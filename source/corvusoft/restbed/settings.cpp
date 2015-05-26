/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/settings.h"
#include "corvusoft/restbed/detail/settings_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::string;
using std::multimap;
using std::chrono::seconds;

//Project Namespaces
using restbed::detail::SettingsImpl;

//External Namespaces

namespace restbed
{
    Settings::Settings( void ) : m_pimpl( new SettingsImpl )
    {
        return;
    }
    
    Settings::~Settings( void )
    {
        return;
    }
    
    uint16_t Settings::get_port( void ) const
    {
        return m_pimpl->get_port( );
    }
    
    string Settings::get_root( void ) const
    {
        return m_pimpl->get_root( );
    }
    
    int32_t Settings::get_connection_limit( void ) const
    {
        return m_pimpl->get_connection_limit( );
    }

    seconds Settings::get_connection_timeout( void ) const
    {
        return m_pimpl->get_connection_timeout( );
    }

    string Settings::get_property( const string& name ) const
    {
        return m_pimpl->get_property( name );
    }
    
    map< string, string > Settings::get_properties( void ) const
    {
        return m_pimpl->get_properties( );
    }

    multimap< string, string > Settings::get_default_headers( void ) const
    {
        return m_pimpl->get_default_headers( );
    }

    void Settings::set_port( const uint16_t value )
    {
        m_pimpl->set_port( value );
    }
    
    void Settings::set_root( const string& value )
    {
        m_pimpl->set_root( value );
    }
    
    void Settings::set_connection_limit( const int32_t value )
    {
        m_pimpl->set_connection_limit( value );
    }

    void Settings::set_connection_timeout( const seconds& value )
    {
        m_pimpl->set_connection_timeout( value );
    }

    void Settings::set_property( const string& name, const string& value )
    {
        m_pimpl->set_property( name, value );
    }
    
    void Settings::set_properties( const map< string, string >& values )
    {
        m_pimpl->set_properties( values );
    }

    void Settings::set_default_header( const string& name, const string& value )
    {
        m_pimpl->set_default_header( name, value );
    }

    void Settings::set_default_headers( const multimap< string, string >& values )
    {
        m_pimpl->set_default_headers( values );
    }
}
