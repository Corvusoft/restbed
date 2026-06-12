//System Includes
#include <string>
#include <thread>
#include <chrono>
#include <future>
#include <memory>

//Project Includes
#include <corvusoft/restbed/string.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::string;
using std::thread;
using std::promise;
using std::make_shared;
using std::future_status;
using std::chrono::seconds;

//Project Namespaces
using restbed::String;

//External Namespaces

TEST_CASE( "string replace loops forever when the substitute contains the target", "[string]" )
{
    // Replacing "a" with "ba" should resolve to "ba" in a single pass. The buggy
    // implementation re-scans the result after substituting, so each pass keeps
    // finding the freshly-inserted "a" and the loop never terminates.
    //
    // Run the call on a detached worker so a hang manifests as a clean timeout
    // failure instead of wedging the whole test binary. A std::async future would
    // block in its destructor, so a raw detached thread with a shared promise is
    // used instead.
    auto result = make_shared< promise< string > >( );
    auto future = result->get_future( );

    thread( [ result ]( )
    {
        result->set_value( String::replace( "a", "ba", "a" ) );
    } ).detach( );

    REQUIRE( future.wait_for( seconds( 2 ) ) == future_status::ready );
    REQUIRE( future.get( ) == "ba" );
}

int main( int argc, char* argv[] )
{
    return Catch::Session().run( argc, argv );
}
