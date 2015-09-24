/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <thread>
#include <memory>
#include <string>
#include <vector>
#include <functional>

//Project Includes
#include <restbed>
#include "http.hpp"

//External Includes
#pragma warning( disable:4702 )
#include <catch.hpp>
#pragma warning( restore:4702 )

//System Namespaces
using std::thread;
using std::vector;
using std::to_string;
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

void post_handler( const shared_ptr< Session > session )
{
    session->fetch( 492, [ ]( const shared_ptr< Session > session, const Bytes& )
    {
        auto expectation = Bytes( body, body + 492 );
        const auto request = session->get_request( );
        const auto status = ( request->get_body( ) == expectation ) ? 201 : 400;
        
        session->close( status, expectation, { { "Content-Length", "492" } } );
    } );
}

TEST_CASE( "large request bodies being trimmed", "[request]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "test" );
    resource->set_method_handler( "POST", post_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            Http::Request request;
            request.method = "POST";
            request.port = 1984;
            request.host = "localhost";
            request.path = "/test";
            request.body = Bytes( body, body + 492 );
            request.headers = { { "Content-Length", ::to_string( request.body.size( ) ) } };
            
            auto response = Http::post( request );
            
            REQUIRE( 201 == response.status_code );
            
            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}
