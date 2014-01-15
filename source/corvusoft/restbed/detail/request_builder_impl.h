/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_DETAIL_REQUEST_BUILDER_IMPL_H
#define _RESTBED_DETAIL_REQUEST_BUILDER_IMPL_H 1

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
        
        class RequestBuilderImpl : private Request
        {
            public:
                //Friends
                
                //Definitions

                //Constructors
                RequestBuilderImpl( std::istream& socket );
                
                RequestBuilderImpl( const RequestBuilderImpl& original );
                
                virtual ~RequestBuilderImpl( void );
                
                //Functionality
                Request build( void ) const;

                void parse( std::istream& socket );

                //Getters
                
                //Setters
                void set_origin( const std::string& value );
                
                void set_path_parameters( const std::map< std::string, std::string >& parameters );

                //Operators
                RequestBuilderImpl& operator =( const RequestBuilderImpl& rhs );

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
                static Bytes parse_http_body( std::istream& socket );
                
                static double parse_http_version( std::istream& socket );

                static std::string parse_http_path( std::istream& socket );
                
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

#endif  /* _RESTBED_DETAIL_REQUEST_BUILDER_IMPL_H */
