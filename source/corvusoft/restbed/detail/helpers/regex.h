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

#ifndef _RESTBED_DETAIL_HELPERS_REGEX_H
#define _RESTBED_DETAIL_HELPERS_REGEX_H 1

//System Includes
#include <string>

//Project Includes

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

            class Regex
            {
                public:
                    //Friends
                    
                    //Definitions

                    //Constructors
                    
                    //Functionality
                    static bool is_valid( const std::string& value );

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
                    Regex( void ) = delete;
                    
                    Regex( const Regex& original ) = delete;
                    
                    virtual ~Regex( void ) = delete;

                    //Functionality

                    //Getters
                    
                    //Setters
                    
                    //Operators
                    Regex& operator =( const Regex& rhs ) = delete;

                    //Properties
            };
        }
    }
}

#endif  /* _RESTBED_DETAIL_HELPERS_REGEX_H */
