/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <regex>
#include <algorithm>

//Project Includes
#include "corvusoft/restbed/methods.h"
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/response.h"
#include "corvusoft/restbed/detail/resource_impl.h"
#include "corvusoft/restbed/detail/path_parameter_impl.h"

//External Includes
#include <corvusoft/framework/map>
#include <corvusoft/framework/regex>
#include <corvusoft/framework/string>

//System Namespaces
using std::map;
using std::bind;
using std::find;
using std::regex;
using std::string;
using std::vector;
using std::function;
using std::regex_error;
using std::invalid_argument;
using std::placeholders::_1;

//Project Namespaces

//External Namespaces
using framework::Map;
using framework::Regex;
using framework::String;

namespace restbed
{
    namespace detail
    {
        ResourceImpl::ResourceImpl( void ) : m_paths( ),
            m_allow_methods( { "OPTIONS", "TRACE" } ),
            m_header_filters( ),
            m_method_handlers( )
        {
            return;
        }
        
        ResourceImpl::ResourceImpl( const ResourceImpl& original ) : m_paths( original.m_paths ),
            m_allow_methods( original.m_allow_methods ),
            m_header_filters( original.m_header_filters ),
            m_method_handlers( original.m_method_handlers )
        {
            return;
        }
        
        ResourceImpl::~ResourceImpl( void )
        {
            return;
        }

        string ResourceImpl::get_path( void ) const
        {
            return m_paths.empty( ) ? String::empty : m_paths.front( );
        }
        
        vector< string > ResourceImpl::get_paths( void ) const
        {
            return m_paths;
        }
        
        string ResourceImpl::get_header_filter( const string& name ) const
        {
            string filter = String::empty;
            
            const auto iterator = Map::find_ignoring_case( name, m_header_filters );
            
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
        
        function< Response ( const Request& ) > ResourceImpl::get_method_handler( const string& method ) const
        {
            const auto verb = String::uppercase( method );

            if ( m_method_handlers.count( verb ) not_eq 0 )
            {
                return m_method_handlers.at( verb );
            }
            else if ( verb == "TRACE" )
            {
                return &ResourceImpl::default_trace_handler;
            }
            else if ( verb == "OPTIONS" )
            {
                return bind( &ResourceImpl::default_options_handler, _1, m_allow_methods );
            }
            else
            {
                return bind( &ResourceImpl::default_method_not_allowed_handler, _1, m_allow_methods );
            }
        }
        
        map< string, function< Response ( const Request& ) > > ResourceImpl::get_method_handlers( void ) const
        {
            map< string, function< Response ( const Request& ) > > handlers = m_method_handlers;

            if ( handlers.count( "TRACE" ) == 0 )
            {
                handlers[ "TRACE" ] = &ResourceImpl::default_trace_handler;
            }

            if ( handlers.count( "OPTIONS" ) == 0 )
            {
                handlers[ "OPTIONS" ] = bind( &ResourceImpl::default_options_handler, _1, m_allow_methods );
            }

            if ( handlers.count( "GET" ) == 0 )
            {
                handlers[ "GET" ] = bind( &ResourceImpl::default_method_not_allowed_handler, _1, m_allow_methods );
            }

            if ( handlers.count( "PUT" ) == 0 )
            {
                handlers[ "PUT" ] = bind( &ResourceImpl::default_method_not_allowed_handler, _1, m_allow_methods );
            }

            if ( handlers.count( "POST" ) == 0 )
            {
                handlers[ "POST" ] = bind( &ResourceImpl::default_method_not_allowed_handler, _1, m_allow_methods );
            }

            if ( handlers.count( "HEAD" ) == 0 )
            {
                handlers[ "HEAD" ] = bind( &ResourceImpl::default_method_not_allowed_handler, _1, m_allow_methods );
            }

            if ( handlers.count( "DELETE" ) == 0 )
            {
                handlers[ "DELETE" ] = bind( &ResourceImpl::default_method_not_allowed_handler, _1, m_allow_methods );
            }

            if ( handlers.count( "CONNECT" ) == 0 )
            {
                handlers[ "CONNECT" ] = bind( &ResourceImpl::default_method_not_allowed_handler, _1, m_allow_methods );
            }

            return handlers;
        }
        
        void ResourceImpl::set_path( const string& value )
        {
            m_paths.clear( );
            m_paths.push_back( value );
        }
        
        void ResourceImpl::set_paths( const vector< string >& values )
        {
            for ( auto value : values )
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
                
                
                m_paths.push_back( value );
            }
        }
        
        void ResourceImpl::set_header_filter( const string& name, const string& value )
        {
            if ( not Regex::is_valid( value ) )
            {
                throw invalid_argument( String::empty );
            }
            
            auto entry = Map::find_ignoring_case( name, m_header_filters );
            
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
        
        void ResourceImpl::set_method_handler( const string& method, const function< Response ( const Request& ) >& callback )
        {
            auto verb = String::uppercase( method );
            
            m_method_handlers[ verb ] = callback;
            
            auto iterator = find( m_allow_methods.begin( ), m_allow_methods.end( ), verb );
            
            if ( iterator == m_allow_methods.end( ) )
            {
                m_allow_methods.push_back( verb );
            }
        }
        
        void ResourceImpl::set_method_handlers( const map< string, function< Response ( const Request& ) > >& values )
        {
            for ( const auto value : values )
            {
                set_method_handler( value.first, value.second );
            }
        }
        
        bool ResourceImpl::operator <( const ResourceImpl& value ) const
        {
            return m_paths < value.m_paths;
        }
        
        bool ResourceImpl::operator >( const ResourceImpl& value ) const
        {
            return m_paths > value.m_paths;
        }
        
        bool ResourceImpl::operator ==( const ResourceImpl& value ) const
        {
            return m_paths == value.m_paths and m_header_filters == value.m_header_filters;
        }
        
        bool ResourceImpl::operator !=( const ResourceImpl& value ) const
        {
            return not ( *this == value );
        }
        
        ResourceImpl& ResourceImpl::operator =( const ResourceImpl& value )
        {
            m_paths = value.m_paths;

            m_allow_methods = value.m_allow_methods;
            
            m_header_filters = value.m_header_filters;
            
            m_method_handlers = value.m_method_handlers;
            
            return *this;
        }
        
        string ResourceImpl::rebuild_path( const Request& request )
        {
            string query = String::join( request.get_query_parameters( ), "=", "&" );
            
            if ( not query.empty( ) )
            {
                query = "?" + query;
            }
            
            return request.get_path( ) + query;
        }

        Response ResourceImpl::default_trace_handler( const Request& request )
        {
            string path = rebuild_path( request );

            string headers = String::join( request.get_headers( ), ": ", "\r\n" );

            string body = String::format( "TRACE %s HTTP/1.1\r\n%s", path.data( ), headers.data( ) );

            Response response;
            response.set_body( body );
            response.set_status_code( 200 );
            response.set_header( "Content-Type", "message/http" );

            return response;
        }
        
        Response ResourceImpl::default_options_handler( const Request&, const vector< string >& allow_methods )
        {
            Response response;
            response.set_status_code( 200 );
            response.set_header( "Allow", String::join( allow_methods, ", " ) );
            
            return response;
        }
        
        Response ResourceImpl::default_method_not_allowed_handler( const Request&, const vector< string >& allow_methods )
        {
            Response response;
            response.set_status_code( 405 );
            response.set_header( "Allow", String::join( allow_methods, ", " ) );
            
            return response;
        }
    }
}
