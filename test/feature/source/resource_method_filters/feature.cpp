//System Includes
#include <map>
#include <thread>
#include <string>
#include <memory>
#include <utility>
#include <stdexcept>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::string;
using std::multimap;
using std::function;
using std::make_pair;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void xml_method_handler( const shared_ptr< Session > session )
{
    session->close( 1 );
}

void json_method_handler( const shared_ptr< Session > session )
{
    session->close( 2 );
}

SCENARIO( "resource method filters", "[resource]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", { { "Content-Type", "application/xml" } }, xml_method_handler );
    resource->set_method_handler( "GET", { { "Content-Type", "application/json" } }, json_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I publish a resource with 'Content-Type' header filters of 'application/json' and 'application/xml'" )
            {
                WHEN( "I perform a HTTP 'GET' request to '/resource' with header 'Content-Type: application/xml'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resource" );
                    
                    multimap< string, string > headers;
                    headers.insert( make_pair( "Content-Type", "application/xml" ) );
                    request->set_headers( headers );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '1' (No Appropriate Status Message Found) status code" )
                    {
                        REQUIRE( 1 == response->get_status_code( ) );
                        REQUIRE( "No Appropriate Status Message Found" == response->get_status_message( ) );
                    }
                }
                
                WHEN( "I perform a HTTP 'GET' request to '/resource' with header 'Content-Type: application/json'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resource" );
                    
                    multimap< string, string > headers;
                    headers.insert( make_pair( "Content-Type", "application/json" ) );
                    request->set_headers( headers );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '2' (No Appropriate Status Message Found) status code" )
                    {
                        REQUIRE( 2 == response->get_status_code( ) );
                        REQUIRE( "No Appropriate Status Message Found" == response->get_status_message( ) );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
