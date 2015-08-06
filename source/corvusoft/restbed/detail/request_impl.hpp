/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_REQUEST_IMPL_H
#define _RESTBED_DETAIL_REQUEST_IMPL_H 1

//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restbed/byte.hpp>

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
        
        struct RequestImpl
        {
            Bytes body = { };
            
            double version = 1.1;
            
            std::string path = "/";
            
            std::string method = "GET";
            
            std::string protocol = "HTTP";
            
            std::multimap< std::string, std::string > headers = { };
            
            std::map< std::string, std::string > path_parameters = { };
            
            std::multimap< std::string, std::string > query_parameters = { };
        };
    }
}

#endif  /* _RESTBED_DETAIL_REQUEST_IMPL_H */
