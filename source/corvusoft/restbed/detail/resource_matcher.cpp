/*
 * Site: restbed.corvusoft.co.uk
 * Author: Ben Crowhurst
 *
 * Copyright (c) 2013 Restbed Core Development Team and Community Contributors
 *
 * This file is part of Restbed.
 *
 * Restbed is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Restbed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with Restbed.  If not, see <http://www.gnu.org/licenses/>.
 */

//System Includes
#include <map>
#include <regex>
#include <string>
#include <stdexcept>
 #include <iostream> //debug

//Project Includes
#include "restbed/request.h"
#include "restbed/resource.h"
#include "restbed/detail/helpers/string.h"
#include "restbed/detail/resource_matcher.h"

//External Includes

//System Namespaces
using std::map;
using std::regex;
using std::string;
using std::vector;
using std::invalid_argument;

//Project Namespaces
using restbed::detail::helpers::String;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        ResourceMatcher::ResourceMatcher( const Request& request ) : m_request( request)
        {
            //n/a
        }
        
        ResourceMatcher::ResourceMatcher( const ResourceMatcher& original ) : m_request( original.m_request )
        {
            //n/a
        }
        
        ResourceMatcher::~ResourceMatcher( void )
        {
            //n/a
        }     
        
        bool ResourceMatcher::operator ( )( const Resource& resource ) const
        {
            return compare_path( m_request, resource ) and compare_headers( m_request, resource );
        }

        regex ResourceMatcher::parse_filter_definition( const string& value ) const
        {
            string definition = value;

            if ( definition.front( ) == '{' )
            {
                if ( definition.back( ) == '}' )
                { 
                    definition = String::trim( definition, "{" );
                    definition = String::trim( definition, "}" ); 
                    
                    auto segments = String::split( definition, ':' );

                    if ( segments.size( ) not_eq 2 )
                    {
                        throw invalid_argument( String::empty );
                    }
                    
                    definition = String::trim( segments[ 1 ] );
                }
            }

            return regex( definition );  
        }

        vector< string > ResourceMatcher::parse_path_definition( const string& value ) const
        {
            return String::split( value, '/' );
        }

        bool ResourceMatcher::compare_path( const Request& request, const Resource& resource ) const
        {
            bool result = true;

            auto path_filters = parse_path_definition( resource.get_path( ) );

            auto path_segments = String::split( request.get_path( ), '/' );

            if ( path_segments.size( ) == path_filters.size( ) )
            {
                for ( vector< string >::size_type index = 0; index not_eq path_filters.size( ); index++ )
                {
                    regex pattern = parse_filter_definition( path_filters[ index ] );

                    if ( not regex_match( path_segments[ index ], pattern ) )
                    {
                        result = false;
                        break;
                    }
                }
            }

            return result;
        }

        bool ResourceMatcher::compare_headers( const Request& request, const Resource& resource ) const
        {
            bool result = true;

            for ( auto filter : resource.get_header_filters( ) )
            {
                string name = filter.first;

                if ( request.has_header( name ) )
                {
                    string header = request.get_header( name );

                    regex pattern = regex( filter.second );

                    if ( not regex_match( header, pattern ) )
                    {
                        result = false;
                        break;
                    }
                }
                else
                {
                    result = false;
                    break;
                }
            }

            return result;
        }
    }
}
