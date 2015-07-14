/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <thread>
#include <memory>
#include <functional>

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

void get_handler( const shared_ptr< Session >& session )
{
    session->close( 200 );
}

TEST_CASE( "with space in path", "[resource]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "test queue" );
    resource->set_method_handler( "GET", get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_root( "queues" );
    
    shared_ptr< thread > worker = nullptr;

    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service& service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            Http::Request request;
            request.method = "GET";
            request.port = 1984;
            request.host = "localhost";
            request.path = "/queues/test queue";

            auto response = Http::get( request );
            
            REQUIRE( 400 == response.status_code );

            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}

TEST_CASE( "without space in path", "[resource]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "testQueue" );
    resource->set_method_handler( "GET", get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_root( "queues" );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service& service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            Http::Request request;
            request.method = "GET";
            request.port = 1984;
            request.host = "localhost";
            request.path = "/queues/testQueue";

            auto response = Http::get( request );
            
            REQUIRE( 200 == response.status_code );

            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}
