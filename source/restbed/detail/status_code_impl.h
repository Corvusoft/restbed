/*
 * Site: restbed.net
 * Author: Ben Crowhurst
 *
 * Copyright (c) 2013 Restbed Core Development Team and Community Contributors
 *
 * This file is part of Restbed.
 *
 * AppOn is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AppOn is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with AppOn.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _RESTBED_DETAIL_STATUS_CODE_IMPL_H
#define _RESTBED_DETAIL_STATUS_CODE_IMPL_H 1

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
        
        class StatusCodeImpl
        {
            public:
                //Friends
                
                //Definitions

                //Constructors
                
                //Functionality
                static std::string to_string( const int code );

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
                StatusCodeImpl( void ) = delete;
                
                StatusCodeImpl( const StatusCodeImpl& original ) = delete;
                
                virtual ~StatusCodeImpl( void ) = delete;

                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                StatusCodeImpl& operator =( const StatusCodeImpl& rhs ) = delete;

                //Properties
                static std::map< int, std::string> m_strings;
        };
    }
}

#endif  /* _RESTBED_DETAIL_STATUS_CODE_IMPL_H */
