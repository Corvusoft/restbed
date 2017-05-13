/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restbed/request.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::map;
using std::string;
using std::multimap;

//Project Namespaces
using restbed::Request;

//External Namespaces

TEST_CASE( "validate default instance values", "[request]" )
{
    const Request request;
    
    REQUIRE( request.get_port( ) == 80 );
    REQUIRE( request.get_host( ) == "" );
    REQUIRE( request.get_version( ) == 1.1 );
    REQUIRE( request.get_path( ) == "/" );
    REQUIRE( request.get_body( ).empty( ) );
    REQUIRE( request.get_method( ) == "GET" );
    REQUIRE( request.get_protocol( ) == "HTTP" );
    REQUIRE( request.get_headers( ).empty( ) );
    REQUIRE( request.get_response( ) == nullptr );
    REQUIRE( request.get_path_parameters( ).empty( ) );
    REQUIRE( request.get_query_parameters( ).empty( ) );
    REQUIRE( request.has_query_parameter( "q" ) == false );
    REQUIRE( request.has_path_parameter( "id" ) == false );
    REQUIRE( request.has_header( "Content-Type" ) == false );
}

TEST_CASE( "confirm default destructor throws no exceptions", "[request]" )
{
    auto request = new Request;
    
    REQUIRE_NOTHROW( delete request );
}

TEST_CASE( "validate setters modify default values", "[request]" )
{
    Request request;
    request.set_body( "abc" );
    request.set_port( 1984 );
    request.set_version( 1.0 );
    request.set_path( "/test case" );
    request.set_host( "www.google.co.uk" );
    request.set_method( "CONNECT" );
    request.set_protocol( "HTTPS" );
    
    multimap< string, string > headers { { "X-CUST", "1223" } };
    request.set_headers( headers );
    
    multimap< string, string > parameters { { "q", "search" } };
    request.set_query_parameters( parameters );
    
    REQUIRE( request.get_port( ) == 1984 );
    REQUIRE( request.get_host( ) == "www.google.co.uk" );
    REQUIRE( request.get_version( ) == 1.0 );
    REQUIRE( request.get_path( ) == "/test case" );
    REQUIRE( request.get_body( ).empty( ) == false );
    REQUIRE( request.get_method( ) == "CONNECT" );
    REQUIRE( request.get_protocol( ) == "HTTPS" );
    REQUIRE( request.get_headers( ) == headers );
    REQUIRE( request.get_response( ) == nullptr );
    REQUIRE( request.get_path_parameters( ).empty( ) );
    REQUIRE( request.get_query_parameters( ) == parameters );
    REQUIRE( request.has_query_parameter( "q" ) == true );
    REQUIRE( request.has_header( "X-CUST" ) == true );
}

TEST_CASE( "validate getter default value", "[request]" )
{
    const Request request;
    
    SECTION( "integer" )
    {
        int value = request.get_header( "Var", 12 );
        REQUIRE( value == 12 );
    }
    
    SECTION( "unsigned integer" )
    {
        unsigned int value = request.get_header( "Var", 6 );
        REQUIRE( value == 6 );
    }
    
    SECTION( "long" )
    {
        long value = request.get_header( "Var", 54 );
        REQUIRE( value == 54 );
    }
    
    SECTION( "long long" )
    {
        long long value = request.get_header( "Var", 66 );
        REQUIRE( value == 66 );
    }
    
    SECTION( "unsigned long" )
    {
        unsigned long default_value = static_cast< unsigned long >( -33 );
        unsigned long value = request.get_header( "Var", default_value );
        REQUIRE( value == default_value );
    }
    
    SECTION( "unsigned long long" )
    {
        long long value = request.get_header( "Var", -6 );
        REQUIRE( value == -6 );
    }
    
    SECTION( "float" )
    {
        float value = request.get_header( "Var", 3.14 );
        REQUIRE( value == 3.14f );
    }
    
    SECTION( "double" )
    {
        double value = request.get_header( "Var", 34.999443 );
        REQUIRE( value == 34.999443 );
    }
    
    SECTION( "string" )
    {
        string header = request.get_header( "Var", "open" );
        REQUIRE( header == "open" );
    }
}

TEST_CASE( "validate set_header overrides previous value", "[request]" )
{
    Request request;
    request.set_header( "Content-Type", "application/json" );
    REQUIRE( "application/json" == request.get_header( "Content-Type" ) );
    
    request.set_header( "Content-Type", "application/xml" );
    REQUIRE( "application/xml" == request.get_header( "Content-Type" ) );
    
    const auto headers = request.get_headers( );
    REQUIRE( headers.size( ) == 1 );
    
    const auto expectation = multimap< string, string >
    {
        { "Content-Type", "application/xml" }
    };
    REQUIRE( headers == expectation );
}

TEST_CASE( "validate add_header does not override a previous value", "[request]" )
{
    Request request;
    request.add_header( "Content-Type", "application/json" );
    REQUIRE( "application/json" == request.get_header( "Content-Type" ) );
    
    request.add_header( "Content-Type", "application/xml" );
    REQUIRE( "application/json" == request.get_header( "Content-Type" ) );
    
    const auto headers = request.get_headers( );
    REQUIRE( headers.size( ) == 2 );
    
    const auto expectation = multimap< string, string >
    {
        { "Content-Type", "application/json" },
        { "Content-Type", "application/xml" }
    };
    REQUIRE( headers == expectation );
}
