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

#ifndef _RESTBED_DETAIL_METHOD_IMPL_H
#define _RESTBED_DETAIL_METHOD_IMPL_H 1

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
        
        class MethodImpl
        {
            public:
                //Friends
                
                //Definitions

                //Constructors
                MethodImpl( const char* value );
                
                MethodImpl( const std::string& value );
                
                MethodImpl( const MethodImpl& original );

                virtual ~MethodImpl( void );
                
                //Functionality
                std::string to_string( void ) const;

                //Getters
                
                //Setters

                //Operators
                bool operator <( const MethodImpl& rhs ) const;
                
                bool operator >( const MethodImpl& rhs ) const;
                
                bool operator ==( const MethodImpl& rhs ) const;
                
                bool operator !=( const MethodImpl& rhs ) const;

                MethodImpl& operator =( const MethodImpl& rhs );

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
                
                //Functionality
                void setup( const std::string& value );
                
                //Getters
                
                //Setters
                
                //Operators

                //Properties
                std::string m_value;
        };
    }
}

#endif  /* _RESTBED_DETAIL_METHOD_IMPL_H */
