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
#include <vector> 
#include <string>
#include <iostream> //debug

//Project Includes
#include "restbed/string.h"
#include "restbed/request.h"
#include "restbed/resource.h"
#include "restbed/detail/resource_matcher_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::regex;
using std::string;
using std::vector;

//Project Namespaces

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
            bool result = true;

            // compare_headers( m_request, resource );
            // for ( auto filter : resource.get_header_filters( ) )
            // {
            //     string name = filter.first;

            //     if ( m_request.has_header( name ) )
            //     {
            //         string value = filter.second;

            //         string pattern = regex( resource.get_header_filter( name ) );

            //         if ( not regex_match( value, pattern ) )
            //         {
            //             result = false;
            //             break;
            //         }
            //     }
            //     else
            //     {
            //         result = false;
            //         break;
            //     }
            // }

            // compare_paths( m_request, resource );
            // auto path_filters = resource.get_path_filters( );
            // auto path_segments = String::split( m_request.get_path( ), '/' );

            // if ( path_segments.size( ) == path_filters.size( ) )
            // {
            //     for ( vector< string >::size_type index = 0; index not_eq path_filters.size( ); index++ )
            //     {
            //         if ( not regex_match( path_segments[ index ], regex( path_filters[ index ] ) ) )
            //         {
            //             result = false;
            //             break;
            //         }
            //     }
            // }

            //return compare_paths( m_request, resource ) and compare_headers( m_request, resource );




            //WHAT IF NONE IS SUPPLIED == SEGFAULT!
            string type = m_request.get_header( "Content-Type" ); //what if none is supplied!?

            regex pattern = regex( resource.get_header_filter( "Content-Type" ) );
        
            if ( std::regex_match( type, pattern ) )
            {
                auto rs = String::split( resource.get_path( ), '/' );
                
                //std::map< std::string, std::string > m_resource_path_parameters;
                std::vector< std::string > m_resource_path_parameter_patterns;
                
                for ( auto element : rs )
                {
                    if ( element.front( ) == '{' ) //const char START_QUERY_PA
                    {
                        if ( element.back( ) == '}' )
                        {
                            //string pattern = String::empty; 
                            //pattern = String::trim( element, '{' );
                            //pattern = String::trim( element, '}' );

                            //auto segments = String::split( pattern, ':' );

                            //resource.get_path_patterns( );


                            std::string pattern = element.substr( 1, element.length( ) - 2 );
                            
                            std::cout << "path pattern: " << pattern << std::endl;
                            
                            auto segments = String::split( pattern, ':' );
                            
                            if ( segments.size( ) not_eq 2 )
                            {
                                std::cout <<"invalid path parameter" << std::endl;
                            }
                            
                            std::string name = segments[ 0 ];
                            
                            std::string value = segments[ 1 ];
                            
                            if ( value.front( ) == ' ' )
                            {
                                value.erase( 0, 1 );
                            }
                            
                            std::cout << "path pattern name: " << name << std::endl;
                            std::cout << "path pattern value: " << value << std::endl;
                            
                            //m_resource_path_parameters[ name ] = value;
                            
                            m_resource_path_parameter_patterns.push_back( value );
                        }
                        else
                        {
                            std::cout << "invalid path" << std::endl; //invalid_argument
                        }
                    }
                    else
                    {
                        m_resource_path_parameter_patterns.push_back( element );
                    }
                }
                
                //match!
                auto rq = String::split( m_request.get_path( ), '/' );
                
                std::cout << rq.size( ) << "-" << m_resource_path_parameter_patterns.size( ) << std::endl;
                
                if ( rq.size( ) == m_resource_path_parameter_patterns.size( ) )
                {
                    bool match = true;
                    
                    for ( std::vector< std::string >::size_type index = 0; index not_eq m_resource_path_parameter_patterns.size( ); index++ )
                    {
                        if ( not std::regex_match( rq[ index ], std::regex(m_resource_path_parameter_patterns[ index ]) ) )
                        {
                            std::cout << "no match" << std::endl;
                            match = false;
                            break;
                        }
                        
                        std::cout << "compared: " << rq[ index ] << "-" <<  m_resource_path_parameter_patterns[ index ] << std::endl;
                    }
                    
                    if ( match )
                    {
                        result = true;
                            
                        std::cout << "found matching resource!" << std::endl;
                    }
                }
            }
            
            return result;
        }

        //delete?
        bool ResourceMatcherImpl::operator <( const ResourceMatcherImpl& rhs ) const
        {
            return m_request < rhs.m_request;
        }
        
        bool ResourceMatcherImpl::operator >( const ResourceMatcherImpl& rhs ) const
        {
            return m_request > rhs.m_request;
        }
        
        bool ResourceMatcherImpl::operator ==( const ResourceMatcherImpl& rhs ) const
        {
            return m_request == rhs.m_request;
        }
        
        bool ResourceMatcherImpl::operator !=( const ResourceMatcherImpl& rhs ) const
        {
            return m_request not_eq rhs.m_request;
        }
    }
}
