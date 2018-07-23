//System Includes
#include <map>
#include <thread>
#include <string>
#include <memory>
#include <ciso646>
#include <utility>
#include <algorithm>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::string;
using std::multimap;
using std::make_pair;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    
    multimap< string, string > expectation;
    expectation.insert( make_pair( "echo", "false" ) );
    expectation.insert( make_pair( "echo", "true" ) );
    
    const auto actual = request->get_query_parameters( "echo" );
    
    if ( actual not_eq expectation )
    {
        session->close( 500 );
    }
    else
    {
        session->close( 200 );
    }
}

TEST_CASE( "fails to parse identical query parameters", "[service]" )
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
            request->set_port( 1984 );
            request->set_host( "localhost" );
            request->set_path( "/test?echo=false&echo=true" );

            auto response = Http::sync( request );
            
            REQUIRE( 200 == response->get_status_code( ) );
            
            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}
