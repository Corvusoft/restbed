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

#ifndef _RESTBED_DETAIL_RESPONSE_IMPL_H
#define _RESTBED_DETAIL_RESPONSE_IMPL_H 1

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

        class ResponseImpl
        {
            public:
                //Friends
                
                //Definitions

                //Constructors
                ResponseImpl( void );

                ResponseImpl( const ResponseImpl& original );
                
                virtual ~ResponseImpl( void );

                //Functionality
                            
                //Getters
                std::string get_data( void ) const;

                std::string get_header( const std::string& name ) const;

                std::map< std::string, std::string > get_headers( void ) const;

                //Setters
                void set_data( const std::string& value ); //Bytes

                void set_header( const std::string& name, const std::string& value );

                void set_headers( const std::map< std::string, std::string >& values );

                //Operators
                bool operator <( const ResponseImpl& rhs ) const;
                
                bool operator >( const ResponseImpl& rhs ) const;
                
                bool operator ==( const ResponseImpl& rhs ) const;
                
                bool operator !=( const ResponseImpl& rhs ) const;

                ResponseImpl& operator =( const ResponseImpl& rhs );

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
                std::string m_data;
        
                std::map< std::string, std::string > m_headers;
        };
    }
}

#endif  /* _RESTBED_DETAIL_RESPONSE_IMPL_H */
