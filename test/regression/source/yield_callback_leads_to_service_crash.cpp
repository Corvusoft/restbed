//System Includes
#include <thread>
#include <memory>
#include <chrono>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::chrono::seconds;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_handler( const shared_ptr< Session > session )
{
    session->yield( OK, "result", { { "Content-Length", "6" } } );
    
    for ( int count = 0; count < 5; ++count )
    {
        session->yield( "result" );
    }
    
    session->close( );
}

TEST_CASE( "yield callback leads to service crash", "[service]" )
{
    auto resource = make_shared< Resource >();
    resource->set_path( "test" );
    resource->set_method_handler( "GET", get_handler );
    
    auto settings = make_shared< Settings >();
    settings->set_port( 1984 );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [&worker]( Service & service )
    {
        worker = make_shared< thread >( [&service]()
        {
            auto request = make_shared< Request >();
            request->set_method( "GET" );
            request->set_port( 1984 );
            request->set_host( "localhost" );
            request->set_path( "/test" );
            
            auto response = Http::sync( request );
            
            REQUIRE( 200 == response->get_status_code() );
            
            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join();
}
