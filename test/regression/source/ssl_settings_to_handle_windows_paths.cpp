//System Includes
#include <map>
#include <string>
#include <stdexcept>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::multimap;
using std::invalid_argument;

//Project Namespaces
using namespace restbed;

//External Namespaces

TEST_CASE( "ssl settings to handle windows paths", "[ssl]" )
{
    try {
        SSLSettings settings;
        settings.set_private_key(Uri( "file://C:/Program%20Files/RestServer/key.pem", true ));

        REQUIRE( settings.get_private_key( ) == "C:/Program Files/RestServer/key.pem");
    }
    catch ( invalid_argument ) {
        REQUIRE( false );
    }
}
