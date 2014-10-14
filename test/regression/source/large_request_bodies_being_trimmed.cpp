/*
 * Copyright (c) 2013, 2014 Corvusoft
 *
 * bug tracker issue #57
 */

//System Includes
#include <memory>
#include <vector>
#include <functional>

//Project Includes
#include <restbed>
#include "helpers/http.h"

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::vector;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

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
    vector< unsigned char > expectation( body, body + 492 );
    
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
    
    auto response = Http::post( "http://localhost:1984/test", body );
    
    EXPECT_EQ( "201", response[ "Status Code" ] );
    
    service->stop( );
}
