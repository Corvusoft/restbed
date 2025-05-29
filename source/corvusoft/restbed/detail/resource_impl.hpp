/*
 * Copyright 2013-2025, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <set>
#include <string>
#include <vector>
#include <functional>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Session;
    
    namespace detail
    {
        //Forward Declarations
        
        struct ResourceImpl
        {
            std::set< std::string > m_paths { };
            
            std::set< std::string > m_methods { };
            
            std::multimap< std::string, std::string > m_default_headers { };
            
            std::function< void ( const int, const std::exception&, const std::shared_ptr< Session > ) > m_error_handler = nullptr;
            
            std::function< void ( const std::shared_ptr< Session >, const std::function< void ( const std::shared_ptr< Session > ) >& ) > m_authentication_handler = nullptr;
            
            std::multimap< std::string, std::function< void ( const std::shared_ptr< Session > ) > > m_method_handlers { };
        };
    }
}
