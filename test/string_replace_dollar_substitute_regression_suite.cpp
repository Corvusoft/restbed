//System Includes
#include <string>

//Project Includes
#include <corvusoft/restbed/string.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::string;

//Project Namespaces
using restbed::String;

//External Namespaces

TEST_CASE( "string replace treats a '$' in the substitute literally", "[string]" )
{
    // String::replace is a literal substitution: the target is regex-escaped so
    // it matches literally. The substitute must likewise be literal, but it was
    // handed straight to std::regex_replace, which interprets ECMAScript
    // replacement syntax ( $1..$99, $&, $`, $', $$ ). A substitute containing a
    // bare '$' was therefore mangled instead of inserted verbatim.
    REQUIRE( String::replace( "X", "$5.00", "Price: X here" ) == "Price: $5.00 here" );
    
    // A trailing group-style reference must survive too.
    REQUIRE( String::replace( "X", "$1", "value=X" ) == "value=$1" );
    
    // '$&' ( whole-match ) and '$$' must not be expanded.
    REQUIRE( String::replace( "X", "a$&b", "X" ) == "a$&b" );
    REQUIRE( String::replace( "X", "$$", "X" ) == "$$" );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
