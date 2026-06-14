//System Includes
#include <string>
#include <thread>
#include <future>
#include <cstdint>
#include <memory>
#include <algorithm>
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

    size_t count_occurrences( const string& haystack, const string& needle )
    {
        size_t count = 0;

        for ( auto position = haystack.find( needle ); position not_eq string::npos; position = haystack.find( needle, position + needle.size( ) ) )
        {
            count++;
        }

        return count;
    }
}

TEST_CASE( "a response header overrides a default header of the same name", "[service]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "test" );
    resource->set_method_handler( "GET", [ ]( const shared_ptr< Session > session )
    {
        session->close( 200, string( "data" ), { { "Content-Type", "application/json" }, { "Content-Length", "4" } } );
    } );

    auto settings = make_shared< Settings >( );
    settings->set_port( 0 );
    // Collides with the Content-Type the handler sets on the response.
    settings->set_default_header( "Content-Type", "text/plain" );

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

    asio::streambuf buffer_in;
    error_code error;
    asio::read( socket, buffer_in, error );

    const string response( ( std::istreambuf_iterator< char >( &buffer_in ) ), std::istreambuf_iterator< char >( ) );

    socket.close( error );
    service->stop( );
    restbed_thread.join( );

    string lowered = response;
    std::transform( lowered.begin( ), lowered.end( ), lowered.begin( ), [ ]( const char value )
    {
        return static_cast< char >( ::tolower( static_cast< unsigned char >( value ) ) );
    } );

    const auto headers = lowered.substr( 0, lowered.find( "\r\n\r\n" ) );

    REQUIRE( count_occurrences( headers, "content-type:" ) == 1 );
    REQUIRE( headers.find( "application/json" ) not_eq string::npos );
    REQUIRE( headers.find( "text/plain" ) == string::npos );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
