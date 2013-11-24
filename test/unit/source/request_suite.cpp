/*
 * Copyright (c) 2013 Corvusoft
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes

//Project Includes
#include <corvusoft/restbed/request>

//External Includes
#include <gtest/gtest.h>

//System Namespaces

//Project Namespaces
using restbed::Request;

//External Namespaces

TEST( Request, default_destructor )
{
    ASSERT_NO_THROW({
        Request* request = new Request( );
        
        delete request;
    });
}
