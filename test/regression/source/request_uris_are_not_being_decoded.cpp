//System Includes
#include <thread>
#include <memory>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    
    REQUIRE( "/uri test" == request->get_path( ) );
    REQUIRE( "@30" == request->get_query_parameter( "ben crowhurst" ) );
    
    session->close( 200 );
}

TEST_CASE( "encoded uri test", "[request]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "uri test" );
    resource->set_method_handler( "GET", get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 8989 );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {            
            auto request = make_shared< Request >( );
            request->set_port( 8989 );
            request->set_host( "localhost" );
            request->set_path( "/uri%20test?ben+crowhurst=%4030" );

            auto response = Http::sync( request );
            
            REQUIRE( 200 == response->get_status_code( ) );
            
            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}
