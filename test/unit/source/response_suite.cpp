/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <map>
#include <string>
#include <cstdint>
#include <stdexcept>

//Project Includes
#include <corvusoft/restbed/response>

//External Includes
#include <gtest/gtest.h>
#include <corvusoft/framework/bytes>

//System Namespaces
using std::map;
using std::string;
using std::vector;
using std::invalid_argument;

//Project Namespaces
using restbed::Response;
using framework::Bytes;

//External Namespaces

TEST( Response, constructor )
{
    Bytes body;
    double version = 1.1;
    int status = 200;
    string message = "";
    map< string, string > headers;
    
    Response response;
    
    EXPECT_EQ( status, response.get_status_code( ) );
    EXPECT_EQ( body, response.get_body( )  );
    EXPECT_EQ( headers, response.get_headers( ) );
    EXPECT_EQ( message, response.get_status_message( ) );
    EXPECT_EQ( version, response.get_version( ) );
}

TEST( Response, copy_constructor )
{
    int status = 201;
    Bytes body = { 'T', 'e', 's', 't', ' ', 'D', 'a', 't', 'a' };
    map< string, string > headers = { { "api", "1.1v" } };
    string message = "CUSTOM-CREATED";
    double version = 1.0;
    
    Response original;
    original.set_body( body );
    original.set_version( version );
    original.set_status_code( status );
    original.set_status_message( message );
    original.set_headers( headers );
    
    Response copy( original );
    
    EXPECT_EQ( status, copy.get_status_code( ) );
    EXPECT_EQ( body, copy.get_body( )  );
    EXPECT_EQ( headers, copy.get_headers( ) );
    EXPECT_EQ( message, copy.get_status_message( ) );
    EXPECT_EQ( version, copy.get_version( ) );
}

TEST( Response, destructor )
{
    ASSERT_NO_THROW(
    {
        Response* response = new Response( );
        
        delete response;
    } );
}

TEST( Response, to_bytes )
{
    int status = 201;
    Bytes body = { 'T', 'e', 's', 't', ' ', 'D', 'a', 't', 'a' };
    map< string, string > headers = { { "api", "1.1v" }, { "Date", "ignore" } };
    string message = "CUSTOM-CREATED";
    double version = 1.0;
    
    Response response;
    response.set_body( body );
    response.set_version( version );
    response.set_status_code( status );
    response.set_status_message( message );
    response.set_headers( headers );
    
    string bytes = "HTTP/1.0 201 CUSTOM-CREATED\r\nConnection: close\r\nServer: Corvusoft - restbed\r\nContent-Type: text/plain; charset=us-ascii\r\nContent-Length: 9\r\nDate: ignore\r\napi: 1.1v\r\n\r\nTest Data";
    
    EXPECT_EQ( Bytes( bytes.begin( ), bytes.end( ) ), response.to_bytes( ) );
}

TEST( Response, modify_body )
{
    string data = "Super important test data.";
    Bytes body( data.begin( ), data.end( ) );
    
    Response response;
    response.set_body( body );
    
    EXPECT_EQ( body, response.get_body( ) );
}

TEST( Response, modify_version )
{
    double version = 1.2;
    
    Response response;
    response.set_version( version );
    
    EXPECT_EQ( version, response.get_version( ) );
}

TEST( Response, modify_status_code )
{
    int status = 404;
    
    Response response;
    response.set_status_code( status );
    
    EXPECT_EQ( status, response.get_status_code( ) );
}

TEST( Response, modify_status_message )
{
    string message = "CUSTOM-STATUS";
    
    Response response;
    response.set_status_message( message );
    
    EXPECT_EQ( message, response.get_status_message( ) );
}

TEST( Response, modify_header )
{
    string name = "Test Name.";
    string value = "Test Value.";
    
    Response response;
    response.set_header( name, value );
    
    EXPECT_EQ( value, response.get_header( name ) );
}

TEST( Response, modify_case_insensitive_header )
{
    string name = "Test Name.";
    string value = "Test Value.";
    
    Response response;
    response.set_header( name, value );
    
    EXPECT_EQ( value, response.get_header( "test name." ) );
}

TEST( Response, modify_headers )
{
    map< string, string > headers =
    {
        { "1", "2" },
        { "3", "4" }
    };
    
    Response response;
    response.set_headers( headers );
    
    EXPECT_EQ( headers, response.get_headers( ) );
}

TEST( Response, assignment_operator )
{
    int status = 201;
    Bytes body = { 'T', 'e', 's', 't', ' ', 'D', 'a', 't', 'a' };
    map< string, string > headers = { { "api", "1.1v" } };
    string message = "CUSTOM-CREATED";
    double version = 1.0;
    
    Response original;
    original.set_body( body );
    original.set_version( version );
    original.set_status_code( status );
    original.set_status_message( message );
    original.set_headers( headers );
    
    Response copy = original;
    
    EXPECT_EQ( status, copy.get_status_code( ) );
    EXPECT_EQ( body, copy.get_body( )  );
    EXPECT_EQ( headers, copy.get_headers( ) );
    EXPECT_EQ( message, copy.get_status_message( ) );
    EXPECT_EQ( version, copy.get_version( ) );
}

TEST( Response, less_than_operator )
{
    Response lhs;
    lhs.set_status_code( 201 );
    
    Response rhs;
    rhs.set_status_code( 301 );
    
    EXPECT_TRUE( lhs < rhs );
}

TEST( Response, greater_than_operator )
{
    Response lhs;
    lhs.set_status_code( 500 );
    
    Response rhs;
    rhs.set_status_code( 401 );
    
    EXPECT_TRUE( lhs > rhs );
}

TEST( Response, equality_operator )
{
    Response lhs;
    lhs.set_header( "name", "value" );
    
    Response rhs;
    rhs.set_header( "name", "value" );
    
    EXPECT_TRUE( lhs == rhs );
}

TEST( Response, inequality_operator )
{
    Response lhs;
    lhs.set_body( "some data" );
    
    Response rhs;
    rhs.set_body( "data some" );
    
    EXPECT_TRUE( lhs != rhs );
}
