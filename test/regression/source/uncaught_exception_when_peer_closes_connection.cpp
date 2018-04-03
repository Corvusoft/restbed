//System Includes
#include <thread>
#include <chrono>
#include <memory>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <asio.hpp>
#include <catch.hpp>

//System Namespaces
using std::thread;
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

bool exception_was_thrown = false;

void worker( shared_ptr< Service > service, shared_ptr< Settings > settings )
{
    try
    {
        service->start( settings );
    }
    catch ( const system_error& se )
    {
        if ( se.code( ) == asio::error::eof )
        {
            exception_was_thrown = true;
        }
    }
}

void wait_for_service_initialisation( void )
{
    std::this_thread::sleep_for( seconds( 1 ) );
}

TEST_CASE( "peer closes connection without sending data", "[service]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "test" );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    auto service = make_shared< Service >( );
    service->publish( resource );
    
    thread restbed_thread( worker, service, settings );
    
    wait_for_service_initialisation( );
    
    io_service io_service;
    tcp::socket socket( io_service );
    tcp::resolver resolver( io_service );
    connect( socket, resolver.resolve( { "localhost", "1984" } ) );
    
    socket.close( );
    
    service->stop( );
    
    restbed_thread.join( );
    
    REQUIRE_FALSE( exception_was_thrown );
}
