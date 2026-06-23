//System Includes

//Project Includes
#include <corvusoft/restbed/web_socket.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces

//Project Namespaces
using restbed::WebSocket;

//External Namespaces

TEST_CASE( "a WebSocket with no underlying socket reports closed", "[web_socket]" )
{
    WebSocket socket;
    
    REQUIRE( socket.is_open( ) == false );
    // is_closed( ) must be the negation of is_open( ): a socket-less WebSocket
    // is not open, therefore it is closed.
    REQUIRE( socket.is_closed( ) == true );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
