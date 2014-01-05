/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes
#include <map>
#include <string>
#include <cstdint>
#include <stdexcept>

//Project Includes
#include <corvusoft/restbed/response>

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::map;
using std::string;
using std::vector;
using std::invalid_argument;

//Project Namespaces
using restbed::Response;

//External Namespaces

TEST( Response, constructor )
{
    const Response response;

    auto body_expection = vector< uint8_t > ( );
    auto header_expectation = map< string, string >( );
    
    EXPECT_EQ( 200, response.get_status_code( ) );
    EXPECT_EQ( body_expection, response.get_body( )  );
    EXPECT_EQ( header_expectation, response.get_headers( ) );
}

TEST( Response, copy_constructor )
{
    const vector< uint8_t > data = { 'T', 'e', 's', 't', ' ', 'D', 'a', 't', 'a' };

    Response original;
    original.set_body( data );

    const Response copy( original );
    
    EXPECT_EQ( data, copy.get_body( ) );
}

TEST( Response, default_destructor )
{
    ASSERT_NO_THROW({
        Response* response = new Response( );
        
        delete response;
    });
}

TEST( Response, body_accessor )
{
    const string data = "Super important test data.";
    const vector< uint8_t > body( data.begin( ), data.end( ) );

    Response response;
    response.set_body( body );

    EXPECT_EQ( body, response.get_body( ) );
}

TEST( Response, status_code_accessor )
{
    const int status = 404;

    Response response;
    response.set_status_code( status );

    EXPECT_EQ( status, response.get_status_code( ) );
}

TEST( Response, header_accessor )
{
    const string name = "Test Name.";
    const string value = "Test Value.";

    Response response;
    response.set_header( name, value );

    EXPECT_EQ( value, response.get_header( name ) );
}

TEST( Response, case_insensitive_header_accessor )
{
    const string name = "Test Name.";
    const string value = "Test Value.";

    Response response;
    response.set_header( name, value );

    EXPECT_EQ( value, response.get_header( "test name." ) );
}

TEST( Response, headers_accessor )
{
    const map< string, string > headers = {
        { "1", "2" },
        { "3", "4" }
    };

    Response response;
    response.set_headers( headers );

    EXPECT_EQ( headers, response.get_headers( ) );
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

TEST( Response, negated_equality_operator )
{
    Response lhs;
    lhs.set_body( "some data" );
    
    Response rhs;
    rhs.set_body( "data some" );
    
    EXPECT_TRUE( lhs != rhs );
}

TEST( Response, assignment_operator )
{
    const map< string, string > headers = {
        {"12", "25"},
        {"33", "44"}
    };

    Response original;
    original.set_headers( headers );

    Response copy = original;

    EXPECT_TRUE( original == copy );
}
