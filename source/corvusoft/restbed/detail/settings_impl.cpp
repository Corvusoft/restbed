/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/ssl_settings.hpp"
#include "corvusoft/restbed/detail/settings_impl.hpp"
#include "corvusoft/restbed/detail/status_messages_impl.hpp"

//External Includes
#include <corvusoft/framework/string>

//System Namespaces
using std::map;
using std::string;
using std::multimap;
using std::shared_ptr;
using std::chrono::seconds;

//Project Namespaces

//External Namespaces
using framework::String;

namespace restbed
{
    namespace detail
    {
        SettingsImpl::SettingsImpl( void ) : m_port( 80 ),
            m_root( "/" ),
            m_connection_limit( 128 ),
            m_connection_timeout( 5 ),
            m_status_messages( status_messages ),
            m_properties( ),
            m_default_headers( )
        {
            return;
        }
        
        SettingsImpl::~SettingsImpl( void )
        {
            return;
        }
        
        uint16_t SettingsImpl::get_port( void ) const
        {
            return m_port;
        }
        
        string SettingsImpl::get_root( void ) const
        {
            return m_root;
        }
        
        int32_t SettingsImpl::get_connection_limit( void ) const
        {
            return m_connection_limit;
        }
        
        seconds SettingsImpl::get_connection_timeout( void ) const
        {
            return m_connection_timeout;
        }
        
        string SettingsImpl::get_status_message( const int code ) const
        {
            string message = String::empty;
            
            if ( m_status_messages.count( code ) )
            {
                message = m_status_messages.at( code );
            }
            else
            {
                message = m_status_messages.at( 0 );
            }
            
            return message;
        }
        
        map< int, string > SettingsImpl::get_status_messages( void ) const
        {
            return m_status_messages;
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

        shared_ptr< const SSLSettings > SettingsImpl::get_ssl_settings( void ) const
        {
            return m_ssl_settings;
        }
        
        multimap< string, string > SettingsImpl::get_default_headers( void ) const
        {
            return m_default_headers;
        }
        
        void SettingsImpl::set_port( const uint16_t value )
        {
            m_port = value;
        }
        
        void SettingsImpl::set_root( const string& value )
        {
            m_root = value;
        }
        
        void SettingsImpl::set_connection_limit( const int32_t value )
        {
            m_connection_limit = value;
        }
        
        void SettingsImpl::set_connection_timeout( const seconds& value )
        {
            m_connection_timeout = value;
        }
        
        void SettingsImpl::set_status_message( const int code, const string& message )
        {
            m_status_messages[ code ] = message;
        }
        
        void SettingsImpl::set_status_messages( const map< int, string >& values )
        {
            m_status_messages = values;
        }
        
        void SettingsImpl::set_property( const string& name, const string& value )
        {
            m_properties[ name ] = value;
        }
        
        void SettingsImpl::set_properties( const map< string, string >& values )
        {
            m_properties.insert( values.begin( ), values.end( ) );
        }

        void SettingsImpl::set_ssl_settings( const shared_ptr< const SSLSettings >& value )
        {
            m_ssl_settings = value;
        }
        
        void SettingsImpl::set_default_header( const string& name, const string& value )
        {
            m_default_headers.insert( make_pair( name, value ) );
        }
        
        void SettingsImpl::set_default_headers( const multimap< string, string >& values )
        {
            m_default_headers = values;
        }
    }
}
