/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/status_code.h"
#include "corvusoft/restbed/detail/request_impl.h"

//External Includes
#include <corvusoft/framework/map>
#include <corvusoft/framework/string>

//System Namespaces
using std::map;
using std::stod;
using std::string;
using std::multimap;

//Project Namespaces
using restbed::detail::RequestImpl;

//External Namespaces
using framework::Map;
using framework::Bytes;
using framework::String;

namespace restbed
{
    namespace detail
    {
        RequestImpl::RequestImpl( void ) : m_body( ),
            m_version( 1.1 ),
            m_path( "/" ),
            m_method( "GET" ),
            m_origin( String::empty ),
            m_protocol( "HTTP" ),
            m_headers( ),
            m_path_parameters( ),
            m_query_parameters( )
        {
            //n/a
        }
        
        RequestImpl::RequestImpl( const RequestImpl& original ) : m_body( original.m_body ),
            m_version( original.m_version ),
            m_path( original.m_path ),
            m_method( original.m_method ),
            m_origin( original.m_origin ),
            m_protocol( original.m_protocol ),
            m_headers( original.m_headers ),
            m_path_parameters( original.m_path_parameters ),
            m_query_parameters( original.m_query_parameters )
        {
            //n/a
        }
        
        RequestImpl::~RequestImpl( void )
        {
            //n/a
        }
        
        Bytes RequestImpl::to_bytes( void ) const
        {
            string headers = String::format( "%s%s\r\n", generate_status_section( ).data( ), generate_header_section( ).data( ) );
            
            Bytes bytes( headers.begin( ), headers.end( ) );
            bytes.insert( bytes.end( ), m_body.begin( ), m_body.end( ) );
            
            return bytes;
        }
        
        bool RequestImpl::has_header( const string& name ) const
        {
            return ( Map::find_key_ignoring_case( name, m_headers ) not_eq m_headers.end( ) );
        }
        
        bool RequestImpl::has_path_parameter( const string& name ) const
        {
            return ( Map::find_key_ignoring_case( name, m_path_parameters ) not_eq m_path_parameters.end( ) );
        }
        
        bool RequestImpl::has_query_parameter( const string& name ) const
        {
            return ( m_query_parameters.find( name ) not_eq m_query_parameters.end( ) );
        }
        
        Bytes RequestImpl::get_body( void ) const
        {
            return m_body;
        }
        
        double RequestImpl::get_version( void ) const
        {
            return m_version;
        }
        
        string RequestImpl::get_path( void ) const
        {
            return m_path;
        }
        
        string RequestImpl::get_method( void ) const
        {
            return m_method;
        }
        
        string RequestImpl::get_origin( void ) const
        {
            return m_origin;
        }

        string RequestImpl::get_protocol( void ) const
        {
            return m_protocol;
        }
        
        string RequestImpl::get_header( const string& name, const string& default_value ) const
        {
            string value = default_value;
            
            if ( has_header( name ) )
            {
                const auto iterator = Map::find_key_ignoring_case( name, m_headers );
                
                value = iterator->second;
            }
            
            return value;
        }
        
        multimap< string, string > RequestImpl::get_headers( void ) const
        {
            return m_headers;
        }
        
        multimap< string, string > RequestImpl::get_headers( const string& name ) const
        {
            multimap< string, string > headers;
            
            auto key = String::lowercase( name );
            
            for ( auto header : m_headers )
            {
                if ( String::lowercase( header.first ) == key )
                {
                    headers.insert( header );
                }
            }
            
            return headers;
        }
        
        string RequestImpl::get_query_parameter( const string& name, const string& default_value ) const
        {
            string parameter = default_value;
            
            if ( has_query_parameter( name ) )
            {
                const auto iterator = m_query_parameters.find( name );
                
                parameter = iterator->second;
            }
            
            return parameter;
        }
        
        multimap< string, string > RequestImpl::get_query_parameters( void ) const
        {
            return m_query_parameters;
        }

