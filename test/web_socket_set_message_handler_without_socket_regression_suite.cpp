//System Includes
#include <memory>
#include <system_error>

//Project Includes
#include <corvusoft/restbed/web_socket.hpp>
#include <corvusoft/restbed/web_socket_message.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::make_shared;
using std::error_code;
using std::shared_ptr;

//Project Namespaces
using restbed::WebSocket;
using restbed::WebSocketMessage;

//External Namespaces

TEST_CASE( "setting a message handler on a WebSocket with no socket does not crash", "[web_socket]" )
{
    auto socket = make_shared< WebSocket >( );

    error_code reported;
    bool invoked = false;
    socket->set_error_handler( [ &reported, &invoked ]( const shared_ptr< WebSocket >, const error_code code )
    {
        reported = code;
        invoked = true;
    } );

    // Setting a message handler starts the read loop via WebSocketImpl::listen( ),
    // which dereferenced m_socket. On a socket-less WebSocket m_socket is null, so
    // this crashed. listen( ) must guard the socket and report through the error
    // handler instead, mirroring the guards in send( ) / close( ).
    REQUIRE_NOTHROW( socket->set_message_handler( [ ]( const shared_ptr< WebSocket >, const shared_ptr< WebSocketMessage > ) { } ) );

    REQUIRE( invoked == true );
    REQUIRE( reported == std::make_error_code( std::errc::not_connected ) );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
