/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/detail/settings_impl.h"

//External Includes
#include <corvusoft/framework/string>

//System Namespaces
using std::map;
using std::stol;
using std::stoll;
using std::string;
using std::to_string;
using std::chrono::seconds;

//Project Namespaces

//External Namespaces
using framework::String;

namespace restbed
{
    namespace detail
    {
        SettingsImpl::SettingsImpl( void ) : m_properties( )
        {
            m_properties[ "root" ] = "/";
            m_properties[ "port" ] = "80";
            m_properties[ "connection-limit" ] = "128";
            m_properties[ "connection-timeout" ] = "5";
        }
        
        SettingsImpl::~SettingsImpl( void )
        {
            return;
        }
        
        uint16_t SettingsImpl::get_port( void ) const
        {
            return stoi( get_property( "port" ) );
        }
        
        string SettingsImpl::get_root( void ) const
        {
            return get_property( "root" );
        }
        
        int32_t SettingsImpl::get_connection_limit( void ) const
        {
            return stoul( get_property( "connection-limit" ) );
        }

        seconds SettingsImpl::get_connection_timeout( void ) const
        {
            return seconds( stoll( get_property( "socket-timeout" ) ) );
        }

        string SettingsImpl::get_property( const string& name ) const
        {
            if ( m_properties.count( name ) )
            {
                return m_properties.at( name );
            }
            
            return String::empty;
        }
        
        map< string, string > SettingsImpl::get_properties( void ) const
        {
            return m_properties;
        }
        
        void SettingsImpl::set_port( const uint16_t value )
        {
            set_property( "port", ::to_string( value ) );
        }
        
        void SettingsImpl::set_root( const string& value )
        {
            set_property( "root", value );
        }
        
        void SettingsImpl::set_connection_limit( const int32_t value )
        {
            set_property( "connection-limit", ::to_string( value ) );
        }

        void SettingsImpl::set_connection_timeout( const seconds& value )
        {
            set_property( "connection-timeout", ::to_string( value.count( ) ) );
        }

        void SettingsImpl::set_property( const string& name, const string& value )
        {
            m_properties[ name ] = value;
        }
        
        void SettingsImpl::set_properties( const map< string, string >& values )
        {
            m_properties.insert( values.begin( ), values.end( ) );
        }
    }
}
