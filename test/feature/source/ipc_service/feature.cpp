//System Includes
#include <map>
#include <thread>
#include <string>
#include <memory>
#include <ciso646>
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
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_handler( const shared_ptr< Session > session )
{
    session->close( 200, "Hello, Unix Domain!", { { "Content-Length", "19" } } );
}

SCENARIO( "publishing single path resources", "[resource]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources/ipc" );
    resource->set_method_handler( "GET", get_handler );
    
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
            GIVEN( "I publish a resource at '/resources/ipc' with a HTTP 'GET' method handler" )
            {
                WHEN( "I perform a unix domain HTTP 'GET' request to '/resources/ipc'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_method( "GET" );
                    request->set_protocol( "local" );
                    request->set_path( "/resources/ipc" );
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '200' (OK) status code" )
                    {
                        REQUIRE( 200 == response->get_status_code( ) );
                        REQUIRE( "OK" == response->get_status_message( ) );
                    }
                    
                    multimap< string, string > headers = response->get_headers( );
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = headers.find( "Connection" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "close" == header->second );
                    }
                    
                    AND_THEN( "I should see a 'Content-Length' header value of '19'" )
                    {
                        auto header = headers.find( "Content-Length" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "19" == header->second );
                    }

                    AND_THEN( "I should see a response body of 'Hello, World!'" )
                    {
                        auto actual = Http::fetch( 19, response );
                        Bytes expectation { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'U', 'n', 'i', 'x', ' ', 'D', 'o', 'm', 'a', 'i', 'n', '!' };
                        REQUIRE( actual == expectation );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
