//System Includes
#include <set>
#include <map>
#include <memory>
#include <string>
#include <stdexcept>

//Project Includes
#include <corvusoft/restbed/session.hpp>

//External Includes
#include <catch2/catch_all.hpp>

//System Namespaces
using std::set;
using std::string;
using std::bad_cast;
using std::multimap;
using std::shared_ptr;
using std::make_shared;
using std::out_of_range;
using std::invalid_argument;

//Project Namespaces
using restbed::Session;

//External Namespaces

TEST_CASE( "validate default instance values", "[session]" )
{
    const Session session;
    
    REQUIRE( session.is_open( ) == false );
    REQUIRE( session.is_closed( ) == true );
    REQUIRE( session.get_origin( ) == "" );
    REQUIRE( session.get_destination( ) == "" );
    REQUIRE( session.get_headers( ).empty( ) );
}

TEST_CASE( "confirm empty session id throws no exceptions", "[session]" )
{
    REQUIRE_NOTHROW( Session( ) );
}

TEST_CASE( "confirm default destructor throws no exceptions", "[session]" )
{
    auto session = new Session( );
    
    REQUIRE_NOTHROW( delete session );
}

TEST_CASE( "validate setters modify default values", "[session]" )
{
    Session session;
    
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

TEST_CASE( "invoke close on uninitialised instance", "[session]" )
{
    auto session = make_shared< Session >( );
    
    REQUIRE( session->is_closed( ) == true );
    REQUIRE_NOTHROW( session->close( ) );
    REQUIRE( session->is_closed( ) == true );
}

TEST_CASE( "invoke yield on uninitialised instance", "[session]" )
{
    auto session = make_shared< Session >( );
    
    REQUIRE( session->is_closed( ) == true );
    
    REQUIRE_NOTHROW( session->yield( "test data", [ ]( const shared_ptr< Session > )
    {
        return;
    } ) );
    REQUIRE_NOTHROW( session->yield( 200, "test data", [ ]( const shared_ptr< Session > )
    {
        return;
    } ) );
    REQUIRE_NOTHROW( session->yield( 200, "test data", { { "Content-Type", "text" } }, [ ]( const shared_ptr< Session > )
    {
        return;
    } ) );
    REQUIRE_NOTHROW( session->yield( 200, { { "Content-Type", "text" } }, [ ]( const shared_ptr< Session > )
    {
        return;
    } ) );
}

TEST_CASE( "validate set_header overrides previous value", "[request]" )
{
    Session session;
    session.set_header( "Content-Type", "application/json" );
    
    session.set_header( "Content-Type", "application/xml" );
    
    const auto headers = session.get_headers( );
    REQUIRE( headers.size( ) == 1 );
    
    const auto expectation = multimap< string, string >
    {
        { "Content-Type", "application/xml" }
    };
    REQUIRE( headers == expectation );
}

TEST_CASE( "validate add_header does not override a previous value", "[request]" )
{
    Session session;
    session.add_header( "Content-Type", "application/json" );
    session.add_header( "Content-Type", "application/xml" );
    
    const auto headers = session.get_headers( );
    REQUIRE( headers.size( ) == 2 );
    
    const auto expectation = multimap< string, string >
    {
        { "Content-Type", "application/json" },
        { "Content-Type", "application/xml" }
    };
    REQUIRE( headers == expectation );
}
