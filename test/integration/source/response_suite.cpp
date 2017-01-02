/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/response.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using restbed::Bytes;
using restbed::Response;

//External Namespaces

TEST_CASE( "validate default instance values", "[response]" )
{
    const Response response;
    REQUIRE( response.get_body( ).empty( ) );
}

TEST_CASE( "validate setters modify default values", "[response]" )
{
    Bytes expectation = { 'a', 'b' };
    
    Response response;
    response.set_body( expectation );
    
    const auto body = response.get_body( );
    REQUIRE( body == expectation );
}
