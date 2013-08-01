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

#ifndef _RESTBED_URI_H
#define _RESTBED_URI_H 1

//System Includes
#include <memory>
#include <string>

//Project Includes
#include <restbed/bytes>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    namespace detail
    {
        class UriImpl;
    }

    class Uri
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            Uri( const std::string& value );
            
            Uri( const Uri& original );
            
            virtual ~Uri( void );
            
            //Functionality
            std::string to_string( void ) const;

            std::string to_native_path( void ) const;

            static Uri parse( const std::string& value );

            static std::string decode( const Bytes& value );

            static std::string decode( const std::string& value );

            static std::string encode( const Bytes& value );

            static std::string encode( const std::string& value );
            
            //Getters
            int get_port( void ) const; //uint16_t

            std::string get_path( void ) const;

            std::string get_query( void ) const;

            std::string get_scheme( void ) const;

            std::string get_fragment( void ) const;

            std::string get_username( void ) const;

            std::string get_password( void ) const;

            std::string get_authority( void ) const;
            
            //Setters
            
            //Operators

            Uri& operator =( const Uri& rhs );

            bool operator <( const Uri& rhs ) const;

            bool operator >( const Uri& rhs ) const;

            bool operator ==( const Uri& rhs ) const;

            bool operator !=( const Uri& rhs ) const;
            
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
            Uri( void );
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            
            //Properties
            const std::unique_ptr< detail::UriImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_URI_H */
