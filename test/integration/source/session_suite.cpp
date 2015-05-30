/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include <corvusoft/restbed/session>
#include <corvusoft/restbed/request>
#include <corvusoft/restbed/resource>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using restbed::Session;

//External Namespaces

TEST_CASE( "validate default instance values", "[session]" )
{
    const Session session( "f47ac10b-58cc-4372-a567-0e02b2c3d479" );

    REQUIRE( session.get_request( ) == nullptr );
    REQUIRE( session.get_resource( ) == nullptr );
}
