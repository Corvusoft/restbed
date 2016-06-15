/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/settings.hpp"
#include "corvusoft/restbed/detail/settings_impl.hpp"

//External Includes

//System Namespaces
using std::map;
using std::string;
using std::multimap;
using std::make_pair;
using std::unique_ptr;
using std::shared_ptr;
using std::chrono::seconds;
using std::chrono::milliseconds;
using std::chrono::duration_cast;

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
        return m_pimpl->m_port;
    }
    
    string Settings::get_root( void ) const
    {
        return m_pimpl->m_root;
    }
    
    unsigned int Settings::get_worker_limit( void ) const
    {
        return m_pimpl->m_worker_limit;
    }
    
    unsigned int Settings::get_connection_limit( void ) const
    {
        return m_pimpl->m_connection_limit;
    }
    
    string Settings::get_bind_address( void ) const
    {
        return m_pimpl->m_bind_address;
    }
    
    bool Settings::get_case_insensitive_uris( void ) const
    {
        return m_pimpl->m_case_insensitive_uris;
    }
    
    milliseconds Settings::get_connection_timeout( void ) const
    {
        return m_pimpl->m_connection_timeout;
    }
    
    string Settings::get_status_message( const int code ) const
    {
        return ( m_pimpl->m_status_messages.count( code ) ) ?  m_pimpl->m_status_messages.at( code ) : "No Appropriate Status Message Found";
    }
    
    map< int, string > Settings::get_status_messages( void ) const
    {
        return m_pimpl->m_status_messages;
    }
    
    string Settings::get_property( const string& name ) const
    {
        return ( m_pimpl->m_properties.count( name ) ) ? m_pimpl->m_properties.at( name ) : "";
    }
    
    map< string, string > Settings::get_properties( void ) const
    {
        return m_pimpl->m_properties;
    }
    
    shared_ptr< const SSLSettings > Settings::get_ssl_settings( void ) const
    {
        return m_pimpl->m_ssl_settings;
    }
    
    multimap< string, string > Settings::get_default_headers( void ) const
    {
        return m_pimpl->m_default_headers;
    }
    
    void Settings::set_port( const uint16_t value )
    {
        m_pimpl->m_port = value;
    }
    
    void Settings::set_root( const string& value )
    {
        m_pimpl->m_root = value;
    }
    
    void Settings::set_worker_limit( const unsigned int value )
    {
        m_pimpl->m_worker_limit = value;
    }
    
    void Settings::set_connection_limit( const unsigned int value )
    {
        m_pimpl->m_connection_limit = value;
    }
    
    void Settings::set_bind_address( const string& value )
    {
        m_pimpl->m_bind_address = value;
    }
    
    void Settings::set_case_insensitive_uris( const bool value )
    {
        m_pimpl->m_case_insensitive_uris = value;
    }
    
    void Settings::set_connection_timeout( const seconds& value )
    {
        m_pimpl->m_connection_timeout = duration_cast< milliseconds >( value );
    }
    
    void Settings::set_connection_timeout( const milliseconds& value )
    {
        m_pimpl->m_connection_timeout = value;
    }
    
    void Settings::set_status_message( const int code, const string& message )
    {
        m_pimpl->m_status_messages[ code ] = message;
    }
    
    void Settings::set_status_messages( const map< int, string >& values )
    {
        m_pimpl->m_status_messages = values;
    }
    
    void Settings::set_property( const string& name, const string& value )
    {
        m_pimpl->m_properties[ name ] = value;
    }
    
    void Settings::set_properties( const map< string, string >& values )
    {
        m_pimpl->m_properties = values;
    }
    
    void Settings::set_ssl_settings( const shared_ptr< const SSLSettings >& values )
    {
        m_pimpl->m_ssl_settings = values;
    }
    
    void Settings::set_default_header( const string& name, const string& value )
    {
        m_pimpl->m_default_headers.insert( make_pair( name, value ) );
    }
    
    void Settings::set_default_headers( const multimap< string, string >& values )
    {
        m_pimpl->m_default_headers = values;
    }
}
