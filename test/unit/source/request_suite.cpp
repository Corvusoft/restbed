/*
 * Copyright (c) 2013 Corvusoft
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes
#include <map>
#include <string>
#include <vector>

//Project Includes
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

TEST( Request, default_destructor )
{
    ASSERT_NO_THROW({
        Request* request = new Request( );
        
        delete request;
    });
}

TEST( Request, has_header )
{
    const Request request;
    
    EXPECT_TRUE( request.has_header( "Server" ) == false );
}

TEST( Request, has_path_parameter )
{
    const Request request;
    
    EXPECT_TRUE( request.has_header( "login" ) == false );
}
   
TEST( Request, has_query_parameter )
{
    const Request request;
    
    EXPECT_TRUE( request.has_header( "event" ) == false );
}         
           
TEST( Request, version_accessor )
{
    const Request request;
    
    EXPECT_TRUE( request.get_version( ) == 1.1 );
}

TEST( Request, path_accessor )
{
    const Request request;
    
    EXPECT_TRUE( request.get_path( ) == "/" );
}
            
TEST( Request, body_accessor )
{
    const Request request;

    vector< uint8_t > expection;

    EXPECT_TRUE( request.get_body( ) == expection );
}

TEST( Request, header_accessor )
{
    const Request request;
    
    EXPECT_TRUE( request.get_header( "Content-Type" ) == "" );
}

TEST( Request, headers_accessor )
{
    const Request request;

    map< string, string > expections;
    
    EXPECT_TRUE( request.get_headers( ) == expections );
}

TEST( Request, query_parameter_accessor )
{
    const Request request;
    
    EXPECT_TRUE( request.get_query_parameter( "age" ) == "" );
}

TEST( Request, query_parameters_accessor )
{
    const Request request;

    map< string, string > expections;
    
    EXPECT_TRUE( request.get_query_parameters( ) == expections );
}

TEST( Request, path_parameter_accessor )
{
    const Request request;
    
    EXPECT_TRUE( request.get_path_parameter( "sex" ) == "" );
}

TEST( Request, path_parameters_accessor )
{
    const Request request;

    map< string, string > expections;
    
    EXPECT_TRUE( request.get_path_parameters( ) == expections );
}
