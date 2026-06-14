//System Includes
#include <atomic>
#include <string>
#include <thread>
#include <future>
#include <chrono>
#include <cstdint>
#include <memory>
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
using std::to_string;
using std::shared_ptr;
using std::error_code;
using std::make_shared;
using std::future_status;
using std::chrono::seconds;

//Project Namespaces
using namespace restbed;

//External Namespaces
using asio::buffer;
using asio::ip::tcp;
using asio::connect;
using asio::io_context;

namespace
{
    promise< uint16_t > g_port;
    promise< void > g_upgraded;
    promise< string > g_message;
    std::atomic< bool > g_signalled{ false };

    void record( const shared_ptr< WebSocket >, const shared_ptr< WebSocketMessage > message )
    {
        const auto data = message->get_data( );
        const string text( reinterpret_cast< const char* >( data.data( ) ), data.size( ) );

        if ( not g_signalled.exchange( true ) )
        {
            g_message.set_value( text );
        }
    }
}

TEST_CASE( "setting the WebSocket message handler twice does not corrupt framing", "[web_socket]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "test" );
    resource->set_method_handler( "GET", [ ]( const shared_ptr< Session > session )
    {
        session->upgrade( 101, [ ]( const shared_ptr< WebSocket > socket )
        {
            // Two handlers: the second replaces the first. This must not start a
            // second read loop -- one frame must still be parsed by one reader.
            socket->set_message_handler( [ ]( const shared_ptr< WebSocket >, const shared_ptr< WebSocketMessage > ) { } );
            socket->set_message_handler( record );
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

    thread restbed_thread( [ service, settings ]( ) { service->start( settings ); } );

    const auto port = to_string( g_port.get_future( ).get( ) );

    io_context io;
    tcp::socket socket( io );
    tcp::resolver resolver( io );
    connect( socket, resolver.resolve( "localhost", port ) );

    asio::write( socket, buffer( string( "GET /test HTTP/1.1\r\nHost: localhost\r\n\r\n" ) ) );

    g_upgraded.get_future( ).get( );

    // A single masked TEXT frame carrying "hi": FIN+TEXT, MASK+len 2, key
    // 01 02 03 04, payload 'h'^01 'i'^02.
    const unsigned char frame[ ] = { 0x81, 0x82, 0x01, 0x02, 0x03, 0x04, 0x69, 0x6B };
    asio::write( socket, buffer( frame, sizeof( frame ) ) );

    auto future = g_message.get_future( );
    const auto status = future.wait_for( seconds( 5 ) );

    error_code ignored;
    socket.close( ignored );
    service->stop( );
    restbed_thread.join( );

    REQUIRE( status == future_status::ready );
    REQUIRE( future.get( ) == "hi" );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
