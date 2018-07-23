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
    const auto request = session->get_request( );
    
    int id = request->get_query_parameter( "id", 0 );
    REQUIRE( 100 == id );
    
    REQUIRE( "events" == request->get_query_parameter( "name" ) );
    
    session->close( 204 );
}

SCENARIO( "request query parameters", "[resource]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources/1" );
    resource->set_method_handler( "GET", get_handler );
    resource->set_default_header( "Connection", "close" );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I publish a resource at '/resources/1' with a HTTP 'GET' method handler" )
            {
                WHEN( "I perform a HTTP 'GET' request to '/resources/1?id=100&name=events'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resources/1?id=100&name=events" );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '204' (No Content) status code" )
                    {
                        REQUIRE( 204 == response->get_status_code( ) );
                        REQUIRE( "No Content" == response->get_status_message( ) );
                    }
                    
                    AND_THEN( "I should see an empty response body" )
                    {
                        REQUIRE( response->get_body( ).empty( ) );
                    }
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto headers = response->get_headers( );
                        auto header = headers.find( "Connection" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "close" == headers.find( "Connection" )->second );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
