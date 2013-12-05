/*
 * Copyright (c) 2013 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/mode.h"
#include "corvusoft/restbed/detail/settings_impl.h"
#include "corvusoft/restbed/detail/helpers/string.h"

//External Includes

//System Namespaces
using std::map;
using std::stoi;
using std::string;
using std::to_string;

//Project Namespaces
using restbed::detail::helpers::String;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        SettingsImpl::SettingsImpl( void ) : m_properties( )
        {
            m_properties[ "ROOT" ] = "/";
            m_properties[ "PORT" ] = "80";
            m_properties[ "MODE" ] = ::to_string( SYNCHRONOUS );
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

        string SettingsImpl::get_property( const string& name ) const
        {
            string property = String::empty;

            const string key = String::uppercase( name );

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
