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

TEST_CASE( "uri encode fails to handle high (non-ascii) bytes", "[uri]" )
{
    // 'é' encoded as UTF-8 is the two bytes 0xC3 0xA9. Each byte is >= 0x80, so
    // when stored in a (signed) char it is negative. The encoder must treat the
    // byte as unsigned when extracting the high nibble; otherwise the right-shift
    // produces a negative index into the hex lookup table (out-of-bounds read)
    // and emits a corrupt high nibble.
    const string utf8 = "\xC3\xA9";

    REQUIRE( Uri::encode( utf8 ) == "%C3%A9" );

    // Boundary: 0x80 is the first byte that becomes negative as a signed char.
    REQUIRE( Uri::encode( string( 1, '\x80' ) ) == "%80" );
    REQUIRE( Uri::encode( string( 1, '\xFF' ) ) == "%FF" );
}

int main( int argc, char* argv[] )
{
    return Catch::Session().run( argc, argv );
}
