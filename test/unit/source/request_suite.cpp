/*
 * Copyright (c) 2013 Corvusoft
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes
#include <map>
#include <string>

//Project Includes

//External Includes
#include <gtest/gtest.h>
#include <restbed/request>

//System Namespaces
using std::map;
using std::string;

//Project Namespaces

//External Namespaces
using restbed::Request;

TEST( Request, constructor )
{
    const Request request;
    
    EXPECT_TRUE( request.get_method( ) == "" );
    EXPECT_TRUE( request.get_version( ) == "" );

    auto expectation = map< string, string >( );

    EXPECT_TRUE( request.get_headers( ) == expectation);
    EXPECT_TRUE( request.get_path_parameters( ) == expectation );
    EXPECT_TRUE( request.get_query_parameters( ) == expectation );
}

TEST( Request, copy_constructor )
{
    const string version = "1.1";

    Request original;
    original.set_version( version );

    const Request copy( original );
    
    EXPECT_TRUE( copy.get_version( ) == version );
}

TEST( Request, default_destructor )
{
    ASSERT_NO_THROW({
        Request* request = new Request( );
        
        delete request;
    });
}

TEST( Request, method_accessor )
{
    const string method = "GET";

    Request request;
    request.set_method( method );

    EXPECT_TRUE( request.get_method( ) == method );
}

TEST( Request, version_accessor )
{
    const string version = "1.1";

    Request request;
    request.set_version( version );

    EXPECT_TRUE( request.get_version( ) == version );
}

TEST( Request, headers_accessor )
{
    const map< string, string > headers = {
        { "name", "value" }
    };

    Request request;
    request.set_header( "name", "value" );

    EXPECT_TRUE( request.get_headers( ) == headers );
}

TEST( Request, assignment_operator )
{
    Request original;
    original.set_method( "POST" );
    original.set_version( "1.0" );

    Request copy = original;

    EXPECT_TRUE( original == copy );
}
