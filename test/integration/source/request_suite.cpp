/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
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
    Request request;
    request.set_body( { 'a', 'b', 'c' } );

    REQUIRE( request.get_body( ) == Bytes( { 'a', 'b', 'c' } ) );
}
