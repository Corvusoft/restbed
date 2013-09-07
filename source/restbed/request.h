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

#ifndef _RESTBED_REQUEST_H
#define _RESTBED_REQUEST_H 1

//System Includes
#include <map>
#include <memory>
#include <string>
#include <istream>
 
//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Method;

    namespace detail
    {
        class RequestImpl;
    }

    class Request
    {
        public:
            //Friends
            
            //Definitions

            //Constructors
            Request( void );
            
            Request( const Request& original );

            virtual ~Request( void );

            //Functionality
            static Request parse( std::istream& socket );

            //Getters
            Method get_method( void ) const;

            std::string get_path( void ) const;

            std::string get_body( void ) const;
            
            std::string get_version( void ) const;
            
            std::string get_header( const std::string& name ) const;
            
            std::map< std::string, std::string > get_headers( void ) const;
            
            std::string get_query_parameter( const std::string& name ) const;
            
            std::map< std::string, std::string > get_query_parameters( void ) const;
            
            std::string get_path_parameter( const std::string& name ) const;
            
            std::map< std::string, std::string > get_path_parameters( void ) const;

            //Setters
        
            //Operators
            Request& operator =( const Request& rhs );

            bool operator <( const Request& rhs ) const;
            
            bool operator >( const Request& rhs ) const;
            
            bool operator ==( const Request& rhs ) const;
            
            bool operator !=( const Request& rhs ) const;

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
            void set_method( const Method& value );

            void set_path( const std::string& value );

            void set_body( const std::string& value );
            
            void set_version( const std::string& value );
            
            void set_headers( const std::map< std::string, std::string >& value );
            
            void set_path_parameter( const std::string& name, const std::string& value );
            
            void set_query_parameters( const std::map< std::string, std::string >& value );

            //Operators

            //Properties
            std::unique_ptr< detail::RequestImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_REQUEST_H */