        multimap< string, string > RequestImpl::get_query_parameters( const string& name ) const
        {
            multimap< string, string > parameters;
            
            for ( auto parameter : m_query_parameters )
            {
                if ( parameter.first == name )
                {
                    parameters.insert( parameter );
                }
            }
            
            return parameters;
        }
        
        string RequestImpl::get_path_parameter( const string& name, const string& default_value ) const
        {
            string parameter = default_value;
            
            if ( has_path_parameter( name ) )
            {
                const auto iterator = Map::find_key_ignoring_case( name, m_path_parameters );
                
                parameter = iterator->second;
            }
            
            return parameter;
        }
        
        map< string, string > RequestImpl::get_path_parameters( void ) const
        {
            return m_path_parameters;
        }
        
        void RequestImpl::set_body( const Bytes& value )
        {
            m_body = value;
        }
        
        void RequestImpl::set_version( const double value )
        {
            if ( value not_eq 1.0 and value not_eq 1.1 )
            {
                throw StatusCode::HTTP_VERSION_NOT_SUPPORTED;
            }
            
            m_version = value;
        }
        
        void RequestImpl::set_path( const string& value )
        {
            m_path = value;
        }
        
        void RequestImpl::set_method( const string& value )
        {
            m_method = value;
        }
        
        void RequestImpl::set_origin( const string& value )
        {
            m_origin = value;
        }

        void RequestImpl::set_protocol( const string& value )
        {
            auto protocol = String::uppercase( value );

            if ( protocol not_eq "HTTP" and protocol not_eq "HTTPS" )
            {
                throw StatusCode::BAD_REQUEST;
            }
            
            m_protocol = value;
        }
        
        void RequestImpl::set_headers( const multimap< string, string >& values )
        {
            m_headers = values;
        }
        
        void RequestImpl::set_path_parameters( const map< string, string >& values )
        {
            m_path_parameters = values;
        }
        
        void RequestImpl::set_query_parameters( const multimap< string, string >& values )
        {
            m_query_parameters = values;
        }
        
        bool RequestImpl::operator <( const RequestImpl& value ) const
        {
            return m_path < value.m_path;
        }
        
        bool RequestImpl::operator >( const RequestImpl& value ) const
        {
            return m_path > value.m_path;
        }
        
        bool RequestImpl::operator ==( const RequestImpl& value ) const
        {
            return ( m_path == value.m_path and
                     m_method == value.m_method and
                     m_origin == value.m_origin and
                     m_version == value.m_version and
                     m_headers == value.m_headers and
                     m_protocol == value.m_protocol and
                     m_path_parameters == value.m_path_parameters and
                     m_query_parameters == value.m_query_parameters );
        }
        
        bool RequestImpl::operator !=( const RequestImpl& value ) const
        {
            return not ( *this == value );
        }
        
        RequestImpl& RequestImpl::operator =( const RequestImpl& value )
        {
            m_body = value.m_body;
            
            m_path = value.m_path;
            
            m_method = value.m_method;
            
            m_origin = value.m_origin;
            
            m_version = value.m_version;
            
            m_headers = value.m_headers;
            
            m_protocol = value.m_protocol;
            
            m_path_parameters = value.m_path_parameters;
            
            m_query_parameters = value.m_query_parameters;
            
            return *this;
        }
        
        string RequestImpl::generate_status_section( void ) const
        {
            return String::format( "%s %s %s/%.1f\r\n", m_method.data( ), generate_path_section( ).data( ), m_protocol.data( ), m_version );
        }
        
        string RequestImpl::generate_header_section( void ) const
        {
            string section = String::empty;
            
            for ( auto header : m_headers )
            {
                section += String::format( "%s: %s\r\n", header.first.data( ), header.second.data( ) );
            }
            
            return section;
        }
        
        string RequestImpl::generate_path_section( void ) const
        {
            string section = m_path;
            
            if ( not m_query_parameters.empty( ) )
            {
                section += "?";
                
                for ( auto parameter : m_query_parameters )
                {
                    section += String::format( "%s=%s&", parameter.first.data( ), parameter.second.data( ) );
                }
            }
            
            return String::trim_lagging( section, "&" );
        }
    }
}
