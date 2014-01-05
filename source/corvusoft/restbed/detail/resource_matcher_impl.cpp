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
#include "corvusoft/restbed/detail/path_parameter_impl.h"
#include "corvusoft/restbed/detail/resource_matcher_impl.h"

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
        ResourceMatcherImpl::ResourceMatcherImpl( const Request& request ) : m_request( request)
        {
            //n/a
        }
        
        ResourceMatcherImpl::ResourceMatcherImpl( const ResourceMatcherImpl& original ) : m_request( original.m_request )
        {
            //n/a
        }
        
        ResourceMatcherImpl::~ResourceMatcherImpl( void )
        {
            //n/a
        }     
        
        bool ResourceMatcherImpl::operator ( )( const Resource& resource ) const
        {
            return compare_path( m_request, resource ) and compare_headers( m_request, resource );
        }

        bool ResourceMatcherImpl::compare_path( const Request& request, const Resource& resource ) const
        {
            bool result = false;

            auto path_segments = String::split( request.get_path( ), '/' );
            auto path_filters = String::split( resource.get_path( ), '/' );

            if ( path_segments.size( ) == path_filters.size( ) )
            {
                result = true;

                for ( size_t index = 0; index not_eq path_filters.size( ); index++ )
                {
                    string filter = PathParameterImpl::parse( path_filters[ index ] );

                    regex pattern( filter );

                    if ( not regex_match( path_segments[ index ], pattern ) )
                    {
                        result = false;
                        break;
                    }
                }
            }

            return result;
        }

        bool ResourceMatcherImpl::compare_headers( const Request& request, const Resource& resource ) const
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
