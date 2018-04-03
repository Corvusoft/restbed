//System Includes
#include <thread>
#include <memory>
#include <clocale>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::function;
using std::setlocale;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    
    if ( request->get_version( ) == 1.1 )
    {
        return session->close( 200 );
    }
    
    session->close( 500 );
}

TEST_CASE( "locale which uses comma for numeric delimiter causes incorrect version format", "[service]" )
{
    std::setlocale( LC_NUMERIC, "de_DE" );
    
    auto resource = make_shared< Resource >( );
    resource->set_path( "/sensor" );
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
            request->set_port( 1984 );
            request->set_host( "localhost" );
            request->set_path( "/sensor" );
            
            auto response = Http::sync( request );
            
            REQUIRE( 200 == response->get_status_code( ) );
            
            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}
