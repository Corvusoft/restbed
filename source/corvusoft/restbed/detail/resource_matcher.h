/*
 * Copyright (c) 2013 Corvusoft
 */

#ifndef _RESTBED_DETAIL_RESOURCE_MATCHER_H
#define _RESTBED_DETAIL_RESOURCE_MATCHER_H 1

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

        class ResourceMatcher
        {
            public:
                //Friends
                
                //Definitions

                //Constructors
                ResourceMatcher( const Request& request );
            
                ResourceMatcher( const ResourceMatcher& original );
            
                virtual ~ResourceMatcher( void );

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
                ResourceMatcher& operator =( const ResourceMatcher& rhs ) = delete;

                //Properties
                const Request& m_request;
        };
    }
}

#endif  /* _RESTBED_DETAIL_RESOURCE_MATCHER_H */
