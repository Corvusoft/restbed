//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restbed/string.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::string;
using std::multimap;

//Project Namespaces
using restbed::String;

//External Namespaces

TEST_CASE( "join preserves a value that ends with the delimiter character", "[string]" )
{
    const multimap< string, string > values = { { "path", "/a/" } };
    
    // Only the one appended "/" should be dropped, leaving the value's own
    // trailing slash intact.
    REQUIRE( String::join( values, "=", "/" ) == "path=/a/" );
}

TEST_CASE( "join treats a multi-character delimiter as a string, not a char set", "[string]" )
{
    const multimap< string, string > values = { { "a", "b>" } };
    
    // result is "a=b>><"; only the trailing "><" delimiter is removed.
    REQUIRE( String::join( values, "=", "><" ) == "a=b>" );
}

int main( int argc, char* argv[] )
{
    return Catch::Session().run( argc, argv );
}
