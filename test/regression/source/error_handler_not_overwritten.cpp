//System Includes
#include <memory>
#include <thread>
#include <cstdlib>
#include <stdexcept>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::exception;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void faulty_method_handler( const shared_ptr< Session > )
{
    throw 503;
}

void error_handler( const int, const exception&, const std::shared_ptr< Session > session )
{
    session->close( 444 );
}

TEST_CASE( "overwrite existing resource", "[resource]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "test" );
    resource->set_method_handler( "GET", faulty_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_root( "queues" );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_error_handler( error_handler );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {            
            auto request = make_shared< Request >( );
            request->set_port( 1984 );
            request->set_host( "localhost" );
            request->set_path( "/queues/test" );
            
            auto response = Http::sync( request );
            
            REQUIRE( 444 == response->get_status_code( ) );
            
            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}
