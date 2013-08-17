/*
 * Site: restbed.corvusoft.co.uk
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

#ifndef _RESTBED_METHOD_H
#define _RESTBED_METHOD_H 1

//System Includes
#include <memory>
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
        class MethodImpl;
    }

    class Method
    {
        public:
            //Friends
            
            //Definitions

            //Constructors
            Method( const char* value );
            
            Method( const std::string& value );
            
            Method( const Method& original );

            virtual ~Method( void );

            //Functionality
            std::string to_string( void ) const;
        
            static Method parse( const std::string& value );

            //Getters

            //Setters

            //Operators
            Method& operator =( const Method& rhs );

            bool operator <( const Method& rhs ) const;
            
            bool operator >( const Method& rhs ) const;
            
            bool operator ==( const Method& rhs ) const;
            
            bool operator !=( const Method& rhs ) const;

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
            Method( void );
        
            //Getters
            
            //Setters
            
            //Operators

            //Properties
            std::unique_ptr< detail::MethodImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_METHOD_H */
