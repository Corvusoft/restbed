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

#ifndef _RESTBED_MAP_H
#define _RESTBED_MAP_H 1

//System Includes
#include <map>
#include <string>

//Project Includes
#include "restbed/detail/helpers/string.h"

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    namespace detail
    {
        //Forward Declarations

        namespace helpers
        {
            //Forward Declarations
            
            class Map
            {
                public:
                    //Friends
                    
                    //Definitions

                    //Constructors
                    
                    //Functionality
                    static std::map< std::string, std::string >::const_iterator find_key_ignoring_case( const std::map< std::string, std::string >& haystack, const std::string& needle )
                    {
                        std::string key = String::lowercase( needle );

                        std::string name = String::empty;

                        for ( auto value : haystack )
                        {
                            if ( key == String::lowercase( value.first ) )
                            {
                                name = value.first;
                                break;
                            }
                        }

                        return ( name not_eq String::empty ) ? haystack.find( name ) : haystack.end( );
                    }

                    //Getters
                    
                    //Setters
                    
                    //Operators
                    
                    //Properties
                
                protected:
                    //Friends
                    
                    //Definitions
                    
                    //Constructors
                    
                    //Functionality
                    
                    //Getters
                    
                    //Setters
                    
                    //Operators
                    
                    //Properties
                    
                private:
                    //Friends
                    
                    //Definitions
                    
                    //Constructors
                    Map( void ) = delete;
                    
                    Map( const Map& original ) = delete;
                    
                    virtual ~Map( void ) = delete;

                    //Functionality
                    
                    //Getters
                    
                    //Setters
                    
                    //Operators
                    Map& operator =( const Map& rhs ) = delete;

                    //Properties
            };
        }
    }
}

#endif  /* _RESTBED_MAP_H */
