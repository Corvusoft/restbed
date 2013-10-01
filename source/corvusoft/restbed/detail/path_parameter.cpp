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
#include <vector>
#include <iostream> //debug
#include <stdexcept>

//Project Includes
#include "restbed/detail/path_parameter.h"
#include "restbed/detail/helpers/string.h"

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
        regex PathParameter::parse( const string& definition )
        {
            string declaration = definition;

            if ( declaration.front( ) == '{' )
            {
                if ( declaration.back( ) == '}' )
                { 
                    declaration = String::trim( declaration, "{" );
                    declaration = String::trim( declaration, "}" ); 
                    
                    auto segments = String::split( declaration, ':' );

                    if ( segments.size( ) not_eq 2 )
                    {
                        throw invalid_argument( String::empty );
                    }
                    
                    declaration = String::trim( segments[ 1 ] );
                }
            }

            return regex( declaration );  
        }

        map< string, string > PathParameter::parse( const string& path, const string& definition )
        {
            auto definitions = String::split( definition, '/' );

            auto paths = String::split( path, '/' );

            for ( vector< string >::size_type index = 0; index not_eq definitions.size( ); index++ )
            {
                string declaration = definitions[ index ];

                if ( declaration.front( ) == '{' )
                {
                    if ( declaration.back( ) == '}' )
                    { 
                        declaration = String::trim( declaration, "{" );
                        declaration = String::trim( declaration, "}" ); 
                        
                        auto segments = String::split( declaration, ':' ); //declaration

                        if ( segments.size( ) not_eq 2 )
                        {
                            //throw invalid_argument( String::empty );
                        }
                        
                        string name = String::trim( segments[ 0 ] );
                        string pattern = String::trim( segments[ 1 ] );
                        

                        std::smatch match;

                        if ( std::regex_search( paths[ index ], match, std::regex( pattern ) ) )
                        {
                            std::cout << "name: " << name << std::endl;
                            std::cout << "definition: " << pattern << std::endl;
                            //std::cout << "id: " << match[0] << std::endl;
                        }
                    }
                }
            }

            return map< string, string >( );
        }
    }
}
