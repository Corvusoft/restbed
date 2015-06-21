/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <thread>
#include <memory>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>
#include <corvusoft/framework/http>

//System Namespaces
using std::thread;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces
using namespace framework;

void get_handler( const shared_ptr< Session >& session )
{
    session->close( 200 );
}

TEST_CASE( "content length present on empty response body", "[response]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "test" );
    resource->set_method_handler( "GET", get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    Service service;
    service.publish( resource );
    
    thread service_thread( [ &service, settings ] ( )
    {
        service.start( settings );
    } );

    Http::Request request;
    request.method = "GET";
    request.port = 1984;
    request.host = "localhost";
    request.path = "/test";
    
    auto response = Http::get( request );

    REQUIRE( 200 == response.status_code );
    REQUIRE( response.headers.end( ) == response.headers.find( "Content-Length" ) );

    service.stop( );
    service_thread.join( );
}
