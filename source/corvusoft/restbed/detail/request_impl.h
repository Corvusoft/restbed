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

#ifndef _RESTBED_DETAIL_REQUEST_IMPL_H
#define _RESTBED_DETAIL_REQUEST_IMPL_H 1

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
    
    namespace detail
    {
        //Forward Declarations
        
        class RequestImpl
        {
            public:
                //Friends
                
                //Definitions

                //Constructors
                RequestImpl( void );
                
                RequestImpl( const RequestImpl& original );
                
                virtual ~RequestImpl( void );
                
                //Functionality
                bool has_header( const std::string& name ) const;

                bool has_path_parameter( const std::string& name ) const;

                bool has_query_parameter( const std::string& name ) const;
                
                //Getters
                double get_version( void ) const;

                std::string get_path( void ) const;

                std::string get_body( void ) const;
                
                std::string get_method( void ) const;
                
                std::string get_header( const std::string& name ) const;
                
                std::map< std::string, std::string > get_headers( void ) const;
                
                std::string get_query_parameter( const std::string& name ) const;
                
                std::map< std::string, std::string > get_query_parameters( void ) const;
                
                std::string get_path_parameter( const std::string& name ) const;
                
                std::map< std::string, std::string > get_path_parameters( void ) const;
                
                //Setters
                void set_version( const double value );

                void set_path( const std::string& value );

                void set_body( const std::string& value );
                
                void set_method( const std::string& value );
                
                void set_headers( const std::map< std::string, std::string >& value );
                
                void set_path_parameter( const std::string& name, const std::string& value );

                void set_query_parameters( const std::map< std::string, std::string >& value );

                //Operators
                bool operator <( const RequestImpl& rhs ) const;
                
                bool operator >( const RequestImpl& rhs ) const;
                
                bool operator ==( const RequestImpl& rhs ) const;
                
                bool operator !=( const RequestImpl& rhs ) const;
                
                RequestImpl& operator =( const RequestImpl& rhs );
                
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

                double m_version;

                std::string m_path;

                std::string m_body;
                
                std::string m_method;
                
                std::map< std::string, std::string > m_headers;
                
                std::map< std::string, std::string > m_path_parameters;
                
                std::map< std::string, std::string > m_query_parameters;
        };
    }
}

#endif  /* _RESTBED_DETAIL_REQUEST_IMPL_H */
