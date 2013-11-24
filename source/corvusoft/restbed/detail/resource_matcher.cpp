/*
 * Copyright (c) 2013 Corvusoft
 */

//System Includes
#include <map>
#include <regex>
#include <string>
#include <stdexcept>

//Project Includes
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/resource.h"
#include "corvusoft/restbed/detail/helpers/string.h"
#include "corvusoft/restbed/detail/path_parameter.h"
#include "corvusoft/restbed/detail/resource_matcher.h"

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

            bool result = ( path_segments.size( ) == path_filters.size( ) );

            for ( vector< string >::size_type index = 0; index not_eq path_filters.size( ); index++ )
            {
                regex pattern = PathParameter::parse( path_filters[ index ] );

                if ( not regex_match( path_segments[ index ], pattern ) )
                {
                    result = false;
                    break;
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
