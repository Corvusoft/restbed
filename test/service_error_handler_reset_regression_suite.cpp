//System Includes
#include <chrono>
#include <string>
#include <thread>
#include <future>
#include <cstdint>
#include <memory>
#include <exception>
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
using std::exception;
using std::to_string;
using std::shared_ptr;
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
    bool g_server_exception = false;

    void worker( shared_ptr< Service > service, shared_ptr< Settings > settings )
    {
        // worker_limit defaults to 0, so start( ) drives io_context::run( ) on
        // this thread; a handler that throws propagates straight out of run( ).
        try
        {
            service->start( settings );
        }
        catch ( const exception& )
        {
            g_server_exception = true;
        }
    }
}

TEST_CASE( "resetting the service error handler to nullptr restores the default", "[service]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "test" );

    auto settings = make_shared< Settings >( );
    settings->set_port( 0 );

    promise< uint16_t > bound_port;

    auto service = make_shared< Service >( );
    service->publish( resource );

    // Passing nullptr is documented to fall back to the built-in default error
    // handler. The defect overwrote the freshly assigned default with the null
    // argument, leaving the handler empty so an erroring request invoked a null
    // std::function ( std::bad_function_call ) on the worker thread.
    service->set_error_handler( nullptr );

    service->set_ready_handler( [ &bound_port ]( Service & service )
    {
        bound_port.set_value( service.get_http_uri( )->get_port( ) );
    } );

    thread restbed_thread( worker, service, settings );

    const auto port = to_string( bound_port.get_future( ).get( ) );

    io_context io;
    tcp::socket socket( io );
    tcp::resolver resolver( io );
    connect( socket, resolver.resolve( "localhost", port ) );

    // A complete-but-malformed request: the "\r\n\r\n" terminator lets the read
    // complete so the server reaches parse_request, where the status line fails
    // to parse and the error handler is invoked.
    const string request = "PARSE ME\r\n\r\n";
    asio::write( socket, buffer( request ) );

    // Give the worker ample time to read and parse the request. With the defect
    // the error handler is a null std::function, so parsing throws
    // std::bad_function_call straight out of io_context::run( ) and the worker
    // thread is already gone before stop( ) is even called. With the default
    // handler in place the request is answered and the worker keeps running.
    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

    std::error_code ignored;
    socket.close( ignored );
    service->stop( );
    restbed_thread.join( );

    REQUIRE_FALSE( g_server_exception );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
