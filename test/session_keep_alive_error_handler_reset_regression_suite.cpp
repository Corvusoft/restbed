//System Includes
#include <string>
#include <thread>
#include <future>
#include <chrono>
#include <memory>
#include <cstdint>
#include <stdexcept>

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

TEST_CASE( "each request on a kept-alive connection can still report an error", "[session]" )
{
    // The handler routes every request into the session error handler ( a body
    // fetch that throws ). SessionImpl::get_error_handler invokes the error
    // handler at most once and never reset its flag, so on a kept-alive
    // connection the second request's error was silently swallowed.
    auto resource = make_shared< Resource >( );
    resource->set_path( "boom" );
    resource->set_method_handler( "GET", [ ]( const shared_ptr< Session > session )
    {
        session->fetch( static_cast< size_t >( 0 ), [ ]( const shared_ptr< Session >, const Bytes& )
        {
            throw 400;
        } );
    } );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 0 );
    
    auto service = make_shared< Service >( );
    service->publish( resource );
    service->set_error_handler( [ ]( const int status, const exception&, const shared_ptr< Session > session )
    {
        // Respond but keep the connection alive so the next request is served.
        session->yield( status, string( "XERRX" ), { { "Content-Length", "5" } } );
    } );
    service->set_ready_handler( [ ]( Service & service )
    {
        g_port.set_value( service.get_http_uri( )->get_port( ) );
    } );
    
    thread restbed_thread( [ service, settings ]( )
    {
        service->start( settings );
    } );
    
    const auto port = to_string( g_port.get_future( ).get( ) );
    
    auto io = make_shared< io_context >( );
    auto socket = make_shared< tcp::socket >( *io );
    tcp::resolver resolver( *io );
    connect( *socket, resolver.resolve( "localhost", port ) );
    
    // Two pipelined requests, each of which must produce an error response.
    asio::write( *socket, buffer( string(
                                      "GET /boom HTTP/1.1\r\nHost: localhost\r\n\r\n"
                                      "GET /boom HTTP/1.1\r\nHost: localhost\r\n\r\n" ) ) );
                                      
    // Read on a detached worker until both error responses arrive. A timeout
    // guards the buggy path, where the second error is swallowed and never
    // answered, so the read would otherwise block forever.
    auto result = make_shared< promise< string > >( );
    auto future = result->get_future( );
    
    thread( [ socket, result ]( )
    {
        string accumulated;
        char chunk[ 256 ];
        
        while ( count_occurrences( accumulated, "XERRX" ) < 2 )
        {
            error_code code;
            const size_t length = socket->read_some( buffer( chunk ), code );
            accumulated.append( chunk, length );
            
            if ( code )
            {
                break;
            }
        }
        
        result->set_value( accumulated );
    } ).detach( );
    
    const auto status = future.wait_for( seconds( 5 ) );
    const string response = ( status == future_status::ready ) ? future.get( ) : string( );
    
    error_code code;
    socket->close( code );
    service->stop( );
    restbed_thread.join( );
    
    REQUIRE( status == future_status::ready );
    REQUIRE( count_occurrences( response, "XERRX" ) == 2 );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
