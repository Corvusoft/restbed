//System Includes
#include <string>

//Project Includes
#include <corvusoft/restbed/common.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::string;

//Project Namespaces
using restbed::Common;

//External Namespaces

TEST_CASE( "parse_parameter rejects trailing garbage for arithmetic types", "[common]" )
{
    REQUIRE( Common::parse_parameter< int >( "12abc", -1 ) == -1 );
    REQUIRE( Common::parse_parameter< int >( "0x10", -1 ) == -1 );
    REQUIRE( Common::parse_parameter< double >( "3.5xyz", -1.0 ) == -1.0 );
}

TEST_CASE( "parse_parameter rejects a negative value for unsigned types", "[common]" )
{
    REQUIRE( Common::parse_parameter< unsigned long >( "-1", 7ul ) == 7ul );
    REQUIRE( Common::parse_parameter< unsigned int >( "  -42", 9u ) == 9u );
}

TEST_CASE( "parse_parameter still accepts well-formed values", "[common]" )
{
    REQUIRE( Common::parse_parameter< int >( "42", -1 ) == 42 );
    REQUIRE( Common::parse_parameter< int >( "-5", 0 ) == -5 );
    REQUIRE( Common::parse_parameter< unsigned long >( "123", 7ul ) == 123ul );
    REQUIRE( Common::parse_parameter< double >( "3.5", 0.0 ) == 3.5 );

    // Surrounding whitespace remains tolerated.
    REQUIRE( Common::parse_parameter< int >( "42 ", -1 ) == 42 );
    REQUIRE( Common::parse_parameter< int >( "  7", -1 ) == 7 );
}

int main( int argc, char* argv[] )
{
    return Catch::Session().run( argc, argv );
}
