//System Includes
#include <memory>

//Project Includes
#include <corvusoft/restbed/web_socket.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::make_shared;
using std::shared_ptr;

//Project Namespaces
using restbed::WebSocket;

//External Namespaces

TEST_CASE( "invoking a close handler on a WebSocket with no manager does not crash", "[web_socket]" )
{
    auto socket = make_shared< WebSocket >( );

    bool invoked = false;
    socket->set_close_handler( [ &invoked ]( const shared_ptr< WebSocket > )
    {
        invoked = true;
    } );

    // close( ) guards m_manager before its own destroy( ) call, but the close
    // handler installed by set_close_handler( ) also calls m_manager->destroy( ).
    // On a socket-less / manager-less WebSocket m_manager is null, so firing the
    // handler dereferenced null and crashed. The wrapper must guard m_manager
    // just like close( ) does.
    REQUIRE_NOTHROW( socket->close( ) );
    REQUIRE( invoked == true );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
