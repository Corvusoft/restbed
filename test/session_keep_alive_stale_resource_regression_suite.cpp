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

TEST_CASE( "a not-found on a kept-alive connection does not inherit the prior resource headers", "[session]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "exists" );
    resource->set_default_header( "X-Resource", "present" );
    resource->set_method_handler( "GET", [ ]( const shared_ptr< Session > session )
    {
        // Respond and keep the connection alive for the next request.
        session->yield( 200, string( "ok" ), { { "Content-Length", "2" } } );
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
    
    // Pipelined: a hit on the resource, then a miss on the same connection.
    asio::write( socket, buffer( string(
                                     "GET /exists HTTP/1.1\r\nHost: localhost\r\n\r\n"
                                     "GET /missing HTTP/1.1\r\nHost: localhost\r\n\r\n" ) ) );
                                     
    asio::streambuf buffer_in;
    error_code error;
    asio::read( socket, buffer_in, error );
    
    string response( ( std::istreambuf_iterator< char >( &buffer_in ) ), std::istreambuf_iterator< char >( ) );
    
    socket.close( error );
    service->stop( );
    restbed_thread.join( );
    
    std::transform( response.begin( ), response.end( ), response.begin( ), [ ]( const char value )
    {
        return static_cast< char >( ::tolower( static_cast< unsigned char >( value ) ) );
    } );
    
    // The header belongs only to the first ( resource ) response, not the 404.
    REQUIRE( count_occurrences( response, "x-resource" ) == 1 );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
