/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include <corvusoft/restbed/session>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using restbed::Session;

//External Namespaces

TEST_CASE( "validate default instance values", "[session]" )
{
    const Session session( "f47ac10b-58cc-4372-a567-0e02b2c3d479" );

    REQUIRE( session.is_open( ) == false );
    REQUIRE( session.is_closed( ) == true );
    REQUIRE( session.get_origin( ) == "" );
    REQUIRE( session.get_destination( ) == "" );
    REQUIRE( session.get_id( ) == "f47ac10b-58cc-4372-a567-0e02b2c3d479" );
}

TEST_CASE( "confirm default destructor throws no exceptions", "[session]" )
{
    auto session = new Session( "f47ac10b-58cc-4372-a567-0e02b2c3d479" );

    REQUIRE_NOTHROW( delete session );
}
