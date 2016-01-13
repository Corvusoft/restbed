/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/response.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::multimap;

//Project Namespaces
using restbed::Bytes;
using restbed::Response;

//External Namespaces

TEST_CASE( "validate default instance values", "[response]" )
{
    const Response response;
    REQUIRE( response.get_body( ).empty( ) );
}

TEST_CASE( "validate setters modify default values", "[response]" )
{
    Bytes expectation = { 'a', 'b' };

    Response response;
    response.set_body( expectation );
    
    const auto body = response.get_body( );
    REQUIRE( body == expectation );
}

TEST_CASE( "convert response to bytes", "[response]" )
{
    Response response;
    
    SECTION( "default response" )
    {
        const auto bytes = response.to_bytes( );
        const string data( bytes.data( ), bytes.data( ) + bytes.size( ) );
        
        REQUIRE( data == "HTTP/1.1 200 \r\n\r\n" );
    }
    
    SECTION( "modified response" )
    {
        response.set_body( Bytes( { 'a', 'b' } ) );
        response.set_version( 1.0 );
        response.set_status_code( 400 );
        response.set_protocol( "SPDY" );
        response.set_status_message( "corvusoft ltd" );
        
        multimap< string, string > headers
        {
            { "Connection", "keep-alive" }
        };
        
        response.set_headers( headers );
        
        const auto bytes = response.to_bytes( );
        const string data( bytes.data( ), bytes.data( ) + bytes.size( ) );
        
        REQUIRE( data == "SPDY/1.0 400 corvusoft ltd\r\nConnection: keep-alive\r\n\r\nab" );
    }
}
