//System Includes
#include <regex>
#include <thread>
#include <memory>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::regex;
using std::thread;
using std::function;
using std::shared_ptr;
using std::make_shared;
using std::regex_match;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_method_handler( const shared_ptr< Session > session )
{
    const auto origin = session->get_origin( );
    const auto destination = session->get_destination( );
    const auto pattern = regex{ ".*\\:[0-9]+$" };
    
    if ( regex_match( origin, pattern ) and regex_match( destination, pattern ) )
    {
        session->close( 200 );
    }
    else
    {
        session->close( 400 );
    }
}

TEST_CASE( "malformed origin/destination string", "[session]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/query" );
    resource->set_method_handler( "GET", get_method_handler );
    
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
            request->set_path( "/query" );
            
            auto response = Http::sync( request );
            
            REQUIRE( 200 == response->get_status_code( ) );
            
            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}
