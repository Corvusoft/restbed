//System Includes
#include <string>
#include <vector>

//Project Includes
#include "corvusoft/restbed/byte.hpp"
#include "corvusoft/restbed/string.hpp"

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::vector;

//Project Namespaces
using restbed::Bytes;
using restbed::String;

//External Namespaces

TEST_CASE( "case insensitive remove", "[string]" )
{
    REQUIRE( String::remove( "Solutions", "Corvusoft SOLUTIONS", String::CASE_INSENSITIVE ) == "Corvusoft " );
}

TEST_CASE( "case insensitive remove with missing target", "[string]" )
{
    REQUIRE( String::remove( "ltd", "Corvusoft SOLUTIONS", String::CASE_INSENSITIVE ) == "Corvusoft SOLUTIONS" );
}

TEST_CASE( "case insensitive remove with empty target", "[string]" )
{
    REQUIRE( String::remove( "", "Corvusoft SOLUTIONS", String::CASE_INSENSITIVE ) == "Corvusoft SOLUTIONS" );
}

TEST_CASE( "case insensitive remove with empty value", "[string]" )
{
    REQUIRE( String::remove( "Solutions", "", String::CASE_INSENSITIVE ) == "" );
}

TEST_CASE( "case insensitive remove with empty arguments", "[string]" )
{
    REQUIRE( String::remove( "", "", String::CASE_INSENSITIVE ) == "" );
}

TEST_CASE( "case insensitive replace", "[string]" )
{
    REQUIRE( String::replace( "ltd", "Solutions", "Corvusoft Ltd", String::CASE_INSENSITIVE ) == "Corvusoft Solutions" );
}

TEST_CASE( "case insensitive replace with missing target", "[string]" )
{
    REQUIRE( String::replace( "", "Solutions", "Corvusoft Ltd", String::CASE_INSENSITIVE ) == "Corvusoft Ltd" );
}

TEST_CASE( "case insensitive replace with empty target", "[string]" )
{
    REQUIRE( String::replace( "", "Solutions", "Corvusoft Ltd", String::CASE_INSENSITIVE ) == "Corvusoft Ltd" );
}

TEST_CASE( "case insensitive replace with empty substitute", "[string]" )
{
    REQUIRE( String::replace( "Ltd", "", "Corvusoft Ltd", String::CASE_INSENSITIVE ) == "Corvusoft " );
}

TEST_CASE( "case insensitive replace with empty value", "[string]" )
{
    REQUIRE( String::replace( "Ltd", "Solutions", "", String::CASE_INSENSITIVE ) == "" );
}

TEST_CASE( "case insensitive replace with empty target and substitute", "[string]" )
{
    REQUIRE( String::replace( "", "", "Corvusoft SOLUTIONS", String::CASE_INSENSITIVE ) == "Corvusoft SOLUTIONS" );
}

TEST_CASE( "case insensitive replace with empty target and value", "[string]" )
{
    REQUIRE( String::replace( "", "SOLUTIONS", "", String::CASE_INSENSITIVE ) == "" );
}

TEST_CASE( "case insensitive replace with empty substitute and value", "[string]" )
{
    REQUIRE( String::replace( "Ltd", "", "Corvusoft SOLUTIONS", String::CASE_INSENSITIVE ) == "Corvusoft SOLUTIONS" );
}

TEST_CASE( "case insensitive replace with empty arguments", "[string]" )
{
    REQUIRE( String::replace( "", "", "", String::CASE_INSENSITIVE ) == "" );
}

TEST_CASE( "to_string", "[string]" )
{
    REQUIRE( String::to_string( Bytes( { 'a', 'b' } ) ) == "ab" );
}

TEST_CASE( "empty to_string", "[string]" )
{
    REQUIRE( String::to_string( Bytes( { } ) ) == "" );
}

TEST_CASE( "to_bytes", "[string]" )
{
    REQUIRE( String::to_bytes( "ab" ) == Bytes( { 'a', 'b' } ) );
}

TEST_CASE( "empty to_bytes", "[string]" )
{
    REQUIRE( String::to_bytes( "" ) == Bytes( { } ) );
}
