/*
 * Copyright (c) 2013 Corvusoft
 */

//System Includes
#include <map>
#include <regex>
#include <string>
#include <stdexcept>

//Project Includes
#include "restbed/request.h"
#include "restbed/resource.h"
#include "restbed/detail/helpers/string.h"
#include "restbed/detail/path_parameter.h"
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

        bool ResourceMatcher::compare_path( const Request& request, const Resource& resource ) const
        {
            auto path_segments = String::split( request.get_path( ), '/' );
            auto path_filters = String::split( resource.get_path( ), '/' );
            bool result = false;

            if ( path_segments.size( ) == path_filters.size( ) )
            {
                auto path_segments_it = path_segments.begin();
                auto path_filters_it = path_filters.begin();
                
                for (; path_segments_it not_eq path_segments.end() and path_filters_it not_eq path_filters.end();
                path_segments_it++, path_filters_it++)
                {
                    regex pattern = PathParameter::parse( *path_filters_it );   

                    if ( not regex_match( *path_segments_it, pattern ) )
                    {
                        result = false;
                        break;
                    }
                    else
                    {
                        result = true;
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
                    string value = request.get_header( name );

                    regex pattern = regex( filter.second );

                    if ( not regex_match( value, pattern ) )
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
