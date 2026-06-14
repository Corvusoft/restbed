//System Includes
#include <string>

//Project Includes
#include <corvusoft/restbed/uri.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::string;

//Project Namespaces
using restbed::Uri;

//External Namespaces

TEST_CASE( "Uri copy-assignment preserves the relative flag", "[uri]" )
{
    Uri absolute( "http://example.com/absolute" );
    Uri relative( "http://example.com/relative", true );

    REQUIRE( absolute.is_relative( ) == false );
    REQUIRE( relative.is_relative( ) == true );

    absolute = relative;

    // Assignment must copy the whole value, not just the URI string, so the
    // relative flag has to come across with it ( the copy constructor already
    // does this ).
    REQUIRE( absolute.to_string( ) == relative.to_string( ) );
    REQUIRE( absolute.is_relative( ) == true );
}

TEST_CASE( "Uri copy-assignment clears the relative flag when assigned an absolute", "[uri]" )
{
    Uri relative( "http://example.com/relative", true );
    Uri absolute( "http://example.com/absolute" );

    relative = absolute;

    REQUIRE( relative.to_string( ) == absolute.to_string( ) );
    REQUIRE( relative.is_relative( ) == false );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
