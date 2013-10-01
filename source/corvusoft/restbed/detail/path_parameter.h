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

#ifndef _RESTBED_DETAIL_PATH_PARAMETER_H
#define _RESTBED_DETAIL_PATH_PARAMETER_H 1

//System Includes
#include <map>
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
        
        class PathParameter
        {
            public:
                //Friends
                
                //Definitions

                //Constructors
                
                //Functionality
                static std::map< std::string, std::string > parse( const std::string& path, const std::string& definition );

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
                PathParameter( void ) = delete;
                
                PathParameter( const PathParameter& original ) = delete;
                
                virtual ~PathParameter( void ) = delete;

                //Functionality

                //Getters
                
                //Setters

                //Operators
                PathParameter& operator =( const PathParameter& rhs ) = delete;

                //Properties
        };
    }
}

#endif  /* _RESTBED_DETAIL_PATH_PARAMETER_H */
