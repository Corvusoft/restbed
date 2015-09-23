/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_URI_IMPL_H
#define _RESTBED_DETAIL_URI_IMPL_H 1

//System Includes
#include <string>

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
        
        struct UriImpl
        {
            std::string uri = "";
            
            bool relative = false;
        };
    }
}

#endif  /* _RESTBED_DETAIL_URI_IMPL_H */
