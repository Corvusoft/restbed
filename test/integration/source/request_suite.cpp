/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restbed/method>
#include <corvusoft/restbed/request>

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::map;
using std::vector;
using std::string;

//Project Namespaces
using restbed::Request;

//External Namespaces

TEST( Request, constructor )
{
    const Request request;
    
    EXPECT_EQ( "/", request.get_path( ) );
    EXPECT_EQ( "GET", request.get_method( ).to_string( ) );
    EXPECT_EQ( 1.1, request.get_version( ) );

    auto expectation = map< string, string >( );

    EXPECT_EQ( expectation, request.get_headers( ) );
    EXPECT_EQ( expectation, request.get_path_parameters( ) );
    EXPECT_EQ( expectation, request.get_query_parameters( ) );
}

TEST( Request, bytes_accessor )
{
    const Request request;

    string data = "GET / HTTP/1.1\r\n\r\n";
    vector< uint8_t > expectation( data.begin( ), data.end( ) );

    EXPECT_EQ( expectation, request.to_bytes( ) );
}

TEST( Request, method_accessor )
{
    const Request request;
    
    EXPECT_EQ( "GET", request.get_method( ).to_string( ) );
}

TEST( Request, equality_operator )
{
    Request lhs;
    
    Request rhs;
    
    EXPECT_TRUE( lhs == rhs );
}
