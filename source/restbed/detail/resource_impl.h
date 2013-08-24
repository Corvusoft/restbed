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

#ifndef _RESTBED_DETAIL_RESOURCE_IMPL_H
#define _RESTBED_DETAIL_RESOURCE_IMPL_H 1

//System Includes
#include <map>
#include <string>
#include <functional>
#include <iostream> //debug
 
//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Method;
    class Request;
    class Response;
    
    namespace detail
    {
        //Forward Declarations

        class ResourceImpl
        {
            public:
                //Friends
                
                //Definitions

                //Constructors
                ResourceImpl( void );
            
                ResourceImpl( const ResourceImpl& original );
            
                virtual ~ResourceImpl( void );

                //Functionality

                //Getters
                std::string get_path( void ) const;

                std::string get_content_type( void ) const;

                std::function< Response ( Request& ) > get_method_handler( const Method& method ) const;

                //Setters
                void set_path( const std::string& value );

                void set_content_type( const std::string& value );
                
                void set_method_handler( const Method& method, const std::function< Response ( Request& ) >& callback ); //const Request?

                //Operators
                bool operator <( const ResourceImpl& rhs ) const;
                
                bool operator >( const ResourceImpl& rhs ) const;
                
                bool operator ==( const ResourceImpl& rhs ) const;
                
                bool operator !=( const ResourceImpl& rhs ) const;

                ResourceImpl& operator =( const ResourceImpl& rhs );

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
                void setup( void );

                static Response default_handler( const Request& request );

                static Response default_trace_handler( const Request& request );

                static Response default_options_handler( const Request& request );
                
                //Getters
                
                //Setters
                
                //Operators

                //Properties
                std::string m_path;
        
                std::string m_content_type;
            
                std::map< std::string, std::function< Response ( Request& ) > > m_method_handles;
        };
    }
}

#endif  /* _RESTBED_DETAIL_RESOURCE_IMPL_H */
