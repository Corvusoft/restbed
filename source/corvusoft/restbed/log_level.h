/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_LOG_LEVEL_H
#define _RESTBED_LOG_LEVEL_H 1

//System Includes

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    enum LogLevel :
    int
    {
        INFO = 0000,
        DEBUG = 1000,
        FATAL = 2000,
        ERROR = 3000,
        WARNING = 4000,
        SECURITY = 5000
    };
}

#endif  /* _RESTBED_LOG_LEVEL_H */
