/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_SESSION_MANAGER_IMPL_H
#define _RESTBED_DETAIL_SESSION_MANAGER_IMPL_H 1

//System Includes
#include <map>
#include <memory>
#include <string>

//Project Includes
#include "corvusoft/restbed/session_manager.hpp"

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
        
        struct SessionManagerImpl
        {
            std::map< std::string, std::shared_ptr< Session > > sessions;
        };
    }
}

#endif  /* _RESTBED_DETAIL_SESSION_MANAGER_IMPL_H */
