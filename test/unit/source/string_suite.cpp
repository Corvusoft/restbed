//System Includes
#include <map>
#include <string>
#include <vector>

//Project Includes
#include "corvusoft/restbed/string.hpp"

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::vector;
using std::multimap;

//Project Namespaces
using restbed::String;

//External Namespaces

TEST_CASE( "uppercase to lowercase", "[string]" )
{
    REQUIRE( String::lowercase( "CORVUSOFT" ) == "corvusoft" );
}

TEST_CASE( "lowercase to lowercase", "[string]" )
{
    REQUIRE( String::lowercase( "corvusoft" ) == "corvusoft" );
}

TEST_CASE( "mixedcase to lowercase", "[string]" )
{
    REQUIRE( String::lowercase( "CoRvUSoFt" ) == "corvusoft" );
}

TEST_CASE( "empty to lowercase", "[string]" )
{
    REQUIRE( String::lowercase( "" ) == "" );
}

TEST_CASE( "uppercase to uppercase", "[string]" )
{
    REQUIRE( String::uppercase( "corvusoft" ) == "CORVUSOFT" );
}

TEST_CASE( "lowercase to uppercase", "[string]" )
{
    REQUIRE( String::uppercase( "corvusoft" ) == "CORVUSOFT" );
}

TEST_CASE( "mixedcase to uppercase", "[string]" )
{
    REQUIRE( String::uppercase( "CoRvUSoFt" ) == "CORVUSOFT" );
}

TEST_CASE( "empty to uppercase", "[string]" )
{
    REQUIRE( String::uppercase( "" ) == "" );
}

TEST_CASE( "format", "[string]" )
{
    REQUIRE( String::format( "Corvusoft %s", "Solutions" ) == "Corvusoft Solutions" );
}

TEST_CASE( "format with no specifiers", "[string]" )
{
    REQUIRE( String::format( "Corvusoft" ) == "Corvusoft" );
}

TEST_CASE( "format with empty", "[string]" )
{
    REQUIRE( String::format( "" ) == "" );
}

TEST_CASE( "format with string length equal to initial buffer length", "[string]" )
{
    size_t length = String::FORMAT_BUFFER_INITIAL_LENGTH;
    string str( length, ' ' );
    for ( size_t i = 0; i < length; i++ ) {
        str[ i ] = ( i % 95 ) + 32;
    }
    REQUIRE( String::format( "%s", str.c_str() ) == str );
}

TEST_CASE( "format with string length equal to initial buffer length + 1", "[string]" )
{
    size_t length = String::FORMAT_BUFFER_INITIAL_LENGTH + 1;
    string str( length, ' ' );
    for ( size_t i = 0; i < length; i++ ) {
        str[ i ] = ( i % 95 ) + 32;
    }
    REQUIRE( String::format( "%s", str.c_str() ) == str );
}

TEST_CASE( "split", "[string]" )
{
    REQUIRE( String::split( "Corvusoft Solutions", ' ' ) == vector< string >( { "Corvusoft", "Solutions" } ) );
}

TEST_CASE( "split with missing delimiter", "[string]" )
{
    REQUIRE( String::split( "Corvusoft Solutions", '+' ) == vector< string >( { "Corvusoft Solutions" } ) );
}

TEST_CASE( "split with empty delimiter", "[string]" )
{
    char expectation = 0;
    REQUIRE( String::split( "Corvusoft Solutions", expectation ) == vector< string >( { "Corvusoft Solutions" } ) );
}

TEST_CASE( "join map to string", "[string]" )
{
    multimap< string, string > values = { { "fields", "id,rev" }, { "sort", "rev" } };
    REQUIRE( String::join( values, "=", "&" ) == "fields=id,rev&sort=rev" );
}

TEST_CASE( "join map to string with missing value & pair delimiters", "[string]" )
{
    multimap< string, string > values = { { "fields", "id,rev" }, { "sort", "rev" } };
    REQUIRE( String::join( values, "", "" ) == "fieldsid,revsortrev" );
}

TEST_CASE( "join empty map to string", "[string]" )
{
    multimap< string, string > values;
    REQUIRE( String::join( values, "=", "&" ) == "" );
}

TEST_CASE( "join map to string with missing value delimiter", "[string]" )
{
    multimap< string, string > values = { { "fields", "id,rev" }, { "sort", "rev" } };
    REQUIRE( String::join( values, "", "&" ) == "fieldsid,rev&sortrev" );
}

TEST_CASE( "join map to string with missing pair delimiter", "[string]" )
{
    multimap< string, string > values = { { "fields", "id,rev" }, { "sort", "rev" } };
    REQUIRE( String::join( values, "=", "" ) == "fields=id,revsort=rev" );
}

TEST_CASE( "remove", "[string]" )
{
    REQUIRE( String::remove( "Solutions", "Corvusoft Solutions" ) == "Corvusoft " );
}

TEST_CASE( "remove multiple", "[string]" )
{
    REQUIRE( String::remove( "dot", "dot dash dot dash dash" ) == " dash  dash dash" );
}

TEST_CASE( "remove with missing target", "[string]" )
{
    REQUIRE( String::remove( "ltd", "Corvusoft Solutions" ) == "Corvusoft Solutions" );
}

TEST_CASE( "remove with empty target", "[string]" )
{
    REQUIRE( String::remove( "", "Corvusoft Solutions" ) == "Corvusoft Solutions" );
}

TEST_CASE( "remove with empty value", "[string]" )
{
    REQUIRE( String::remove( " Solutions", "" ) == "" );
}

TEST_CASE( "remove with empty arguments", "[string]" )
{
    REQUIRE( String::remove( "", "" ) == "" );
}

TEST_CASE( "replace", "[string]" )
{
    REQUIRE( String::replace( "ltd", "Solutions", "Corvusoft ltd" ) == "Corvusoft Solutions" );
}

TEST_CASE( "replace multiple", "[string]" )
{
    REQUIRE( String::replace( "dot", "ping", "dot dash dot dash dash" ) == "ping dash ping dash dash" );
}

TEST_CASE( "replace with missing target", "[string]" )
{
    REQUIRE( String::replace( "ltd", "Solutions", "Corvusoft Solutions" ) == "Corvusoft Solutions" );
}

TEST_CASE( "replace with empty target", "[string]" )
{
    REQUIRE( String::replace( "", "Solutions", "Corvusoft ltd" ) == "Corvusoft ltd" );
}

TEST_CASE( "replace with empty substitute", "[string]" )
{
    REQUIRE( String::replace( "ltd", "", "Corvusoft ltd" ) == "Corvusoft " );
}

TEST_CASE( "replace with empty value", "[string]" )
{
    REQUIRE( String::replace( "ltd", "Solutions", "" ) == "" );
}

TEST_CASE( "replace with empty target and substitute", "[string]" )
{
    REQUIRE( String::replace( "", "", "Corvusoft ltd" ) == "Corvusoft ltd" );
}

TEST_CASE( "replace with empty target and value", "[string]" )
{
    REQUIRE( String::replace( "", "Solutions", "" ) == "" );
}

TEST_CASE( "replace with empty substitue and value", "[string]" )
{
    REQUIRE( String::replace( "ltd", "", "" ) == "" );
}

TEST_CASE( "replace with empty arguments", "[string]" )
{
    REQUIRE( String::replace( "", "", "" ) == "" );
}
