/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <string>

//Project Includes
#include <corvusoft/restbed/method>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;

//Project Namespaces
using restbed::Method;

//External Namespaces

SCENARIO( "string constructor", "[method]" )
{
    GIVEN( "i want to instantiate a method from a string value" )
    {
        Method method( "GET" );

        WHEN( "i construct the object with 'GET'" )
        {
            const string value = method.to_string( );

            THEN( "i should see 'GET'" )
            {
                REQUIRE( value == "GET" );
            }
        }
    }
}

SCENARIO( "character pointer constructor", "[method]" )
{
    GIVEN( "i want to instantiate a method from a string value" )
    {
        const char* verb = "GET";
        Method method( verb );

        WHEN( "i construct the object with 'GET'" )
        {
            const string value = method.to_string( );

            THEN( "i should see 'GET'" )
            {
                REQUIRE( value == "GET" );
            }
        }
    }
}

SCENARIO( "lowercase constructor", "[method]" )
{
    GIVEN( "i want to instantiate a method from a string value" )
    {
        Method method( "put" );

        WHEN( "i construct the object with 'put'" )
        {
            const string value = method.to_string( );

            THEN( "i should see 'PUT'" )
            {
                REQUIRE( value == "PUT" );
            }
        }
    }
}

SCENARIO( "uppercase constructor", "[method]" )
{
    GIVEN( "i want to instantiate a method from a string value" )
    {
        Method method( "OPTIONS" );

        WHEN( "i construct the object with 'OPTIONS'" )
        {
            const string value = method.to_string( );

            THEN( "i should see 'OPTIONS'" )
            {
                REQUIRE( value == "OPTIONS" );
            }
        }
    }
}

SCENARIO( "mixedcase constructor", "[method]" )
{
    GIVEN( "i want to instantiate a method from a string value" )
    {
        Method method( "DeLeTE" );

        WHEN( "i construct the object with 'DeLeTE'" )
        {
            const string value = method.to_string( );

            THEN( "i should see 'DELETE'" )
            {
                REQUIRE( value == "DELETE" );
            }
        }
    }
}

SCENARIO( "copy constructor", "[method]" )
{
    GIVEN( "i want to copy an existing method" )
    {
        Method method( "CONNECT" );

        WHEN( "i instantiate the object with the copy-constructor" )
        {
            Method copy( method );

            THEN( "i should see the same properties" )
            {
                REQUIRE( copy.to_string( ) == method.to_string( ) );
            }
        }
    }
}

SCENARIO( "destructor", "[method]" )
{
    GIVEN( "i instantiate a new object" )
    {
        Method* method = new Method( "TRACE" );

        WHEN( "i deallocate the object" )
        {
            THEN( "i should not see any exceptions" )
            {
                REQUIRE_NOTHROW( delete method );
            }
        }
    }
}

SCENARIO( "assignment-operator", "[method]" )
{
    GIVEN( "i want to copy an existing method" )
    {
        Method method( "POST" );

        WHEN( "i instantiate the object with the assignment-operator" )
        {
            Method copy = method;

            THEN( "i should see the same properties" )
            {
                REQUIRE( copy.to_string( ) == method.to_string( ) );
            }
        }
    }
}

SCENARIO( "less-than-operator", "[method]" )
{
    GIVEN( "i want to compare two objects" )
    {
        Method lhs( "GET" );
        Method rhs( "POST" );

        WHEN( "i perform a comparison with the less-than-operator" )
        {
            THEN( "i should see the lhs is less than the rhs" )
            {
                REQUIRE( lhs < rhs );
            }
        }
    }
}

SCENARIO( "greater-than-operator", "[method]" )
{
    GIVEN( "i want to compare two objects" )
    {
        Method lhs( "POST" );
        Method rhs( "GET" );

        WHEN( "i perform a comparison with the greater-than-operator" )
        {
            THEN( "i should see the lhs is greater than the rhs" )
            {
                REQUIRE( lhs > rhs );
            }
        }
    }
}

SCENARIO( "equality-operator", "[method]" )
{
    GIVEN( "i want to compare two objects" )
    {
        Method lhs( "CONNECT" );
        Method rhs( "CONNECT" );

        WHEN( "i perform a comparison with the equality-operator" )
        {
            THEN( "i should see identical instances" )
            {
                REQUIRE( lhs == rhs );
            }
        }
    }
}

SCENARIO( "inequality-operator", "[method]" )
{
    GIVEN( "i want to compare two objects" )
    {
        Method lhs( "CONNECT" );
        Method rhs( "PUT" );

        WHEN( "i perform a comparison with the inequality-operator" )
        {
            THEN( "i should see differing instances" )
            {
                REQUIRE( lhs not_eq rhs );
            }
        }
    }
}

SCENARIO( "to_string", "[method]" )
{
    GIVEN( "an object with example data" )
    {
        Method method( "OPTIONS" );

        WHEN( "i invoke to_string" )
        {
            THEN( "i should a string representation" )
            {
                REQUIRE( method.to_string( ) == "OPTIONS" );
            }
        }
    }
}

SCENARIO( "uppercase parse", "[method]" )
{
    GIVEN( "i want to instantiate a method from a string value" )
    {
        Method method = Method::parse( "PUT" );

        WHEN( "i invoke parse with 'PUT'" )
        {
            const string value = method.to_string( );

            THEN( "i should see 'PUT'" )
            {
                REQUIRE( value == "PUT" );
            }
        }
    }
}

SCENARIO( "lowercase parse", "[method]" )
{
    GIVEN( "i want to instantiate a method from a string value" )
    {
        Method method = Method::parse( "put" );

        WHEN( "i invoke parse with 'put'" )
        {
            const string value = method.to_string( );

            THEN( "i should see 'PUT'" )
            {
                REQUIRE( value == "PUT" );
            }
        }
    }
}

SCENARIO( "mixedcase parse", "[method]" )
{
    GIVEN( "i want to instantiate a method from a string value" )
    {
        Method method = Method::parse( "pUt" );

        WHEN( "i invoke parse with 'put'" )
        {
            const string value = method.to_string( );

            THEN( "i should see 'PUT'" )
            {
                REQUIRE( value == "PUT" );
            }
        }
    }
}
