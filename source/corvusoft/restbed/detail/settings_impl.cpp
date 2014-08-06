/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/mode.h"
#include "corvusoft/restbed/detail/settings_impl.h"

//External Includes
#include <corvusoft/framework/map>
#include <corvusoft/framework/string>

//System Namespaces
using std::map;
using std::stoi;
using std::string;
using std::to_string;

//Project Namespaces

//External Namespaces
using framework::Map;
using framework::String;

namespace restbed
{
    namespace detail
    {
        SettingsImpl::SettingsImpl( void ) : m_properties( )
        {
            m_properties[ "ROOT" ] = "/";
            m_properties[ "PORT" ] = "80";
            m_properties[ "MODE" ] = ::to_string( SYNCHRONOUS );
            m_properties[ "MAXIMUM CONNECTIONS" ] = "1024";
        }
        
        SettingsImpl::SettingsImpl( const SettingsImpl& original ) : m_properties( original.m_properties )
        {
            //n/a
        }
        
        SettingsImpl::~SettingsImpl( void )
        {
            //n/a
        }
        
        Mode SettingsImpl::get_mode( void ) const
        {
            return static_cast< Mode >( stoi( get_property( "MODE" ) ) );
        }
        
        uint16_t SettingsImpl::get_port( void ) const
        {
            return stoi( get_property( "PORT" ) );
        }
        
        string SettingsImpl::get_root( void ) const
        {
            return get_property( "ROOT" );
        }
        
        int SettingsImpl::get_maximum_connections( void ) const
        {
            return stoi( get_property( "MAXIMUM CONNECTIONS" ) );
        }
        
        string SettingsImpl::get_property( const string& name ) const
        {
            string property = String::empty;
            
            auto iterator = Map::find_key_ignoring_case( name, m_properties );
            
            if ( iterator not_eq m_properties.end( ) )
            {
                property = iterator->second;
            }
            
            return property;
        }
        
        map< string, string > SettingsImpl::get_properties( void ) const
        {
            return m_properties;
        }
        
        void SettingsImpl::set_mode( const Mode value )
        {
            set_property( "MODE", ::to_string( value ) );
        }
        
        void SettingsImpl::set_port( const uint16_t value )
        {
            set_property( "PORT", ::to_string( value ) );
        }
        
        void SettingsImpl::set_root( const string& value )
        {
            set_property( "ROOT", value );
        }
        
        void SettingsImpl::set_maximum_connections( const int value )
        {
            set_property( "MAXIMUM CONNECTIONS", ::to_string( value ) );
        }
        
        void SettingsImpl::set_property( const string& name, const string& value )
        {
            const string key = String::uppercase( name );
            
            m_properties[ key ] = value;
        }
        
        void SettingsImpl::set_properties( const map< string, string >& values )
        {
            for ( const auto& value : values )
            {
                set_property( value.first, value.second );
            }
        }
        
        SettingsImpl& SettingsImpl::operator =( const SettingsImpl& value )
        {
            m_properties = value.m_properties;
            
            return *this;
        }
    }
}
