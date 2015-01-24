/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 *
 * bug tracker issue #2
 */

//System Includes
#include <memory>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <gtest/gtest.h>
#include <corvusoft/framework/http>

//System Namespaces
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces
using namespace framework;

Response get_handler( const Request& )
{
    Response response;
    response.set_status_code( StatusCode::OK );
    
    return response;
}

TEST( Service, mismatched_resource_path_of_equal_path_segments )
{
    Resource resource;
    resource.set_path( "test" );
    resource.set_method_handler( "GET", &get_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    settings.set_mode( ASYNCHRONOUS );
    
    auto service = make_shared< Service >( settings );
    service->publish( resource );
    
    service->start( );

    Http::Request request;
    request.method = "GET";
    request.port = 1984;
    request.host = "localhost";
    request.path = "/tests";

    auto response = Http::get( request );
    
    EXPECT_EQ( 404, response.status_code );
    
    service->stop( );
}

TEST( Service, mismatched_resource_path_of_unequal_path_segments )
{
    Resource resource;
    resource.set_path( "test" );
    resource.set_method_handler( "GET", &get_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    settings.set_mode( ASYNCHRONOUS );
    
    auto service = make_shared< Service >( settings );
    service->publish( resource );
    
    service->start( );

    Http::Request request;
    request.method = "GET";
    request.port = 1984;
    request.host = "localhost";
    request.path = "/event/test";

    auto response = Http::get( request );
    
    EXPECT_EQ( 404, response.status_code );
    
    service->stop( );
}

TEST( Service, matched_resource_path )
{
    Resource resource;
    resource.set_path( "test" );
    resource.set_method_handler( "GET", &get_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    settings.set_mode( ASYNCHRONOUS );
    
    auto service = make_shared< Service >( settings );
    service->publish( resource );
    
    service->start( );

    Http::Request request;
    request.method = "GET";
    request.port = 1984;
    request.host = "localhost";
    request.path = "/test";

    auto response = Http::get( request );
    
    EXPECT_EQ( 200, response.status_code );
    
    service->stop( );
}
