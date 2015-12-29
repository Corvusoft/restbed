/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_HTTP_H
#define _RESTBED_HTTP_H 1

//System Includes
#include <string>
#include <memory>
#include <cstddef>

//Project Includes
#include <corvusoft/restbed/byte.hpp>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Request;
    class Response;
    class SSLSettings;
    
    class Http
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            
            //Functionality
            static std::shared_ptr< const Response > sync( const std::shared_ptr< const Request >& request );

            static Bytes fetch( const std::size_t length, const std::shared_ptr< const Response >& response );

            static Bytes fetch( const std::string& delimiter, const std::shared_ptr< const Response >& response );

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
            Http( void ) = delete;
            
            virtual ~Http( void ) = delete;

            Http( const Http& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            Http& operator =( const Http& value ) = delete;
            
            //Properties
    };
}

#endif  /* _RESTBED_HTTP_H */
