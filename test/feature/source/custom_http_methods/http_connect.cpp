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

void invoke_handler( const shared_ptr< Session > session )
{
    session->close( 200, "Hello, World!", { { "Content-Length", "13" } } );
}

SCENARIO( "publishing custom HTTP methods", "[resource]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources/1" );
    resource->set_method_handler( "INVOKE", invoke_handler );
    
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
            GIVEN( "I publish a resource at '/resources/1' with a HTTP 'INVOKE' method handler" )
            {
                WHEN( "I perform a HTTP 'CONNECT' request to '/resources/1'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_method( "CONNECT" );
                    request->set_path( "/resources/1" );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '501' (Not Implemented) status code" )
                    {
                        REQUIRE( 501 == response->get_status_code( ) );
                        REQUIRE( "Not Implemented" == response->get_status_message( ) );
                    }
                    
                    AND_THEN( "I should see an empty response body" )
                    {
                        REQUIRE( response->get_body( ).empty( ) );
                    }
                    
                    multimap< string, string > headers = response->get_headers( );
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = headers.find( "Connection" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "close" == headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should not see a 'Content-Length' header value" )
                    {
                        REQUIRE( headers.find( "Content-Length" ) == headers.end( ) );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
