/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_RESPONSE_BUILDER_IMPL_H
#define _RESTBED_DETAIL_RESPONSE_BUILDER_IMPL_H 1

//System Includes
#include <map>
#include <memory>
#include <string>
#include <istream>

//Project Includes
#include "corvusoft/restbed/detail/response_impl.h"

//External Includes
#include <asio.hpp>
#include <corvusoft/framework/bytes>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    namespace detail
    {
        //Forward Declarations
        
        class ResponseBuilderImpl : private ResponseImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                    
                //Functionality
                static void write( const Response& response, const std::shared_ptr< asio::ip::tcp::socket >& socket );
                
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
                ResponseBuilderImpl( void );

                ResponseBuilderImpl( const ResponseBuilderImpl& original );

                virtual ~ResponseBuilderImpl( void );

                //Functionality
                static std::string generate_status_section( const Response& response );

                static std::string generate_header_section( const Response& response );

                static std::string generate_default_date_header( const Response& response );

                static std::string generate_default_server_header( const Response& response );

                static std::string generate_default_connection_header( const Response& response );

                static std::string generate_default_content_type_header( const Response& response );

                static std::string generate_default_content_length_header( const Response& response );

                //Getters

                //Setters
                
                //Operators
                ResponseBuilderImpl& operator =( const ResponseBuilderImpl& value );
                
                //Properties
        };
    }
}

#endif  /* _RESTBED_DETAIL_RESPONSE_BUILDER_IMPL_H */
