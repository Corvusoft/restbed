/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <map>
#include <string>
#include <stdexcept>

//Project Includes
#include <corvusoft/restbed/session.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::multimap;
using std::invalid_argument;

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
    REQUIRE( session.get_headers( ).empty( ) );
    REQUIRE( session.get_id( ) == "f47ac10b-58cc-4372-a567-0e02b2c3d479" );
}

TEST_CASE( "confirm empty session id results in a invalid argument exception", "[session]" )
{
    REQUIRE_THROWS_AS( Session( "" ), invalid_argument );
}

TEST_CASE( "confirm default destructor throws no exceptions", "[session]" )
{
    auto session = new Session( "f47ac10b-58cc-4372-a567-0e02b2c3d479" );
    
    REQUIRE_NOTHROW( delete session );
}

TEST_CASE( "validate setters modify default values", "[response]" )
{
    Session session( "f47ac10b-58cc-4372-a567-0e02b2c3d479" );
    
    session.set_header( "Connection", "close" );
    multimap< string, string > expectation = { { "Connection", "close" } };
    REQUIRE( session.get_headers( ) == expectation );
    
    expectation =
    {
        { "Content-Type", "application/yaml" },
        { "Content-Encoding", "" }
    };
    
    session.set_headers( expectation );
    REQUIRE( session.get_headers( ) == expectation );
}
