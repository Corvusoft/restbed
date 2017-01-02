/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_DETAIL_RESOURCE_IMPL_H
#define _RESTBED_DETAIL_RESOURCE_IMPL_H 1

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
    class Rule;
    class Session;
    
    namespace detail
    {
        //Forward Declarations
        
        struct ResourceImpl
        {
            std::set< std::string > m_paths { };
            
            std::set< std::string > m_methods { };
            
            std::vector< std::shared_ptr< Rule > > m_rules { };
            
            std::multimap< std::string, std::string > m_default_headers { };
            
            std::function< void ( const std::shared_ptr< Session > ) > m_failed_filter_validation_handler = nullptr;
            
            std::function< void ( const int, const std::exception&, const std::shared_ptr< Session > ) > m_error_handler = nullptr;
            
            std::function< void ( const std::shared_ptr< Session >, const std::function< void ( const std::shared_ptr< Session > ) >& ) > m_authentication_handler = nullptr;
            
            std::multimap< std::string, std::pair< std::multimap< std::string, std::string >, std::function< void ( const std::shared_ptr< Session > ) > > > m_method_handlers { };
        };
    }
}

#endif  /* _RESTBED_DETAIL_RESOURCE_IMPL_H */
