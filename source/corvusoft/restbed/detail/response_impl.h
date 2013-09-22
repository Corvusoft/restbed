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

#ifndef _RESTBED_DETAIL_RESPONSE_IMPL_H
#define _RESTBED_DETAIL_RESPONSE_IMPL_H 1

//System Includes
#include <map>
#include <string>
 
//Project Includes
#include <corvusoft/restbed/bytes>

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
                Bytes to_bytes( void ) const;

                //Getters
                Bytes get_body( void ) const;

                int get_status_code( void ) const;

                std::string get_header( const std::string& name ) const;

                std::map< std::string, std::string > get_headers( void ) const;

                //Setters
                void set_body( const Bytes& value );

                void set_body( const std::string& value );

                void set_status_code( const int value );

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
                bool has_header( const std::string& name ) const;

                std::string generate_status_section( void ) const;

                std::string generate_header_section( void ) const;

                std::string generate_default_date_header( void ) const;

                std::string generate_default_server_header( void ) const;

                std::string generate_default_connection_header( void ) const;

                std::string generate_default_content_type_header( void ) const;

                std::string generate_default_content_length_header( void ) const;
                
                //Getters
                
                //Setters
                
                //Operators

                //Properties
                Bytes m_body;

                int m_status_code;
        
                std::map< std::string, std::string > m_headers;
        };
    }
}

#endif  /* _RESTBED_DETAIL_RESPONSE_IMPL_H */
