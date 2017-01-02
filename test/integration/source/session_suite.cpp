/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <set>
#include <map>
#include <memory>
#include <string>
#include <iostream>

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/session.hpp>
#include <corvusoft/restbed/request.hpp>
#include <corvusoft/restbed/resource.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::set;
using std::string;
using std::multimap;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using restbed::Bytes;
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

TEST_CASE( "invoke fetch on uninitialised instance", "[session]" )
{
    auto session = make_shared< Session >( "" );
    
    REQUIRE( session->is_closed( ) == true );
    
    REQUIRE_NOTHROW( session->fetch( 100, [ ]( const shared_ptr< Session >, const Bytes& )
    {
        return;
    } ) );
    REQUIRE_NOTHROW( session->fetch( "\r\n", [ ]( const shared_ptr< Session >, const Bytes& )
    {
        return;
    } ) );
}

TEST_CASE( "invoke yield on uninitialised instance", "[session]" )
{
    auto session = make_shared< Session >( "" );
    
    REQUIRE( session->is_closed( ) == true );
    
    REQUIRE_NOTHROW( session->yield( Bytes( { 'a' } ), [ ]( const shared_ptr< Session > )
    {
        return;
    } ) );
    REQUIRE_NOTHROW( session->yield( 200, Bytes( { 'a' } ), [ ]( const shared_ptr< Session > )
    {
        return;
    } ) );
    REQUIRE_NOTHROW( session->yield( 200, Bytes( { 'a' } ), { { "Content-Type", "text" } }, [ ]( const shared_ptr< Session > )
    {
        return;
    } ) );
}
