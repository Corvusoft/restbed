//System Includes
#include <memory>
#include <functional>

//Project Includes
#include <corvusoft/restbed/web_socket.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::function;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using restbed::WebSocket;

//External Namespaces

TEST_CASE( "a retrieved close handler is safe to invoke after its WebSocket is gone", "[web_socket]" )
{
    // set_close_handler installs a lambda that, given a socket, tears it down
    // through its manager. The handler is copyable via get_close_handler( ), so
    // it can outlive the WebSocket it came from. It must therefore key off the
    // socket argument rather than a captured this pointer, which would dangle
    // once the originating WebSocket is destroyed.
    function< void ( const shared_ptr< WebSocket > ) > handler;
    bool invoked = false;
    
    {
        auto origin = make_shared< WebSocket >( );
        origin->set_close_handler( [ &invoked ]( const shared_ptr< WebSocket > )
        {
            invoked = true;
        } );
        handler = origin->get_close_handler( );
    }
    
    // origin ( and its pimpl ) is now destroyed. Invoking the retrieved handler
    // with a live, independent socket must run the user callback and operate on
    // that socket, without touching the dead originating WebSocket.
    auto live = make_shared< WebSocket >( );
    REQUIRE_NOTHROW( handler( live ) );
    REQUIRE( invoked == true );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
