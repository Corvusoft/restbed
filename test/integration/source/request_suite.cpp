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
    
    EXPECT_TRUE( request.get_path( ) == "/" );
    EXPECT_TRUE( request.get_method( ) == "GET" );
    EXPECT_TRUE( request.get_version( ) == 1.1 );

    auto expectation = map< string, string >( );

    EXPECT_TRUE( request.get_headers( ) == expectation);
    EXPECT_TRUE( request.get_path_parameters( ) == expectation );
    EXPECT_TRUE( request.get_query_parameters( ) == expectation );
}

TEST( Request, bytes_accessor )
{
    const Request request;

    string data = "GET / HTTP/1.1\r\n\r\n";
    vector< uint8_t > expection( data.begin( ), data.end( ) );

    EXPECT_TRUE( request.to_bytes( ) == expection );
}

TEST( Request, method_accessor )
{
    const Request request;
    
    EXPECT_TRUE( request.get_method( ) == "GET" );
}

TEST( Request, equality_operator )
{
    Request lhs;
    
    Request rhs;
    
    EXPECT_TRUE( lhs == rhs );
}
