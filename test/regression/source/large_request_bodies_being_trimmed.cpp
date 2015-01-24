/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 *
 * bug tracker issue #57
 */

//System Includes
#include <memory>
#include <vector>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <gtest/gtest.h>
#include <corvusoft/framework/http>
#include <corvusoft/framework/bytes>

//System Namespaces
using std::vector;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces
using namespace framework;

const char* body = R"(
 { "queues": [
     { "name": "usb 1", "ttl":  60, "behaviour": "basic"       , "consumption": "indirect" },
     { "name": "usb 2", "ttl":  60, "behaviour": "acknowledged", "consumption": "direct"   },
     { "name": "usb 3", "ttl": 120, "behaviour": "basic"       , "consumption": "indirect" },
     { "name": "usb 4", "ttl":  60, "behaviour": "acknowledged", "consumption": "indirect" },
     { "name": "usb 5", "ttl":  30, "behaviour": "acknowledged", "consumption": "indirect" }
   ]
 })";

Response post_handler( const Request& request )
{
    Bytes expectation( body, body + 492 );
    
    Response response;
    response.set_status_code( ( request.get_body( ) == expectation ) ? StatusCode::CREATED : StatusCode::BAD_REQUEST );
    
    return response;
}

TEST( Service, large_request_bodies_being_trimmed )
{
    Resource resource;
    resource.set_path( "test" );
    resource.set_method_handler( "POST", &post_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    settings.set_mode( ASYNCHRONOUS );
    
    auto service = make_shared< Service >( settings );
    service->publish( resource );
    
    service->start( );

    Http::Request request;
    request.method = "POST";
    request.port = 1984;
    request.host = "localhost";
    request.path = "/test";
    request.body = Bytes( body, body + 492 );

    auto response = Http::post( request );
    
    EXPECT_EQ( 201, response.status_code );
    
    service->stop( );
}
