/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
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
using std::shared_ptr;
using std::chrono::milliseconds;

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
        delete m_pimpl;
    }
    
    uint16_t Settings::get_port( void ) const
    {
        return m_pimpl->port;
    }
    
    string Settings::get_root( void ) const
    {
        return m_pimpl->root;
    }
    
    int32_t Settings::get_connection_limit( void ) const
    {
        return m_pimpl->connection_limit;
    }
    
    bool Settings::get_case_insensitive_uris( void ) const
    {
        return m_pimpl->case_insensitive_uris;
    }
    
    milliseconds Settings::get_connection_timeout( void ) const
    {
        return m_pimpl->connection_timeout;
    }
    
    string Settings::get_status_message( const int code ) const
    {
        return ( m_pimpl->status_messages.count( code ) ) ?  m_pimpl->status_messages.at( code ) : "No Appropriate Status Message Found";
    }
    
    map< int, string > Settings::get_status_messages( void ) const
    {
        return m_pimpl->status_messages;
    }
    
    string Settings::get_property( const string& name ) const
    {
        return ( m_pimpl->properties.count( name ) ) ? m_pimpl->properties.at( name ) : "";
    }
    
    map< string, string > Settings::get_properties( void ) const
    {
        return m_pimpl->properties;
    }
#ifdef BUILD_SSL
    shared_ptr< const SSLSettings > Settings::get_ssl_settings( void ) const
    {
        return m_pimpl->ssl_settings;
    }
#endif
    multimap< string, string > Settings::get_default_headers( void ) const
    {
        return m_pimpl->default_headers;
    }
    
    void Settings::set_port( const uint16_t value )
    {
        m_pimpl->port = value;
    }
    
    void Settings::set_root( const string& value )
    {
        m_pimpl->root = value;
    }
    
    void Settings::set_connection_limit( const int32_t value )
    {
        m_pimpl->connection_limit = value;
    }
    
    void Settings::set_case_insensitive_uris( const bool value )
    {
        m_pimpl->case_insensitive_uris = value;
    }
    
    void Settings::set_connection_timeout( const milliseconds& value )
    {
        m_pimpl->connection_timeout = value;
    }
    
    void Settings::set_status_message( const int code, const string& message )
    {
        m_pimpl->status_messages[ code ] = message;
    }
    
    void Settings::set_status_messages( const map< int, string >& values )
    {
        m_pimpl->status_messages = values;
    }
    
    void Settings::set_property( const string& name, const string& value )
    {
        m_pimpl->properties[ name ] = value;
    }
    
    void Settings::set_properties( const map< string, string >& values )
    {
        m_pimpl->properties = values;
    }
#ifdef BUILD_SSL
    void Settings::set_ssl_settings( const shared_ptr< const SSLSettings >& values )
    {
        m_pimpl->ssl_settings = values;
    }
#endif
    void Settings::set_default_header( const string& name, const string& value )
    {
        m_pimpl->default_headers.insert( make_pair( name, value ) );
    }
    
    void Settings::set_default_headers( const multimap< string, string >& values )
    {
        m_pimpl->default_headers = values;
    }
}
