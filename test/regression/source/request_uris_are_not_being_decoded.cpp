/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 *
 * bug tracker issue #9
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

Response get_handler( const Request& request )
{
    REQUIRE( "/uri test" == request.get_path( ) );
    REQUIRE( "@30" == request.get_query_parameter( "ben crowhurst" ) );
    
    Response response;
    response.set_status_code( StatusCode::OK );
    
    return response;
}

TEST_CASE( "encoded uri test", "[service]" )
{
    Resource resource;
    resource.set_path( "uri test" );
    resource.set_method_handler( "GET", &get_handler );
    
    Settings settings;
    settings.set_port( 8989 );
    settings.set_mode( ASYNCHRONOUS );
    
    auto service = make_shared< Service >( settings );
    service->publish( resource );
    
    service->start( );

    Http::Request request;
    request.method = "GET";
    request.port = 8989;
    request.host = "localhost";
    request.path = "/uri%20test?ben+crowhurst=%4030";

    auto response = Http::get( request );
    
    REQUIRE( 200 == response.status_code );
    
    service->stop( );
}
