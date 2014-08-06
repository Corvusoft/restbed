/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <regex>

//Project Includes
#include "corvusoft/restbed/method.h"
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/response.h"
#include "corvusoft/restbed/status_code.h"
#include "corvusoft/restbed/detail/resource_impl.h"
#include "corvusoft/restbed/detail/path_parameter_impl.h"

//External Includes
#include <corvusoft/framework/map>
#include <corvusoft/framework/regex>
#include <corvusoft/framework/string>
#include <corvusoft/framework/functional>

//System Namespaces
using std::map;
using std::bind;
using std::regex;
using std::string;
using std::function;
using std::regex_error;
using std::invalid_argument;
using std::placeholders::_1;

//Project Namespaces

//External Namespaces
using framework::Map;
using framework::Regex;
using framework::String;
using framework::Functional;

namespace restbed
{
    namespace detail
    {
        ResourceImpl::ResourceImpl( void ) : m_path( String::empty ),
            m_header_filters( ),
            m_method_handlers( )
        {
            setup( );
        }
        
        ResourceImpl::ResourceImpl( const ResourceImpl& original ) : m_path( original.m_path ),
            m_header_filters( original.m_header_filters ),
            m_method_handlers( original.m_method_handlers )
        {
            //n/a
        }
        
        ResourceImpl::~ResourceImpl( void )
        {
            //n/a
        }
        
        string ResourceImpl::get_path( void ) const
        {
            return m_path;
        }
        
        string ResourceImpl::get_header_filter( const string& name ) const
        {
            string filter = String::empty;
            
            const auto iterator = Map::find_key_ignoring_case( name, m_header_filters );
            
            if ( iterator not_eq m_header_filters.end( ) )
            {
                filter = iterator->second;
            }
            
            return filter;
        }
        
        map< string, string > ResourceImpl::get_header_filters( void ) const
        {
            return m_header_filters;
        }
        
        function< Response ( const Request& ) > ResourceImpl::get_method_handler( const Method& verb ) const
        {
            return m_method_handlers.at( verb.to_string( ) );
        }
        
        void ResourceImpl::set_path( const string& value )
        {
            auto path = String::split( value, '/' );
            
            for ( auto directory : path )
            {
                string pattern = PathParameterImpl::parse( directory );
                
                if ( not Regex::is_valid( pattern ) )
                {
                    throw invalid_argument( String::empty );
                }
            }
            
            m_path = value;
        }
        
        void ResourceImpl::set_header_filter( const string& name, const string& value )
        {
            if ( not Regex::is_valid( value ) )
            {
                throw invalid_argument( String::empty );
            }
            
            auto entry = Map::find_key_ignoring_case( name, m_header_filters );
            
            if ( entry not_eq m_header_filters.end( ) )
            {
                entry->second = value;
            }
            else
            {
                m_header_filters[ name ] = value;
            }
        }
        
        void ResourceImpl::set_header_filters( const map< string, string >& values )
        {
            for ( auto value : values )
            {
                set_header_filter( value.first, value.second );
            }
        }
        
        void ResourceImpl::set_method_handler( const Method& verb, const function< Response ( const Request& ) >& callback )
        {
            m_method_handlers[ verb.to_string( ) ] = callback;
        }
        
        bool ResourceImpl::operator <( const ResourceImpl& value ) const
        {
            return m_path < value.m_path;
        }
        
        bool ResourceImpl::operator >( const ResourceImpl& value ) const
        {
            return m_path > value.m_path;
        }
        
        bool ResourceImpl::operator ==( const ResourceImpl& value ) const
        {
            return m_path == value.m_path and m_header_filters == value.m_header_filters;
        }
        
        bool ResourceImpl::operator !=( const ResourceImpl& value ) const
        {
            return m_path not_eq value.m_path;
        }
        
        ResourceImpl& ResourceImpl::operator =( const ResourceImpl& value )
        {
            m_path = value.m_path;
            
            m_header_filters = value.m_header_filters;
            
            m_method_handlers = value.m_method_handlers;
            
            return *this;
        }
        
        void ResourceImpl::setup( void )
        {
            set_method_handler( "GET", &ResourceImpl::default_not_implemented_handler );
            set_method_handler( "PUT", &ResourceImpl::default_not_implemented_handler );
            set_method_handler( "POST", &ResourceImpl::default_not_implemented_handler );
            set_method_handler( "HEAD", &ResourceImpl::default_not_implemented_handler );
            set_method_handler( "DELETE", &ResourceImpl::default_not_implemented_handler );
            set_method_handler( "CONNECT", &ResourceImpl::default_not_implemented_handler );
            set_method_handler( "TRACE", &ResourceImpl::default_trace_handler );
            set_method_handler( "OPTIONS", bind( &ResourceImpl::default_options_handler, this, _1 ) );
        }
        
        string ResourceImpl::generate_allow_header_value( void )
        {
            string value = String::empty;
            
            for ( auto& handler : m_method_handlers )
            {
                Functional::address_type callback_address = Functional::get_address( handler.second );
                Functional::address_type default_address = ( Functional::address_type ) ResourceImpl::default_not_implemented_handler;
                
                if ( callback_address not_eq default_address )
                {
                    value += String::format( "%s, ", handler.first.data( ) );
                }
            }
            
            if ( not value.empty( ) )
            {
                value = value.substr( 0, value.length( ) - 2 );
            }
            
            return value;
        }
        
        string ResourceImpl::rebuild_path( const Request& request )
        {
            string query = "?";
            
            for ( auto parameter : request.get_query_parameters( ) )
            {
                query += String::format( "%s=%s&", parameter.first.data( ), parameter.second.data( ) );
            }
            
            query = String::trim( query, "&" );
            
            string path = request.get_path( );
            path += ( query.length( ) > 1 ) ? query : String::empty;
            
            return path;
        }
        
        string ResourceImpl::rebuild_headers( const Request& request )
        {
            string headers = String::empty;
            
            for ( auto header : request.get_headers( ) )
            {
                headers += String::format( "%s: %s\r\n", header.first.data( ), header.second.data( ) );
            }
            
            return headers;
        }
        
        Response ResourceImpl::default_options_handler( const Request& )
        {
            Response response;
            response.set_status_code( StatusCode::OK );
            response.set_header( "Allow", generate_allow_header_value( ) );
            
            return response;
        }
        
        Response ResourceImpl::default_trace_handler( const Request& request )
        {
            string path = rebuild_path( request );
            
            string headers = rebuild_headers( request );
            
            string body = String::format( "TRACE %s HTTP/1.1\r\n%s", path.data( ), headers.data( ) );
            
            Response response;
            response.set_body( body );
            response.set_status_code( StatusCode::OK );
            response.set_header( "Content-Type", "message/http" );
            
            return response;
        }
        
        Response ResourceImpl::default_not_implemented_handler( const Request& )
        {
            Response response;
            response.set_status_code( StatusCode::NOT_IMPLEMENTED );
            
            return response;
        }
    }
}
