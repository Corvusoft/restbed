/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restbed/response.hpp>

//External Includes
#pragma warning( disable:4702 )
#include <catch.hpp>
#pragma warning( restore:4702 )

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
    REQUIRE( response.get_status_code( ) == 200 );
    REQUIRE( response.get_protocol( ) == "HTTP" );
    REQUIRE( response.get_headers( ).empty( ) );
    REQUIRE( response.get_status_message( ).empty( ) );
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
}
