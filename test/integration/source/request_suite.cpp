/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/request.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using restbed::Bytes;
using restbed::Request;

//External Namespaces

TEST_CASE( "validate setters modify default values", "[request]" )
{
    Bytes expectation = { 'a', 'b', 'c' };
    
    Request request;
    request.set_body( expectation );
    
    REQUIRE( request.get_body( ) == expectation );
}
