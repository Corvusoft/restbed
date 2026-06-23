//System Includes
#include <string>
#include <thread>
#include <future>
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
}

TEST_CASE( "set_method_handler replaces a previously registered handler", "[resource]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "test" );
    
    resource->set_method_handler( "GET", [ ]( const shared_ptr< Session > session )
    {
        session->close( 200, string( "first" ), { { "Content-Length", "5" } } );
    } );
    // Re-registering must replace the handler above, not be ignored.
    resource->set_method_handler( "GET", [ ]( const shared_ptr< Session > session )
    {
        session->close( 200, string( "second" ), { { "Content-Length", "6" } } );
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
    
    asio::streambuf buffer_in;
    error_code error;
    asio::read( socket, buffer_in, error );
    
    const string response( ( std::istreambuf_iterator< char >( &buffer_in ) ), std::istreambuf_iterator< char >( ) );
    
    socket.close( error );
    service->stop( );
    restbed_thread.join( );
    
    REQUIRE( response.find( "second" ) not_eq string::npos );
    REQUIRE( response.find( "first" ) == string::npos );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
