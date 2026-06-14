//System Includes
#include <memory>

//Project Includes
#include <corvusoft/restbed/web_socket.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::make_shared;

//Project Namespaces
using restbed::WebSocket;

//External Namespaces

TEST_CASE( "closing a WebSocket with no underlying socket does not crash", "[web_socket]" )
{
    auto socket = make_shared< WebSocket >( );

    // A socket-less WebSocket has neither a manager nor an underlying socket.
    // close( ) must guard against both being null instead of dereferencing
    // them, mirroring the null-socket guards in is_open( )/is_closed( ).
    REQUIRE_NOTHROW( socket->close( ) );
    REQUIRE( socket->is_closed( ) == true );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
