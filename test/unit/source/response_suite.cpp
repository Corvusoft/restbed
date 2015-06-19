/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restbed/response>

//External Includes
#include <catch.hpp>
#include <corvusoft/framework/byte>

//System Namespaces
using std::string;
using std::multimap;

//Project Namespaces
using restbed::Response;

//External Namespaces
using framework::Bytes;

TEST_CASE( "validate default instance values", "[response]" )
{
    const Response response;

    REQUIRE( response.get_body( ).empty( ) );
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

    multimap< string, string > headers {
        { "Connection", "keep-alive" }
    };

    response.set_headers( headers );

    REQUIRE( response.get_version( ) == 1.0 );
    REQUIRE( response.get_status_code( ) == 400 );
    REQUIRE( response.get_protocol( ) == "SPDY" );
    REQUIRE( response.get_headers( ) == headers );
    REQUIRE( response.get_status_message( ) == "corvusoft ltd" );

    const auto body = response.get_body( );
    REQUIRE( body == Bytes( { 'a', 'b' } ) );
}

TEST_CASE( "convert response to bytes", "[response]" )
{
    Response response;

    SECTION( "default response" )
    {
        const auto bytes = response.to_bytes( );
        const string body( bytes.data( ), bytes.data( ) + bytes.size( ) );

        REQUIRE( body == "HTTP/1.1 200 \r\n\r\n" );
    }

    SECTION( "modified response" )
    {
        response.set_body( "ab" );
        response.set_version( 1.0 );
        response.set_status_code( 400 );
        response.set_protocol( "SPDY" );
        response.set_status_message( "corvusoft ltd" );

        multimap< string, string > headers {
            { "Connection", "keep-alive" }
        };

        response.set_headers( headers );

        const auto bytes = response.to_bytes( );
        const string body( bytes.data( ), bytes.data( ) + bytes.size( ) );

        REQUIRE( body == "SPDY/1.0 400 corvusoft ltd\r\nConnection: keep-alive\r\n\r\nab" );
    }
}
