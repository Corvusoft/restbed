/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 *
 * bug tracker issue #98
 */

//System Includes
#include <memory>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>
#include <corvusoft/framework/http>

//System Namespaces
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces
using namespace framework;

TEST_CASE( "resource instance destroyed with bound method functors", "[resource]" )
{
    auto resource = make_shared< Resource >( );

    Settings settings;
    settings.set_port( 1984 );
    settings.set_mode( ASYNCHRONOUS );

    auto service = make_shared< Service >( settings );
    service->publish( *resource );

    resource.reset( );

    service->start( );

    Http::Request request;
    request.method = "GET";
    request.port = 1984;
    request.host = "localhost";
    request.path = "/";

    auto response = Http::get( request );

    REQUIRE( 405 == response.status_code );

    service->stop( );
}
