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

TEST_CASE( "uri get parameter fails to handle empty values", "[uri]" )
{
    multimap< string, string > expectation {{"param", "1"}};
    Uri uri_with_value( "http://www.corvusoft.co.uk?param=1" );
    REQUIRE( uri_with_value.get_query_parameters( ) == expectation );

    expectation = {{"param", ""}};
    Uri uri_blank_param( "http://www.corvusoft.co.uk?param=" );
    REQUIRE( uri_blank_param.get_query_parameters( ) == expectation );

    Uri uri_empty_param( "http://www.corvusoft.co.uk?param" );
    REQUIRE( uri_empty_param.get_query_parameters( ) == expectation );
}
