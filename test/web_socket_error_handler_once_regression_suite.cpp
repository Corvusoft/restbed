//System Includes
#include <memory>
#include <system_error>

//Project Includes
#include <corvusoft/restbed/web_socket.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::errc;
using std::error_code;
using std::shared_ptr;
using std::make_shared;
using std::make_error_code;

//Project Namespaces
using restbed::WebSocket;

//External Namespaces

TEST_CASE( "the user's WebSocket error handler is invoked at most once", "[web_socket]" )
{
    auto socket = make_shared< WebSocket >( );
    
    int invocations = 0;
    socket->set_error_handler( [ &invocations ]( const shared_ptr< WebSocket >, const error_code )
    {
        invocations++;
    } );
    
    const auto handler = socket->get_error_handler( );
    
    handler( socket, make_error_code( errc::bad_message ) );
    handler( socket, make_error_code( errc::connection_reset ) );
    
    REQUIRE( invocations == 1 );
}

int main( int argc, char* argv[] )
{
    return Catch::Session().run( argc, argv );
}
