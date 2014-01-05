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

    enum LogLevel : int
    {
        INFO     = 0x0000008,     
        DEBUG    = 0x0000040,
        FATAL    = 0x0000200,
        ERROR    = 0x0001000,
        WARNING  = 0x0008000,
        SECURITY = 0x0040000
    };
}

#endif  /* _RESTBED_LOG_LEVEL_H */
