/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <map>
#include <regex>
#include <string>
#include <stdexcept>

//Project Includes
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/resource.h"
#include "corvusoft/restbed/detail/path_parameter_impl.h"
#include "corvusoft/restbed/detail/resource_matcher_impl.h"

//External Includes
#include <corvusoft/framework/string>

//System Namespaces
using std::map;
using std::regex;
using std::string;
using std::vector;
using std::invalid_argument;

//Project Namespaces

//External Namespaces
using framework::String;

namespace restbed
{
    namespace detail
    {
        ResourceMatcherImpl::ResourceMatcherImpl( const Request& request ) : m_request( request )
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
            bool found_matching_path = false;
            
            auto resource_paths = resource.get_paths( );
            auto path_segments = String::split( request.get_path( ), '/' );
            
            for ( auto path : resource_paths )
            {
                auto path_filters = String::split( path, '/' );
                
                if ( path_segments.size( ) == path_filters.size( ) )
                {
                    found_matching_path = true;
                    
                    for ( size_t index = 0; index not_eq path_filters.size( ); index++ )
                    {
                        string filter = PathParameterImpl::parse( path_filters[ index ] );
                        
                        regex pattern( filter );
                        
                        if ( not regex_match( path_segments[ index ], pattern ) )
                        {
                            found_matching_path = false;
                            break;
                        }
                    }
                }
                
                if ( found_matching_path )
                {
                    break;
                }
            }
            
            return found_matching_path;
        }
        
        bool ResourceMatcherImpl::compare_headers( const Request& request, const Resource& resource ) const
        {
            bool result = true;
            
            for ( auto filter : resource.get_header_filters( ) )
            {
                string name = filter.first;
                regex pattern = regex( filter.second );
                
                for ( auto header : request.get_headers( name ) )
                {
                    string value = header.second;
                    
                    if ( not regex_match( value, pattern ) )
                    {
                        return false;
                    }
                }
            }
            
            return result;
        }
    }
}
