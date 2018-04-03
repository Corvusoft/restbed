//System Includes
#include <map>
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
using std::multimap;
using std::shared_ptr;
using std::make_shared;
using std::chrono::seconds;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_handler( const shared_ptr< Session > session )
{
    string body( 65535, 'x' );
    
    session->close( OK, body, { { "Connection", "close" }, { "Content-Length", "65535" } } );
}

TEST_CASE( "client fails to calculate correct response body length", "[http]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "test" );
    resource->set_method_handler( "GET", get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            auto request = make_shared< Request >( );
            request->set_method( "GET" );
            request->set_port( 1984 );
            request->set_host( "localhost" );
            request->set_path( "/test" );
            
            auto response = Http::sync( request );
            
            REQUIRE( 200 == response->get_status_code( ) );
            Http::fetch( 65535, response );
            
            string actual;
            response->get_body( actual );
            
            string expectation( 65535, 'x' );
            
            REQUIRE( actual.compare( expectation ) == 0 );
            REQUIRE( actual.length( ) == expectation.length( ) );
            
            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}
