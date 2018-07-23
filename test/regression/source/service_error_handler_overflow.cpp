//System Includes
#include <memory>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <stdexcept>

//Project Includes
#include <restbed>

//External Includes
#include <asio.hpp>
#include <catch.hpp>

//System Namespaces
using std::string;
using std::thread;
using std::exception;
using std::shared_ptr;
using std::make_shared;
using std::chrono::seconds;

//Project Namespaces
using namespace restbed;

//External Namespaces
using asio::ip::tcp;
using asio::connect;
using asio::io_service;
using asio::system_error;

void error_handler( const int, const exception&, const std::shared_ptr< Session > session )
{
    static unsigned int counter = 0;
    counter++;
    
    if ( counter > 1 )
    {
        REQUIRE( false );
    }
    
    session->close( 444 );
}

void post_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    
    size_t content_length = request->get_header( "Content-Length", 0 );
    
    session->fetch( content_length, [ ]( const shared_ptr< Session > session, const Bytes& )
    {
        session->close( OK, "Hello, World!\n", { { "Content-Length", "14" }, { "Connection", "close" } } );
    } );
}

TEST_CASE( "service error handler overflow", "[service]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "test" );
    resource->set_method_handler( "POST", post_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_error_handler( error_handler );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            io_service io_service;
            tcp::socket socket( io_service );
            tcp::resolver resolver( io_service );
            connect( socket, resolver.resolve( { "localhost", "1984" } ) );
            
            string request = "POST /test HTTP/1.1\r\nContent-Length: 1024\r\n\r\nABCDEFG";
            
            socket.write_some( asio::buffer( request.data( ), request.size( ) ) );
            socket.close( );
            
            std::this_thread::sleep_for( seconds( 1 ) );
            service.stop( );
        } );
    } );
    
    service.start( settings );
    worker->join( );
    
    REQUIRE( true );
}
