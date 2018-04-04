/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <memory>
#include <string>

//Project Includes
#include "corvusoft/restbed/byte.hpp"

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Request;
    
    namespace detail
    {
        //Forward Declarations
        
        struct ResponseImpl
        {
            Bytes m_body { };
            
            double m_version = 1.1;
            
            int m_status_code = 0;
            
            Request* m_request = nullptr;
            
            std::string m_protocol = "HTTP";
            
            std::string m_status_message = "";
            
            std::multimap< std::string, std::string > m_headers { };
        };
    }
}
