//System Includes
#include <map>
#include <thread>
#include <string>
#include <memory>
#include <ciso646>
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
using std::function;
using std::multimap;
using std::exception;
using std::make_pair;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void negative_handler( const shared_ptr< Session > session )
{
    session->close( -342 );
}

void positive_handler( const shared_ptr< Session > session )
{
    session->close( 9834 );
}

SCENARIO( "custom positive response status", "[settings]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", positive_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    auto status_messages = settings->get_status_messages( );
    status_messages[ 9834 ] = "Positive Status Code Message";
    settings->set_status_messages( status_messages );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I publish a resources with a custom status of '9834' (Positive Status Code Message)" )
            {
                WHEN( "I perform a HTTP 'GET' request to '/resource'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resource" );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '9834' (Positive Status Code Message) status code" )
                    {
                        REQUIRE( 9834 == response->get_status_code( ) );
                        REQUIRE( "Positive Status Code Message" == response->get_status_message( ) );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}

SCENARIO( "custom negative response status", "[settings]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", negative_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    auto status_messages = settings->get_status_messages( );
    status_messages[ -342 ] = "Negative Status Code Message";
    settings->set_status_messages( status_messages );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I publish a resources with a custom status of '-342' (Negative Status Code Message)" )
            {
                WHEN( "I perform a HTTP 'GET' request to '/resource'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resource" );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '-342' (Negative Status Code Message) status code" )
                    {
                        REQUIRE( -342 == response->get_status_code( ) );
                        REQUIRE( "Negative Status Code Message" == response->get_status_message( ) );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
