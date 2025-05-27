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
#include <catch2/catch_all.hpp>

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
    const Session session;
    REQUIRE( session.get_request( ) == nullptr );
    REQUIRE( session.get_resource( ) == nullptr );
}

TEST_CASE( "invoke fetch on uninitialised instance", "[session]" )
{
    auto session = make_shared< Session >( );
    
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
    auto session = make_shared< Session >( );
    
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
