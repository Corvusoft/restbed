/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <map>
#include <string>
#include <vector>
#include <stdexcept>

//Project Includes
#include <corvusoft/restbed/resource>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::map;
using std::string;
using std::vector;
using std::invalid_argument;

//Project Namespaces
using restbed::Resource;

//External Namespaces

SCENARIO( "constructor", "[resource]" )
{
    GIVEN( "i want to instantiate a default resource" )
    {
        Resource resource;

        WHEN( "i construct the object" )
        {
            THEN( "i should see the default properties" )
            {
                string path = "";
                vector< string > paths;
                map< string, string > filters;

                REQUIRE( resource.get_path( ) == path );
                REQUIRE( resource.get_paths( ) == paths );
                REQUIRE( resource.get_header_filters( ) == filters );
            }
        }
    }
}

SCENARIO( "copy constructor", "[resource]" )
{
    GIVEN( "i want to copy an existing resource" )
    {
        string path = "/events";
        map< string, string > filters = { { "Content-Language", "en_GB" } };

        Resource resource;
        resource.set_path( path );
        resource.set_header_filters( filters );

        WHEN( "i instantiate the object with the copy-constructor" )
        {
            Resource copy( resource );

            THEN( "i should see the same properties" )
            {
                REQUIRE( copy.get_path( ) == path );
                REQUIRE( copy.get_header_filters( ) == filters );
            }
        }
    }
}

SCENARIO( "destructor", "[resource]" )
{
    GIVEN( "i instantiate a new object" )
    {
        Resource* resource = new Resource( );

        WHEN( "i deallocate the object" )
        {
            THEN( "i should not see any exceptions" )
            {
                REQUIRE_NOTHROW( delete resource );
            }
        }
    }
}

SCENARIO( "assignment-operator", "[resource]" )
{
    GIVEN( "i want to copy an existing resource" )
    {
        string path = "/events";
        vector< string > paths = { "/events" };
        map< string, string > filters = { { "Content-Language", "en_GB" } };

        Resource resource;
        resource.set_path( path );
        resource.set_header_filters( filters );

        WHEN( "i instantiate the object with the assignment-operator" )
        {
            Resource copy = resource;

            THEN( "i should see the same properties" )
            {
                REQUIRE( resource.get_path( ) == path );
                REQUIRE( resource.get_paths( ) == paths );
                REQUIRE( resource.get_header_filters( ) == filters );
            }
        }
    }
}

SCENARIO( "less-than-operator", "[resource]" )
{
    GIVEN( "i want to compare two objects" )
    {
        Resource lhs;
        lhs.set_path( "/api/1.1" );

        Resource rhs;
        rhs.set_path( "/api/1.2" );

        WHEN( "i perform a comparison with the less-than-operator" )
        {
            THEN( "i should see the lhs is less than the rhs" )
            {
                REQUIRE( lhs < rhs );
            }
        }
    }
}

SCENARIO( "greater-than-operator", "[resource]" )
{
    GIVEN( "i want to compare two objects" )
    {
        Resource lhs;
        lhs.set_path( "/api/1.2" );

        Resource rhs;
        rhs.set_path( "/api/1.1" );

        WHEN( "i perform a comparison with the greater-than-operator" )
        {
            THEN( "i should see the lhs is greater than the rhs" )
            {
                REQUIRE( lhs > rhs );
            }
        }
    }
}

SCENARIO( "equality-operator", "[resource]" )
{
    GIVEN( "i want to compare two objects" )
    {
        Resource lhs;
        lhs.set_path( "/api" );

        Resource rhs;
        rhs.set_path( "/api" );

        WHEN( "i perform a comparison with the equality-operator" )
        {
            THEN( "i should see identical instances" )
            {
                REQUIRE( lhs == rhs );
            }
        }
    }
}

SCENARIO( "inequality-operator", "[resource]" )
{
    GIVEN( "i want to compare two objects" )
    {
        Resource lhs;
        lhs.set_path( "/api/1.1" );

        Resource rhs;
        lhs.set_path( "/api/1.2" );

        WHEN( "i perform a comparison with the inequality-operator" )
        {
            THEN( "i should see differing instances" )
            {
                REQUIRE( lhs not_eq rhs );
            }
        }
    }
}

SCENARIO( "header filter case sensitivity", "[resource]" )
{
    GIVEN( "i want to read header filter field 'Content-Type'" )
    {
        map< string, string > filters = { { "Content-Type", "application/xml" } };

        Resource resource;
        resource.set_header_filters( filters );

        WHEN( "i invoke get_header_filter with 'CoNtEnt-TYPE' example data" )
        {
            THEN( "i should see 'application/xml'" )
            {
                REQUIRE( resource.get_header_filter( "CoNtEnt-TYPE" ) == "application/xml" );
            }
        }
    }
}
