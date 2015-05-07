/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include <corvusoft/restbed/request>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using restbed::Request;

//External Namespaces

SCENARIO( "constructor", "[request]" )
{
    GIVEN( "i want to instantiate a default request" )
    {
        WHEN( "i construct the object" )
        {
            Request request;

            THEN( "i should see default properties" )
            {
                REQUIRE( request.get_method( ) == "GET" );
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
                REQUIRE( request.get_method( ) == "GET" );
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
                REQUIRE( request.get_method( ) == "GET" );
            }
        }
    }
}
