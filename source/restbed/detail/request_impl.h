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

#ifndef _RESTBED_DETAIL_REQUEST_IMPL_H
#define _RESTBED_DETAIL_REQUEST_IMPL_H 1

//System Includes
#include <map>
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
                
                //Getters
                Uri get_uri( void ) const;
                
                std::string get_method( void ) const;
                
                std::string get_version( void ) const;
                
                std::string get_header( const std::string& name ) const;
                
                std::map< std::string, std::string > get_headers( void ) const;
                
                std::string get_query_parameter( const std::string& name ) const;
                
                std::map< std::string, std::string > get_query_parameters( void ) const;
                
                std::string get_path_parameter( const std::string& name ) const;
                
                std::map< std::string, std::string > get_path_parameters( void ) const;
                
                //Setters //All these methods should be hidden!
                void set_uri( const Uri& value );
                
                void set_method( const std::string& value );
                
                void set_version( const std::string& value );
                
                void set_header( const std::string& name, const std::string& value );
                
                void set_path_parameter( const std::string& name, const std::string& value );
                
                void set_query_parameter( const std::string& name, const std::string& value );
                
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
                std::string m_uri;
                
                std::string m_method;
                
                std::string m_version;
                
                std::map< std::string, std::string > m_headers;
                
                std::map< std::string, std::string > m_path_parameters;
                
                std::map< std::string, std::string > m_query_parameters;
        };
    }
}

#endif  /* _RESTBED_DETAIL_REQUEST_IMPL_H */
