/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/mode.h"
#include "corvusoft/restbed/settings.h"
#include "corvusoft/restbed/detail/settings_impl.h"

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
    
    Settings::Settings( const SettingsImpl& implementation ) : m_pimpl( new SettingsImpl( implementation ) )
    {
        //n/a
    }
    
    Settings::~Settings( void )
    {
        //n/a
    }
    
    Mode Settings::get_mode( void ) const
    {
        return m_pimpl->get_mode( );
    }
    
    uint16_t Settings::get_port( void ) const
    {
        return m_pimpl->get_port( );
    }
    
    string Settings::get_root( void ) const
    {
        return m_pimpl->get_root( );
    }
    
    int Settings::get_maximum_connections( void ) const
    {
        return m_pimpl->get_maximum_connections( );
    }
    
    string Settings::get_property( const string& name ) const
    {
        return m_pimpl->get_property( name );
    }
    
    map< string, string > Settings::get_properties( void ) const
    {
        return m_pimpl->get_properties( );
    }
    
    void Settings::set_mode( const Mode value )
    {
        m_pimpl->set_mode( value );
    }
    
    void Settings::set_port( const uint16_t value )
    {
        m_pimpl->set_port( value );
    }
    
    void Settings::set_root( const string& value )
    {
        m_pimpl->set_root( value );
    }
    
    void Settings::set_maximum_connections( const int value )
    {
        m_pimpl->set_maximum_connections( value );
    }
    
    void Settings::set_property( const string& name, const string& value )
    {
        m_pimpl->set_property( name, value );
    }
    
    void Settings::set_properties( const map< string, string >& values )
    {
        m_pimpl->set_properties( values );
    }
    
    Settings& Settings::operator =( const Settings& value )
    {
        *m_pimpl = *value.m_pimpl;
        
        return *this;
    }
}
