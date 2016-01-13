/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/request.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::multimap;

//Project Namespaces
using restbed::Bytes;
using restbed::Request;

//External Namespaces

TEST_CASE( "validate setters modify default values", "[request]" )
{
	Bytes expectation = { 'a', 'b', 'c' };

    Request request;
    request.set_body( expectation );

    REQUIRE( request.get_body( ) == expectation );
}

TEST_CASE( "convert request to bytes", "[request]" )
{
    Request request;
    
    SECTION( "default request" )
    {
        const auto bytes = request.to_bytes( );
        const string data( bytes.data( ), bytes.data( ) + bytes.size( ) );
        
        REQUIRE( data == "GET / HTTP/1.1\r\n\r\n" );
    }

    SECTION( "modified request" )
    {
        request.set_version( 1.0 );
        request.set_method( "POST" );
        request.set_protocol( "SPDY" );
        request.set_path( "/index.html" );
        request.set_body( Bytes( { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!' } ) );

        multimap< string, string > parameters
        {
            { "query", "search term" },
            { "page", "1" }
        };
        
        request.set_query_parameters( parameters );
        
        multimap< string, string > headers
        {
            { "Connection", "keep-alive" }
        };
        
        request.set_headers( headers );
        
        const auto bytes = request.to_bytes( );
        const string data( bytes.data( ), bytes.data( ) + bytes.size( ) );

        REQUIRE( data == "POST /index.html?page=1&query=search%20term SPDY/1.0\r\nConnection: keep-alive\r\n\r\nHello, World!" );
    }
}
