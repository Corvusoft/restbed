//System Includes
#include <map>
#include <string>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::multimap;

//Project Namespaces
using namespace restbed;

//External Namespaces

TEST_CASE( "uri fails to handle file scheme relative paths", "[uri]" )
{
    multimap< string, string > expectation;
    
    Uri relative( "file://certs/server.key", true );
    REQUIRE( relative.get_port( ) == 0 );
    REQUIRE( relative.get_path( ) == "certs/server.key" );
    REQUIRE( relative.get_query( ) == "" );
    REQUIRE( relative.get_scheme( ) == "file" );
    REQUIRE( relative.get_fragment( ) == "" );
    REQUIRE( relative.get_username( ) == "" );
    REQUIRE( relative.get_password( ) == "" );
    REQUIRE( relative.get_authority( ) == "" );
    REQUIRE( relative.is_relative( ) == true );
    REQUIRE( relative.is_absolute( ) == false );
    REQUIRE( relative.to_string( ) == "file://certs/server.key" );
    REQUIRE( relative.get_query_parameters( ) == expectation );
    
    Uri absolute( "file:///certs/server.key" );
    REQUIRE( absolute.get_port( ) == 0 );
    REQUIRE( absolute.get_path( ) == "/certs/server.key" );
    REQUIRE( absolute.get_query( ) == "" );
    REQUIRE( absolute.get_scheme( ) == "file" );
    REQUIRE( absolute.get_fragment( ) == "" );
    REQUIRE( absolute.get_username( ) == "" );
    REQUIRE( absolute.get_password( ) == "" );
    REQUIRE( absolute.get_authority( ) == "" );
    REQUIRE( absolute.is_relative( ) == false );
    REQUIRE( absolute.is_absolute( ) == true );
    REQUIRE( absolute.to_string( ) == "file:///certs/server.key" );
    REQUIRE( absolute.get_query_parameters( ) == expectation );
}
