/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 *
 * bug tracker issue #53
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

TEST( Service, with_space_in_path )
{
    Resource resource;
    resource.set_path( "test queue" );
    resource.set_method_handler( "GET", &get_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    settings.set_root( "queues" );
    settings.set_mode( ASYNCHRONOUS );
    
    auto service = make_shared< Service >( settings );
    service->publish( resource );
    
    service->start( );

    Http::Request request;
    request.method = "GET";
    request.port = 1984;
    request.host = "localhost";
    request.path = "/queues/test queue";

    auto response = Http::get( request );
    
    EXPECT_EQ( 400, response.status_code );
    
    service->stop( );
}

TEST( Service, without_space_in_path )
{
    Resource resource;
    resource.set_path( "testQueue" );
    resource.set_method_handler( "GET", &get_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    settings.set_root( "queues" );
    settings.set_mode( ASYNCHRONOUS );
    
    auto service = make_shared< Service >( settings );
    service->publish( resource );
    
    service->start( );

    Http::Request request;
    request.method = "GET";
    request.port = 1984;
    request.host = "localhost";
    request.path = "/queues/testQueue";

    auto response = Http::get( request );
    
    EXPECT_EQ( 200, response.status_code );
    
    service->stop( );
}
