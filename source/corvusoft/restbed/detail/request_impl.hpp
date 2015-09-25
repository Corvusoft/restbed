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
            Bytes m_body { };
            
            double m_version = 1.1;
            
            std::string m_path = "/";
            
            std::string m_method = "GET";
            
            std::string m_protocol = "HTTP";
            
            std::multimap< std::string, std::string > m_headers { };
            
            std::map< std::string, std::string > m_path_parameters { };
            
            std::multimap< std::string, std::string > m_query_parameters { };
        };
    }
}

#endif  /* _RESTBED_DETAIL_REQUEST_IMPL_H */
