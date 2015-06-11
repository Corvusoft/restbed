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
    const auto request = session->get_request( );

    REQUIRE( "/uri test" == request->get_path( ) );
    REQUIRE( "@30" == request->get_query_parameter( "ben crowhurst" ) );

    session->close( 200 );
}

TEST_CASE( "encoded uri test", "[request]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "uri test" );
    resource->set_method_handler( "GET", &get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 8989 );
    
    Service service;
    service.publish( resource );
    
    thread service_thread( [ &service, settings ] ( )
    {
        service.start( settings );
    } );

    Http::Request request;
    request.method = "GET";
    request.port = 8989;
    request.host = "localhost";
    request.path = "/uri%20test?ben+crowhurst=%4030";

    auto response = Http::get( request );
    
    REQUIRE( 200 == response.status_code );
    
    service.stop( );
    service_thread.join( );
}
