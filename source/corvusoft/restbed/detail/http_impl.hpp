/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_DETAIL_HTTP_H
#define _RESTBED_DETAIL_HTTP_H 1

//System Includes
#include <string>
#include <memory>
#include <functional>
#include <system_error>

//Project Includes
#include <corvusoft/restbed/byte.hpp>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Fordward Declarations
    class Request;
    class Response;
    class Settings;
    class SSLSettings;
    
    namespace detail
    {
        //Forward Declarations
        
        class HttpImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                static Bytes to_bytes( const std::shared_ptr< Request >& value );
                
                static void socket_setup( const std::shared_ptr< Request >& request, const std::shared_ptr< const Settings >& settings );
#ifdef BUILD_SSL
                static void ssl_socket_setup( const std::shared_ptr< Request >& request, const std::shared_ptr< const SSLSettings >& settings );
#endif
                static void request_handler( const std::error_code& error, const std::shared_ptr< Request >& request, const std::function< void ( const std::shared_ptr< Request >, const std::shared_ptr< Response > ) >& callback );
                
                static void write_handler( const std::error_code& error, const std::size_t length, const std::shared_ptr< Request >& request, const std::function< void ( const std::shared_ptr< Request >, const std::shared_ptr< Response > ) >& callback );
                
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
                HttpImpl( void ) = delete;
                
                virtual ~HttpImpl( void ) = delete;
                
                HttpImpl( const HttpImpl& original ) = delete;
                
                //Functionality
                static const std::shared_ptr< Response > create_error_response( const std::shared_ptr< Request >& request, const std::string& message );
                
                static void read_status_handler( const std::error_code& error, const std::size_t length, const std::shared_ptr< Request >& request, const std::function< void ( const std::shared_ptr< Request >, const std::shared_ptr< Response > ) >& callback );
                
                static void read_headers_handler( const std::error_code& error, const std::size_t length, const std::shared_ptr< Request >& request, const std::function< void ( const std::shared_ptr< Request >, const std::shared_ptr< Response > ) >& callback );
                
                //Getters
                
                //Setters
                
                //Operators
                HttpImpl& operator =( const HttpImpl& value ) = delete;
                
                //Properties
        };
    }
}

#endif  /* _RESTBED_DETAIL_HTTP_H */
