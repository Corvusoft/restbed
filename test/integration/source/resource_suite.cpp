/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <map>
#include <string>
#include <stdexcept>
#include <functional>

//Project Includes
#include <corvusoft/restbed/method>
#include <corvusoft/restbed/request>
#include <corvusoft/restbed/response>
#include <corvusoft/restbed/resource>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::map;
using std::string;
using std::function;

//Project Namespaces

//External Namespaces
using restbed::Method;
using restbed::Request;
using restbed::Response;
using restbed::Resource;

const static int method_handler_accessor_expectation = 3349;

Response test_method_handler( const Request& )
{
    Response response;
    response.set_status_code( method_handler_accessor_expectation );
    
    return response;
}

SCENARIO( "method handler", "[resource]" )
{
    GIVEN( "i setup a 'GET' method handler" )
    {
        Resource resource;
        resource.set_method_handler( "GET", &test_method_handler );

        WHEN( "i invoke the 'GET' method handler" )
        {
            auto handler = resource.get_method_handler( "GET" );

            Request request;
            Response response = handler( request );

            THEN( "i should see '3349' status code" )
            {
                REQUIRE( response.get_status_code( ) == method_handler_accessor_expectation );
            }
        }
    }
}

SCENARIO( "method handlers", "[resource]" )
{
    GIVEN( "i setup a method handlers" )
    {
        map< Method, function< Response ( const Request& ) > > handlers;
        handlers[ "GET" ] = &test_method_handler;
        handlers[ "PUT" ] = &test_method_handler;
        handlers[ "DELETE" ] = &test_method_handler;

        Resource resource;
        resource.set_method_handlers( handlers );

        WHEN( "i invoke get_method_handlers" )
        {
            THEN( "i should see 3 entries 'GET, PUT, DELETE'" )
            {
                REQUIRE( handlers.find( "GET" ) not_eq handlers.end( ) );
                REQUIRE( handlers.find( "PUT" ) not_eq handlers.end( ) );
                REQUIRE( handlers.find( "DELETE" ) not_eq handlers.end( ) );
            }
        }
    }
}
