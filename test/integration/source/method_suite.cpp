/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <string>

//Project Includes
#include <corvusoft/restbed/method>
#include <corvusoft/restbed/status_code>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;

//Project Namespaces
using restbed::Method;
using restbed::StatusCode;

//External Namespaces

SCENARIO( "invalid constructor", "[method]" )
{
    GIVEN( "i want to instantiate a method from a string value" )
    {
        WHEN( "i construct the object with '---_)(*&'" )
        {
            THEN( "i should see an exception" )
            {
                REQUIRE_THROWS_AS( Method( "---_)(*&" ), StatusCode::Value );
            }
        }
    }
}

SCENARIO( "empty constructor", "[method]" )
{
    GIVEN( "i want to instantiate a method from a string value" )
    {
        WHEN( "i construct the object with ''" )
        {
            THEN( "i should see an exception" )
            {
                REQUIRE_THROWS_AS( Method( "" ), StatusCode::Value );
            }
        }
    }
}

SCENARIO( "nullptr constructor", "[method]" )
{
    GIVEN( "i want to instantiate a method from a string value" )
    {
        WHEN( "i construct the object with a 'nullptr'" )
        {
            THEN( "i should see an exception" )
            {
                REQUIRE_THROWS_AS( Method( nullptr ), StatusCode::Value );
            }
        }
    }
}

SCENARIO( "invalid parse", "[method]" )
{
    GIVEN( "i want to instantiate a checksum from a string value" )
    {
        WHEN( "i invoke parse with '---_)(*&'" )
        {
            THEN( "i should see an exception" )
            {
                REQUIRE_THROWS_AS( Method::parse( "---_)(*&" ), StatusCode::Value );
            }
        }
    }
}

SCENARIO( "empty parse", "[method]" )
{
    GIVEN( "i want to instantiate a checksum from a string value" )
    {
        WHEN( "i invoke parse with ''" )
        {
            THEN( "i should see an exception" )
            {
                REQUIRE_THROWS_AS( Method::parse( "" ), StatusCode::Value );
            }
        }
    }
}
