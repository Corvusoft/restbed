/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restbed/uri.hpp>
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/request.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::multimap;

//Project Namespaces
using restbed::Uri;
using restbed::Bytes;
using restbed::Request;

//External Namespaces

TEST_CASE( "validate setters modify default values", "[request]" )
{
    Bytes expectation = { 'a', 'b', 'c' };
    
    Request request;
    request.set_body( expectation );
    
    REQUIRE( request.get_body( ) == expectation );
    REQUIRE( request.has_query_parameter( "q" ) == false );
    REQUIRE( request.has_path_parameter( "id" ) == false );
}

TEST_CASE( "validate URI constructor", "[request]" )
{
    Request request( Uri( "https://localhost:1985/messages?a=1&b=2&c=9#1234" ) );
    
    REQUIRE( request.get_port( ) == 1985 );
    REQUIRE( request.get_protocol( ) == "HTTPS" );
    REQUIRE( request.get_path( ) == "/messages" );
    REQUIRE( request.get_host( ) == "localhost" );
    
    multimap< string, string > parameters
    {
        { "a", "1" },
        { "b", "2" },
        { "c", "9" }
    };
    
    REQUIRE( request.get_query_parameters( ) == parameters );
}

TEST_CASE( "validate HTTPS URI constructor", "[request]" )
{
    Request request( Uri( "https://localhost/?abc=456&efg=123" ) );
    
    REQUIRE( request.get_port( ) == 443 );
    REQUIRE( request.get_protocol( ) == "HTTPS" );
    REQUIRE( request.get_path( ) == "/" );
    REQUIRE( request.get_host( ) == "localhost" );
    
    multimap< string, string > parameters
    {
        { "abc", "456" },
        { "efg", "123" }
    };
    
    REQUIRE( request.get_query_parameters( ) == parameters );
}

TEST_CASE( "validate HTTP URI constructor", "[request]" )
{
    Request request( Uri( "http://localhost/?abc=456&efg=123" ) );
    
    REQUIRE( request.get_port( ) == 80 );
    REQUIRE( request.get_protocol( ) == "HTTP" );
    REQUIRE( request.get_path( ) == "/" );
    REQUIRE( request.get_host( ) == "localhost" );
    
    multimap< string, string > parameters
    {
        { "abc", "456" },
        { "efg", "123" }
    };
    
    REQUIRE( request.get_query_parameters( ) == parameters );
}

TEST_CASE( "validate URI constructor with no path", "[request]" )
{
    Request request( Uri( "http://localhost?abc=456&efg=123" ) );
    
    REQUIRE( request.get_port( ) == 80 );
    REQUIRE( request.get_protocol( ) == "HTTP" );
    REQUIRE( request.get_path( ) == "/" );
    REQUIRE( request.get_host( ) == "localhost" );
    
    multimap< string, string > parameters
    {
        { "abc", "456" },
        { "efg", "123" }
    };
    
    REQUIRE( request.get_query_parameters( ) == parameters );
}
