/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <map>
#include <string>
#include <vector>
#include <cstdint>

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
    ASSERT_NO_THROW(
    {
        Request* request = new Request( );
        
        delete request;
    } );
}

TEST( Request, has_header )
{
    const Request request;
    
    EXPECT_EQ( false, request.has_header( "Server" ) );
}

TEST( Request, has_path_parameter )
{
    const Request request;
    
    EXPECT_EQ( false, request.has_header( "login" ) );
}

TEST( Request, has_query_parameter )
{
    const Request request;
    
    EXPECT_EQ( false, request.has_header( "event" ) );
}

TEST( Request, version_accessor )
{
    const Request request;
    
    EXPECT_EQ( 1.1, request.get_version( ) );
}

TEST( Request, path_accessor )
{
    const Request request;
    
    EXPECT_EQ( "/", request.get_path( ) );
}

TEST( Request, body_accessor )
{
    const Request request;
    
    vector< uint8_t > expectation;
    
    EXPECT_EQ( expectation, request.get_body( ) );
}

TEST( Request, header_accessor )
{
    const Request request;
    
    EXPECT_EQ( "", request.get_header( "Content-Type" ) );
}

TEST( Request, headers_accessor )
{
    const Request request;
    
    map< string, string > expectation;
    
    EXPECT_EQ( expectation, request.get_headers( ) );
}

TEST( Request, query_parameter_accessor )
{
    const Request request;
    
    EXPECT_EQ( "", request.get_query_parameter( "age" ) );
}

TEST( Request, query_parameters_accessor )
{
    const Request request;
    
    map< string, string > expectation;
    
    EXPECT_EQ( expectation, request.get_query_parameters( ) );
}

TEST( Request, path_parameter_accessor )
{
    const Request request;
    
    EXPECT_EQ( "", request.get_path_parameter( "sex" ) );
}

TEST( Request, path_parameters_accessor )
{
    const Request request;
    
    map< string, string > expectation;
    
    EXPECT_EQ( expectation, request.get_path_parameters( ) );
}
