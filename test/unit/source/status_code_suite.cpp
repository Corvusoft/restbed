/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <map>
#include <string>
#include <stdexcept>

//Project Includes
#include <corvusoft/restbed/status_code>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::map;
using std::string;
using std::invalid_argument;

//Project Namespaces
using restbed::StatusCode;

//External Namespaces

SCENARIO( "to string with valid status code", "[status code]" )
{
    GIVEN( "i want to translate a status code to a status message" )
    {
        WHEN( "i invoke to_string with '200'" )
        {
            THEN( "i should the string 'OK'" )
            {
                REQUIRE( StatusCode::to_string( StatusCode::OK ) == "OK" );
            }
        }
    }
}

SCENARIO( "to string with invalid status code", "[status code]" )
{
    GIVEN( "i want to translate an invalid status code to a status message" )
    {
        WHEN( "i invoke to_string with '9999'" )
        {
            THEN( "i should an exception" )
            {
                REQUIRE_THROWS_AS( StatusCode::to_string( 9999 ), invalid_argument );
            }
        }
    }
}

SCENARIO( "parse with valid status message", "[status code]" )
{
    GIVEN( "i want to translate a status message to a status code" )
    {
        WHEN( "i invoke parse with 'Unprocessable Entity'" )
        {
            THEN( "i should the code '422'" )
            {
                REQUIRE( StatusCode::parse( "Unprocessable Entity" ) == 422 );
            }
        }
    }
}

SCENARIO( "parse with invalid status message", "[status code]" )
{
    GIVEN( "i want to translate an invalid status message to a status code" )
    {
        WHEN( "i invoke parse with 'Missing Error Message'" )
        {
            THEN( "i should the code '422'" )
            {
                REQUIRE_THROWS_AS( StatusCode::parse( "Missing Error Message" ), invalid_argument );
            }
        }
    }
}

SCENARIO( "custom status codes/messages", "[status code]" )
{
    GIVEN( "i want custom status mappings" )
    {
        map< int, string > values =
        {
            { 109, "Custom Error Message" },
            { 222, "Inhouse Error Message" }
        };

        StatusCode::set_mappings( values );

        WHEN( "i invoke set_mappings" )
        {
            THEN( "i should the those mappings" )
            {
                REQUIRE( StatusCode::get_mappings( ) == values );
                REQUIRE( StatusCode::to_string( 109 ) == "Custom Error Message" );
                REQUIRE( StatusCode::parse( "Inhouse Error Message" ) == 222 );
            }
        }
    }
}
