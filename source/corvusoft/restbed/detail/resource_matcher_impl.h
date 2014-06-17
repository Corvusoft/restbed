/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_DETAIL_RESOURCE_MATCHER_IMPL_H
#define _RESTBED_DETAIL_RESOURCE_MATCHER_IMPL_H 1

//System Includes
#include <regex>
#include <vector>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Request;
    class Resource;
    
    namespace detail
    {
        //Forward Declarations
        
        class ResourceMatcherImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                ResourceMatcherImpl( const Request& request );
                
                ResourceMatcherImpl( const ResourceMatcherImpl& original );
                
                virtual ~ResourceMatcherImpl( void );
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                bool operator ( )( const Resource& resource ) const;
                
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
                bool compare_path( const Request& request, const Resource& resource ) const;
                
                bool compare_headers( const Request& request, const Resource& resource ) const;
                
                //Getters
                
                //Setters
                
                //Operators
                ResourceMatcherImpl& operator =( const ResourceMatcherImpl& value ) = delete;
                
                //Properties
                const Request& m_request;
        };
    }
}

#endif  /* _RESTBED_DETAIL_RESOURCE_MATCHER_IMPL_H */
