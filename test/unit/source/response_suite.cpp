/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <map>
#include <string>
#include <cstdint>

//Project Includes
#include <corvusoft/restbed/response>

//External Includes
#include <catch.hpp>
#include <corvusoft/framework/bytes>

//System Namespaces
using std::string;
using std::multimap;

//Project Namespaces
using restbed::Response;

//External Namespaces
using framework::Bytes;

SCENARIO( "constructor", "[response]" )
{
    GIVEN( "i want to instantiate a default response" )
    {
        Response response;

        WHEN( "i construct the object" )
        {
            Bytes body;
            double version = 1.1;
            int status = 200;
            string message = "OK";
            multimap< string, string > headers;

            THEN( "i should see default properties" )
            {
                REQUIRE( response.get_body( ) == body );
                REQUIRE( response.get_version( ) == version );
                REQUIRE( response.get_status_code( ) == status );
                REQUIRE( response.get_headers( ) == headers );
            }
        }
    }
}

SCENARIO( "copy constructor", "[response]" )
{
    GIVEN( "i want to copy an existing checksum" )
    {
        Bytes body = { 'a', 'b', 'c' };
        double version = 1.0;
        int status = 201;
        string message = "Corvusoft";
        multimap< string, string > headers = { { "accept", "application/csv" } };

        Response response;
        response.set_body( body );
        response.set_version( version );
        response.set_status_code( status );
        response.set_status_message( message );
        response.set_headers( headers );

        WHEN( "i instantiate the object with the copy-constructor" )
        {
            Response copy( response );

            THEN( "i should see the same properties" )
            {
                REQUIRE( copy.get_body( ) == body );
                REQUIRE( copy.get_version( ) == version );
                REQUIRE( copy.get_status_code( ) == status );
                REQUIRE( copy.get_status_message( ) == message );
                REQUIRE( response.get_headers( ) == headers );
            }
        }
    }
}

SCENARIO( "destructor", "[response]" )
{
    GIVEN( "i instantiate a new object" )
    {
        Response* response= new Response( );

        WHEN( "i deallocate the object" )
        {
            THEN( "i should not see any exceptions" )
            {
                REQUIRE_NOTHROW( delete response );
            }
        }
    }
}

SCENARIO( "assignment-operator", "[response]" )
{
    GIVEN( "i want to copy an existing response" )
    {
        Bytes body = { 'a', 'b', 'c' };
        double version = 1.0;
        int status = 201;
        string message = "Corvusoft";
        multimap< string, string > headers = { { "accept", "application/csv" } };

        Response response;
        response.set_body( body );
        response.set_version( version );
        response.set_status_code( status );
        response.set_status_message( message );
        response.set_headers( headers );

        WHEN( "i instantiate the object with the assignment-operator" )
        {
            Response copy = response;

            THEN( "i should see the same properties" )
            {
                REQUIRE( copy.get_body( ) == body );
                REQUIRE( copy.get_version( ) == version );
                REQUIRE( copy.get_status_code( ) == status );
                REQUIRE( copy.get_status_message( ) == message );
                REQUIRE( copy.get_headers( ) == headers );
            }
        }
    }
}

SCENARIO( "less-than-operator", "[response]" )
{
    GIVEN( "i want to compare two objects" )
    {
        Response lhs;
        lhs.set_status_code( 200 );

        Response rhs;
        rhs.set_status_code( 201 );

        WHEN( "i perform a comparison with the less-than-operator" )
        {
            THEN( "i should see the lhs is less than the rhs" )
            {
                REQUIRE( lhs < rhs );
            }
        }
    }
}

SCENARIO( "greater-than-operator", "[response]" )
{
    GIVEN( "i want to compare two objects" )
    {
        Response lhs;
        lhs.set_status_code( 201 );

        Response rhs;
        rhs.set_status_code( 200 );

        WHEN( "i perform a comparison with the greater-than-operator" )
        {
            THEN( "i should see the lhs is greater than the rhs" )
            {
                REQUIRE( lhs > rhs );
            }
        }
    }
}

SCENARIO( "equality-operator", "[response]" )
{
    GIVEN( "i want to compare two objects" )
    {
        Response lhs;
        Response rhs;

        WHEN( "i perform a comparison with the equality-operator" )
        {
            THEN( "i should see identical instances" )
            {
                REQUIRE( lhs == rhs );
            }
        }
    }
}

SCENARIO( "inequality-operator", "[response]" )
{
    GIVEN( "i want to compare two objects" )
    {
        Response lhs;
        lhs.set_header( "name", "1" );

        Response rhs;
        rhs.set_header( "name", "2" );

        WHEN( "i perform a comparison with the inequality-operator" )
        {
            THEN( "i should see differing instances" )
            {
                REQUIRE( lhs not_eq rhs );
            }
        }
    }
}

SCENARIO( "to_bytes", "[response]" )
{
    GIVEN( "an object with example data" )
    {
        int status = 201;
        Bytes body = { 'T', 'e', 's', 't', ' ', 'D', 'a', 't', 'a' };
        string message = "CUSTOM-CREATED";
        double version = 1.0;
        multimap< string, string > headers = { { "api", "1.1v" }, { "Date", "ignore" } };

        Response response;
        response.set_body( body );
        response.set_version( version );
        response.set_status_code( status );
        response.set_status_message( message );
        response.set_headers( headers );

        WHEN( "i invoke to_bytes" )
        {
            THEN( "i should a byte representation" )
            {
                string data = "HTTP/1.0 201 CUSTOM-CREATED\r\nConnection: close\r\nServer: Corvusoft - restbed\r\nContent-Type: text/plain; charset=us-ascii\r\nContent-Length: 9\r\nDate: ignore\r\napi: 1.1v\r\n\r\nTest Data";

                REQUIRE( response.to_bytes( ) == Bytes( data.begin( ), data.end( ) ) );
            }
        }
    }
}

SCENARIO( "header filter case sensitivity", "[response]" )
{
    GIVEN( "i want to read header filter field 'Content-Type'" )
    {
        multimap< string, string > headers = { { "Content-Type", "application/xml" } };

        Response response;
        response.set_headers( headers );

        WHEN( "i invoke get_header with 'CoNtEnt-TYPE' example data" )
        {
            THEN( "i should see 'application/xml'" )
            {
                REQUIRE( response.get_header( "CoNtEnt-TYPE" ) == "application/xml" );
            }
        }
    }
}
