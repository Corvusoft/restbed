/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_DETAIL_STATUS_CODE_IMPL_H
#define _RESTBED_DETAIL_STATUS_CODE_IMPL_H 1

//System Includes
#include <map>
#include <string>

//Project Includes
#include "corvusoft/restbed/status_code.h"

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
        
        class StatusCodeImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                static bool is_successful( const StatusCode::Value value );

                static bool is_redirection( const StatusCode::Value value );

                static bool is_informational( const StatusCode::Value value );

                static bool is_client_error( const StatusCode::Value value );

                static bool is_server_error( const StatusCode::Value value );

                static int parse( const std::string& value );
                
                static std::string to_string( const int code );
                
                //Getters
                static std::map< int, std::string > get_mappings( void );
                
                //Setters
                static void set_mappings( const std::map< int, std::string >& values );
                
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
                StatusCodeImpl( void ) = delete;
                
                StatusCodeImpl( const StatusCodeImpl& original ) = delete;
                
                virtual ~StatusCodeImpl( void ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                StatusCodeImpl& operator =( const StatusCodeImpl& value ) = delete;
                
                //Properties
                static std::map< int, std::string > m_mappings;
        };
    }
}

#endif  /* _RESTBED_DETAIL_STATUS_CODE_IMPL_H */
