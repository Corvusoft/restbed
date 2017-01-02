/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_HTTP_H
#define _RESTBED_HTTP_H 1

//System Includes
#include <string>
#include <memory>
#include <future>
#include <cstddef>
#include <functional>

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
    class Settings;
    
    class Http
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            
            //Functionality
            static Bytes to_bytes( const std::shared_ptr< Request >& value );
            
            static Bytes to_bytes( const std::shared_ptr< Response >& value );
            
            static void close( const std::shared_ptr< Request >& value );
            
            static bool is_open( const std::shared_ptr< Request >& value );
            
            static bool is_closed( const std::shared_ptr< Request >& value );
            
            static const std::shared_ptr< Response > sync( const std::shared_ptr< Request > request, const std::shared_ptr< const Settings >& settings = std::make_shared< Settings >( ) );
            
            static std::future< std::shared_ptr< Response > > async( const std::shared_ptr< Request > request, const std::function< void ( const std::shared_ptr< Request >, const std::shared_ptr< Response > ) >& callback, const std::shared_ptr< const Settings >& settings = std::make_shared< Settings >( ) );
            
            static Bytes fetch( const std::size_t length, const std::shared_ptr< Response >& response );
            
            static Bytes fetch( const std::string& delimiter, const std::shared_ptr< Response >& response );
            
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
