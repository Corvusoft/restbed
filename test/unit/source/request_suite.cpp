/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
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
    
    REQUIRE( request.get_version( ) == 1.1 );
    REQUIRE( request.get_path( ) == "/" );
    REQUIRE( request.get_body( ).empty( ) );
    REQUIRE( request.get_method( ) == "GET" );
    REQUIRE( request.get_protocol( ) == "HTTP" );
    REQUIRE( request.get_headers( ).empty( ) );
    REQUIRE( request.get_path_parameters( ).empty( ) );
    REQUIRE( request.get_query_parameters( ).empty( ) );
    REQUIRE( request.has_query_parameter( "q" ) == false );
    REQUIRE( request.has_path_parameter( "id" ) == false );
    REQUIRE( request.has_header( "Content-Type" ) == false );
    REQUIRE( request.has_query_parameter( "q", true ) == false );
    REQUIRE( request.has_path_parameter( "id", true ) == false );
}

TEST_CASE( "confirm default destructor throws no exceptions", "[request]" )
{
    auto request = new Request;
    
    REQUIRE_NOTHROW( delete request );
}

TEST_CASE( "validate getter default value", "[request]" )
{
    const Request request;
    
    SECTION( "integer" )
    {
        int value;
        request.get_header( "Var", value, 12 );
        REQUIRE( value == 12 );
    }
    
    SECTION( "unsigned integer" )
    {
        unsigned int value;
        request.get_header( "Var", value, 6 );
        REQUIRE( value == 6 );
    }
    
    SECTION( "long" )
    {
        long value;
        request.get_header( "Var", value, 54 );
        REQUIRE( value == 54 );
    }

    SECTION( "long long" )
    {
        long long value;
        request.get_header( "Var", value, 66 );
        REQUIRE( value == 66 );
    }
    
    SECTION( "unsigned long" )
    {
        unsigned long value;
        unsigned long default_value = -33;
        request.get_header( "Var", value, default_value );
        REQUIRE( value == default_value );
    }

    SECTION( "unsigned long long" )
    {
        long long value;
        request.get_header( "Var", value, -6 );
        REQUIRE( value == -6 );
    }
    
    SECTION( "float" )
    {
        float value;
        request.get_header( "Var", value, 3.6 );
        REQUIRE( value == 3.6f );
    }
    
    SECTION( "double" )
    {
        double value;
        request.get_header( "Var", value, 34443 );
        REQUIRE( value == 34443 );
    }
    
    SECTION( "string" )
    {
		string header = request.get_header( "Var", string( "open" ) );
        REQUIRE( header == "open" );
    }
}
