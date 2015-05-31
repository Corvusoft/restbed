/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 *
 * bug tracker issue #98
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

TEST_CASE( "resource instance destroyed with bound method functors", "[resource]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/" );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );

    Service service;
    service.publish( resource );

    resource.reset( );

    thread service_thread( [ &service, settings ] ( )
    {
        service.start( settings );
    } );

    Http::Request request;
    request.method = "GET";
    request.port = 1984;
    request.host = "localhost";
    request.path = "/";

    auto response = Http::get( request );

    REQUIRE( 501 == response.status_code );

    service.stop( );
    service_thread.join( );
}
