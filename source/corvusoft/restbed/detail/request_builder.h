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

#ifndef _RESTBED_DETAIL_REQUEST_BUILDER_H
#define _RESTBED_DETAIL_REQUEST_BUILDER_H 1

//System Includes
#include <map>
#include <memory>
#include <string>
#include <istream>

//Project Includes

//External Includes
#include <asio.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    namespace detail
    {
        //Forward Declarations
        
        class RequestBuilder : private Request
        {
            public:
                //Friends
                
                //Definitions

                //Constructors
                RequestBuilder( void );
                
                RequestBuilder( const RequestBuilder& original );
                
                virtual ~RequestBuilder( void );
                
                //Functionality
                Request build( void ) const;

                void parse( std::shared_ptr< asio::ip::tcp::socket >& socket );
                                
                void parse_path_parameters( const std::string& definition );

                //Getters
                
                //Setters

                //Operators
                
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
                static double parse_http_version( std::istream& socket );

                static std::string parse_http_path( std::istream& socket );

                static std::string parse_http_body( std::istream& socket );
                
                static std::string parse_http_method( std::istream& socket );
            
                static std::map< std::string, std::string > parse_http_headers( std::istream& socket );

                static std::map< std::string, std::string > parse_http_query_parameters( std::istream& socket );

                //Getters
                
                //Setters

                //Operators
                
                //Properties
        };
    }
}

#endif  /* _RESTBED_DETAIL_REQUEST_BUILDER_H */
