//System Includes
#include <string>
#include <thread>
#include <future>
#include <memory>
#include <chrono>
#include <cstdint>
#include <system_error>

//Project Includes
#include <restbed>

//External Includes
#include <asio.hpp>
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::string;
using std::thread;
using std::promise;
using std::weak_ptr;
using std::to_string;
using std::shared_ptr;
using std::error_code;
using std::make_shared;
using std::chrono::milliseconds;

//Project Namespaces
using namespace restbed;

//External Namespaces
using asio::buffer;
using asio::ip::tcp;
using asio::connect;
using asio::io_context;

namespace
{
    weak_ptr< WebSocket > g_socket;
    promise< void > g_upgraded;
    promise< uint16_t > g_port;
}

TEST_CASE( "the manager does not keep a WebSocket alive after it is finished with", "[web_socket]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "test" );
    resource->set_method_handler( "GET", [ ]( const shared_ptr< Session > session )
    {
        session->upgrade( 101, [ ]( const shared_ptr< WebSocket > socket )
        {
            // Observe the socket weakly and start its read loop. We deliberately
            // retain no shared_ptr, so the only strong references are the in-flight
            // read and -- with the defect -- the manager's registry.
            g_socket = socket;
            socket->set_message_handler( [ ]( const shared_ptr< WebSocket >, const shared_ptr< WebSocketMessage > ) { } );
            g_upgraded.set_value( );
        } );
    } );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 0 );
    
    auto service = make_shared< Service >( );
    service->publish( resource );
    service->set_ready_handler( [ ]( Service & service )
    {
        g_port.set_value( service.get_http_uri( )->get_port( ) );
    } );
    
    thread restbed_thread( [ service, settings ]( )
    {
        service->start( settings );
    } );
    
    const auto port = to_string( g_port.get_future( ).get( ) );
    
    io_context io;
    tcp::socket socket( io );
    tcp::resolver resolver( io );
    connect( socket, resolver.resolve( "localhost", port ) );
    
    asio::write( socket, buffer( string( "GET /test HTTP/1.1\r\nHost: localhost\r\n\r\n" ) ) );
    
    // Wait until the server has upgraded and armed the WebSocket read loop.
    g_upgraded.get_future( ).get( );
    
    // Drop the connection; the pending read completes with an error and releases
    // its reference to the socket.
    error_code ignored;
    socket.close( ignored );
    
    // With the fix the socket is freed promptly; with the leak the registry's
    // strong reference keeps it alive for the service lifetime, so this polls
    // until expiry rather than asserting immediately.
    bool expired = false;
    
    for ( int attempt = 0; attempt < 300 and not expired; attempt++ )
    {
        expired = g_socket.expired( );
        
        if ( not expired )
        {
            std::this_thread::sleep_for( milliseconds( 10 ) );
        }
    }
    
    service->stop( );
    restbed_thread.join( );
    
    REQUIRE( expired );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
