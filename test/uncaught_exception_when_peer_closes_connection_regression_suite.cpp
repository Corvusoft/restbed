//System Includes
#include <thread>
#include <future>
#include <string>
#include <cstdint>
#include <memory>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <asio.hpp>
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::thread;
using std::promise;
using std::to_string;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces
using asio::ip::tcp;
using asio::connect;
using asio::io_context;
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

TEST_CASE( "peer closes connection without sending data", "[service]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "test" );

    auto settings = make_shared< Settings >( );
    settings->set_port( 0 );

    promise< uint16_t > bound_port;

    auto service = make_shared< Service >( );
    service->publish( resource );
    service->set_ready_handler( [ &bound_port ]( Service & service )
    {
        bound_port.set_value( service.get_http_uri( )->get_port( ) );
    } );

    thread restbed_thread( worker, service, settings );

    const auto port = to_string( bound_port.get_future( ).get( ) );

    io_context io_context;
    tcp::socket socket( io_context );
    tcp::resolver resolver( io_context );
    connect( socket, resolver.resolve( "localhost", port ) );

    socket.close( );
    
    service->stop( );
    
    restbed_thread.join( );
    
    REQUIRE_FALSE( exception_was_thrown );
}

int main(int argc, char* argv[])
{
    return Catch::Session().run(argc, argv);
}
