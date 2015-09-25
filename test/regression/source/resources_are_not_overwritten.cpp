/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <thread>
#include <memory>

//Project Includes
#include <restbed>
#include "http.hpp"

//External Includes
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void json_get_handler( const shared_ptr< Session > session )
{
    session->close( 200, "{ name: \"value\" }", { { "Content-Length", "17" }, { "Content-Type", "application/json" } } );
}

void xml_get_handler( const shared_ptr< Session > session )
{
    session->close( 401, "<name>value</name>", { { "Content-Length", "18" }, { "Content-Type", "application/xml" } } );
}

TEST_CASE( "overwrite existing resource", "[resource]" )
{
    auto initial_resource = make_shared< Resource >( );
    initial_resource->set_path( "TestResource" );
    initial_resource->set_method_handler( "GET", json_get_handler );
    
    auto secondary_resource = make_shared< Resource >( );
    secondary_resource->set_path( "TestResource" );
    secondary_resource->set_method_handler( "GET", xml_get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( initial_resource );
    service.publish( secondary_resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            Http::Request request;
            request.method = "GET";
            request.port = 1984;
            request.host = "localhost";
            request.path = "/TestResource";
            
            auto response = Http::get( request );
            
            REQUIRE( 401 == response.status_code );
            
            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}

TEST_CASE( "add alternative resource", "[resource]" )
{
    auto initial_resource = make_shared< Resource >( );
    initial_resource->set_path( "TestResource" );
    initial_resource->set_method_handler( "GET", { { "Content-Type", "application/json" } }, json_get_handler );
    
    auto secondary_resource = make_shared< Resource >( );
    secondary_resource->set_path( "TestResource" );
    secondary_resource->set_method_handler( "GET", { { "Content-Type", "application/xml" } }, xml_get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( initial_resource );
    service.publish( secondary_resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            Http::Request request;
            request.method = "GET";
            request.port = 1984;
            request.host = "localhost";
            request.path = "/TestResource";
            request.headers = { { "Content-Type", "application/xml" } };
            
            auto response = Http::get( request );
            
            REQUIRE( 401 == response.status_code );
            
            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}
