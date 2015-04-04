/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restbed/request>

//External Includes
#include <catch.hpp>
#include <corvusoft/framework/bytes>

//System Namespaces
using std::map;
using std::string;
using std::multimap;

//Project Namespaces
using restbed::Request;

//External Namespaces
using framework::Bytes;

SCENARIO( "constructor", "[request]" )
{
    GIVEN( "a default object" )
    {
        Request request;

        WHEN( "the properties are retrieved" )
        {
            const Bytes body = request.get_body( );
            const string path = request.get_path( );
            const string origin = request.get_origin( );
            const string destination = request.get_destination( );
            const string protocol = request.get_protocol( );
            const double version = request.get_version( );
            const multimap< string, string > headers = request.get_headers( );
            const map< string, string > path_parameters = request.get_path_parameters( );
            const multimap< string, string > query_parameters = request.get_query_parameters( );

            THEN( "i should see default values" )
            {
                REQUIRE( body.empty( ) );
                REQUIRE( path == "/" );
                REQUIRE( origin.empty( ) );
                REQUIRE( destination.empty( ) );
                REQUIRE( version == 1.1 );
                REQUIRE( headers.empty( ) );
                REQUIRE( protocol == "HTTP" );
                REQUIRE( path_parameters.empty( ) );
                REQUIRE( query_parameters.empty( ) );
            }
        }
    }
}

SCENARIO( "copy constructor", "[request]" )
{
    GIVEN( "i want to copy an existing request" )
    {
        Request request;


        WHEN( "i instantiate the object with the copy-constructor" )
        {
            Request copy( request );

            THEN( "i should see the same properties" )
            {
                REQUIRE( copy.get_body( ).empty( ) );
                REQUIRE( copy.get_path( ) == "/" );
                REQUIRE( copy.get_origin( ).empty( ) );
                REQUIRE( copy.get_destination( ).empty( ) );
                REQUIRE( copy.get_version( ) == 1.1 );
                REQUIRE( copy.get_headers( ).empty( ) );
                REQUIRE( copy.get_protocol( ) == "HTTP" );
                REQUIRE( copy.get_path_parameters( ).empty( ) );
                REQUIRE( copy.get_query_parameters( ).empty( ) );
            }
        }
    }
}

SCENARIO( "destructor", "[request]" )
{
    GIVEN( "i instantiate a new object" )
    {
        Request* request = new Request( );

        WHEN( "i deallocate the object" )
        {
            THEN( "i should not see any exceptions" )
            {
                REQUIRE_NOTHROW( delete request );
            }
        }
    }
}

SCENARIO( "assignment-operator", "[request]" )
{
    GIVEN( "i want to copy an existing request" )
    {
        Request request;

        WHEN( "i instantiate the object with the assignment-operator" )
        {
            Request copy = request;

            THEN( "i should see the same properties" )
            {
                REQUIRE( copy.get_body( ).empty( ) );
                REQUIRE( copy.get_path( ) == "/" );
                REQUIRE( copy.get_origin( ).empty( ) );
                REQUIRE( copy.get_destination( ).empty( ) );
                REQUIRE( copy.get_version( ) == 1.1 );
                REQUIRE( copy.get_headers( ).empty( ) );
                REQUIRE( copy.get_protocol( ) == "HTTP" );
                REQUIRE( copy.get_path_parameters( ).empty( ) );
                REQUIRE( copy.get_query_parameters( ).empty( ) );
            }
        }
    }
}

SCENARIO( "less-than-operator", "[request]" )
{
    GIVEN( "i want to compare two objects" )
    {
        Request lhs;
        Request rhs;

        WHEN( "i perform a comparison with the less-than-operator" )
        {
            THEN( "i should see the lhs is not less than the rhs" )
            {
                REQUIRE( not ( lhs < rhs ) );
            }
        }
    }
}

SCENARIO( "greater-than-operator", "[request]" )
{
    GIVEN( "i want to compare two objects" )
    {
        Request lhs;
        Request rhs;

        WHEN( "i perform a comparison with the greater-than-operator" )
        {
            THEN( "i should see the lhs is not greater than the rhs" )
            {
                REQUIRE( not ( lhs > rhs ) );
            }
        }
    }
}

SCENARIO( "equality-operator", "[request]" )
{
    GIVEN( "i want to compare two objects" )
    {
        Request lhs;
        Request rhs;

        WHEN( "i perform a comparison with the equality-operator" )
        {
            THEN( "i should see identical instances" )
            {
                REQUIRE( lhs == rhs );
            }
        }
    }
}

SCENARIO( "inequality-operator", "[request]" )
{
    GIVEN( "i want to compare two objects" )
    {
        Request lhs;
        Request rhs;

        WHEN( "i perform a comparison with the inequality-operator" )
        {
            THEN( "i should not see differing instances" )
            {
                REQUIRE( not ( lhs not_eq rhs ) );
            }
        }
    }
}

SCENARIO( "has_header", "[request]" )
{
    GIVEN( "i want to test for an available request header" )
    {
        Request request;

        WHEN( "i invoke has_header on a default request with 'Content-Type'" )
        {
            THEN( "i should see false" )
            {
                REQUIRE( request.has_header( "Content-Type" ) == false );
            }
        }
    }
}

SCENARIO( "has_path_parameter", "[request]" )
{
    GIVEN( "i want to test for an available request header" )
    {
        Request request;

        WHEN( "i invoke has_path_parameter on a default request with 'keys'" )
        {
            THEN( "i should see false" )
            {
                REQUIRE( request.has_path_parameter( "keys" ) == false );
            }
        }
    }
}

SCENARIO( "has_query_parameter", "[request]" )
{
    GIVEN( "i want to test for an available request header" )
    {
        Request request;

        WHEN( "i invoke has_query_parameter on a default request with 'version'" )
        {
            THEN( "i should see false" )
            {
                REQUIRE( request.has_query_parameter( "version" ) == false );
            }
        }
    }
}
