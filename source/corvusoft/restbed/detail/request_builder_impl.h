/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_REQUEST_BUILDER_IMPL_H
#define _RESTBED_DETAIL_REQUEST_BUILDER_IMPL_H 1

//System Includes
#include <map>
#include <istream>

//Project Includes
#include "corvusoft/restbed/detail/request_impl.h"

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
        
        class RequestBuilderImpl : public Request
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                RequestBuilderImpl( void ); //remove/hide
                
                RequestBuilderImpl( const RequestBuilderImpl& original ); //remove
                
                virtual ~RequestBuilderImpl( void );
                
                //Functionality
                static std::shared_ptr< Request > build( std::istream& stream );

                //Getters
                
                //Setters

                //Operators
                RequestBuilderImpl& operator =( const RequestBuilderImpl& value ); //remove
                
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
                static const std::map< std::string, std::string > parse_request_line( std::istream& stream );

                static const std::multimap< std::string, std::string > parse_request_headers( std::istream& stream );

                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
        };
    }
}

#endif  /* _RESTBED_DETAIL_REQUEST_BUILDER_IMPL_H */
