/*
 * Copyright (c) 2013 Corvusoft
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes
#include <string>
#include <stdexcept>

//Project Includes
#include <corvusoft/restbed/resource>

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::string;
using std::invalid_argument;

//Project Namespaces

//External Namespaces
using restbed::Resource;

TEST( Resource, copy_constructor )
{
    const string path = "/event/.*";

    Resource original;
    original.set_path( path );
    original.set_header_filters( filters );
    origiinal.set_method_handler( "POST", func );

    const Resource copy( original );
    
    EXPECT_TRUE( copy.get_path( ) == path );
}

TEST( Resource, method_handler_accessor )
{
    Resource resource;
    resource.set_method_handler( "GET", func );

    EXPECT_TRUE( resource.get_method_handler( ) == func );
}
