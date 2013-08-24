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

#ifndef _RESTBED_DETAIL_URI_IMPL_H
#define _RESTBED_DETAIL_URI_IMPL_H 1

//System Includes
#include <string>

//Project Includes
#include "restbed/bytes.h"

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
        
        class UriImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                UriImpl( void );
                
                UriImpl( const UriImpl& original );
                
                virtual ~UriImpl( void );
                
                //Functionality
                std::string to_string( void ) const;
                
                std::string to_native_path( void ) const;
                
                static std::string decode( const Bytes& value );
                
                static std::string decode( const std::string& value );
                
                static std::string encode( const Bytes& value );
                
                static std::string encode( const std::string& value );
                
                //Getters
                int get_port( void ) const;
                
                std::string get_path( void ) const;
                
                std::string get_query( void ) const;
                
                std::string get_scheme( void ) const;
                
                std::string get_fragment( void ) const;
                
                std::string get_username( void ) const;
                
                std::string get_password( void ) const;
                
                std::string get_authority( void ) const;
                
                //Setters
                void set_uri( const std::string& value );
                
                //Operators
                UriImpl& operator =( const UriImpl& rhs );
                
                bool operator <( const UriImpl& rhs ) const;
                
                bool operator >( const UriImpl& rhs ) const;
                
                bool operator ==( const UriImpl& rhs ) const;
                
                bool operator !=( const UriImpl& rhs ) const;
                
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
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                std::string m_uri;
        };
    }
}

#endif  /* _RESTBED_DETAIL_URI_IMPL_H */
