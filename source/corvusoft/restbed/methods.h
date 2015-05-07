/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_METHODS_H
#define _RESTBED_METHODS_H 1

//System Includes
#include <set>
#include <string>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    static std::set< std::string > methods {
    	"GET",
    	"HEAD",
    	"PUT",
    	"POST",
        "DELETE",
        "TRACE",
    	"OPTIONS",
    	"CONNECT",
    };
}

#endif  /* _RESTBED_METHODS_H */