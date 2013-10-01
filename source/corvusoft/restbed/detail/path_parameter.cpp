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
#include <regex>
#include <vector>
#include <iostream> //debug

//Project Includes
#include "restbed/detail/path_parameter.h"
#include "restbed/detail/helpers/string.h"

//External Includes

//System Namespaces
using std::map;
using std::string;
using std::vector;

//Project Namespaces
using restbed::detail::helpers::String;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        map< string, string > PathParameter::parse( const string& path, const string& definition )
        {
            auto definitions = String::split( definition, '/' );

            auto paths = String::split( get_path( ), '/' );

            for ( vector< string >::size_type index = 0; index not_eq definitions.size( ); index++ )
            {
                string def = definitions[ index ];

                if ( def.front( ) == '{' )
                {
                    if ( def.back( ) == '}' )
                    { 
                        def = String::trim( def, "{" );
                        def = String::trim( def, "}" ); 
                        
                        auto segments = String::split( def, ':' ); //declaration

                        if ( segments.size( ) not_eq 2 )
                        {
                            //throw invalid_argument( String::empty );
                        }
                        
                        def = String::trim( segments[ 1 ] );

                        std::cout << "definition: " << def << std::endl;
                    }
                }

                std::smatch match;

                if ( std::regex_search( paths[ index ], match, std::regex( def ) ) )
                {
                    std::cout << "id: " << match[0] << std::endl;
                }
            }
        }
    }
}
