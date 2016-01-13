/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <set>
#include <map>
#include <string>
#include <iostream>

//Project Includes
#include <corvusoft/restbed/session.hpp>
#include <corvusoft/restbed/request.hpp>
#include <corvusoft/restbed/resource.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::set;
using std::string;
using std::multimap;

//Project Namespaces
using restbed::Session;
using restbed::Request;
using restbed::Resource;

//External Namespaces

TEST_CASE( "validate default instance values", "[session]" )
{
    const Session session( "f47ac10b-58cc-4372-a567-0e02b2c3d479" );
    
    REQUIRE( session.get_request( ) == nullptr );
    REQUIRE( session.get_resource( ) == nullptr );
    REQUIRE( session.has( "test-key" ) == false );
    REQUIRE( session.keys( ) == set< string >( ) );
    REQUIRE( session.get_id( ) == "f47ac10b-58cc-4372-a567-0e02b2c3d479" );
}

TEST_CASE( "validate setters modify default values", "[session]" )
{
    const set< string > filters = { "value-1", "value-2" };
    
    Session session( "f47ac10b-58cc-4372-a567-0e02b2c3d479" );
    session.set( "name", string( "corvusoft" ) );
    session.set( "filters", filters );
    
    const string session_name = session.get( "name" );
    const set< string > session_filters = session.get( "filters" );
    
    REQUIRE( session_filters == filters );
    REQUIRE( session_name == string( "corvusoft" ) );
    REQUIRE( session.has( "name" ) == true );
    REQUIRE( session.has( "filters" ) == true );
    REQUIRE( session.keys( ) == set< string >( { "name", "filters" } ) );
}
