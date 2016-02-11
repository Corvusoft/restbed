/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restbed/response.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::multimap;

//Project Namespaces
using restbed::Response;

//External Namespaces

TEST_CASE( "validate default instance values", "[response]" )
{
    const Response response;
    
    REQUIRE( response.get_version( ) == 1.1 );
    REQUIRE( response.get_status_code( ) == 0 );
    REQUIRE( response.get_protocol( ) == "HTTP" );
    REQUIRE( response.get_headers( ).empty( ) );
    REQUIRE( response.get_status_message( ).empty( ) );
    REQUIRE( response.get_request( ) == nullptr );
}

TEST_CASE( "confirm default destructor throws no exceptions", "[response]" )
{
    auto response = new Response;
    
    REQUIRE_NOTHROW( delete response );
}

TEST_CASE( "validate setters modify default values", "[response]" )
{
    Response response;
    response.set_body( "ab" );
    response.set_version( 1.0 );
    response.set_status_code( 400 );
    response.set_protocol( "SPDY" );
    response.set_status_message( "corvusoft ltd" );
    
    multimap< string, string > headers
    {
        { "Connection", "keep-alive" }
    };
    
    response.set_headers( headers );
    
    REQUIRE( response.get_version( ) == 1.0 );
    REQUIRE( response.get_status_code( ) == 400 );
    REQUIRE( response.get_protocol( ) == "SPDY" );
    REQUIRE( response.get_headers( ) == headers );
    REQUIRE( response.get_status_message( ) == "corvusoft ltd" );
    REQUIRE( response.get_request( ) == nullptr );
}

TEST_CASE( "validate getter default value", "[response]" )
{
    const Response response;
    
    SECTION( "integer" )
    {
        int value;
        response.get_header( "Var", value, 12 );
        REQUIRE( value == 12 );
    }
    
    SECTION( "unsigned integer" )
    {
        unsigned int value;
        response.get_header( "Var", value, 6 );
        REQUIRE( value == 6 );
    }
    
    SECTION( "long" )
    {
        long value;
        response.get_header( "Var", value, 54 );
        REQUIRE( value == 54 );
    }
    
    SECTION( "long long" )
    {
        long long value;
        response.get_header( "Var", value, 66 );
        REQUIRE( value == 66 );
    }
    
    SECTION( "unsigned long" )
    {
        unsigned long value;
        unsigned long default_value = static_cast< unsigned long >( -33 );
        response.get_header( "Var", value, default_value );
        REQUIRE( value == default_value );
    }
    
    SECTION( "unsigned long long" )
    {
        long long value;
        response.get_header( "Var", value, -6 );
        REQUIRE( value == -6 );
    }
    
    SECTION( "float" )
    {
        float value;
        response.get_header( "Var", value, float( 3.6 ) );
        REQUIRE( value == 3.6f );
    }
    
    SECTION( "double" )
    {
        double value;
        response.get_header( "Var", value, 34443 );
        REQUIRE( value == 34443 );
    }
    
    SECTION( "string" )
    {
        string header = response.get_header( "Var", string( "open" ) );
        REQUIRE( header == "open" );
    }
}
