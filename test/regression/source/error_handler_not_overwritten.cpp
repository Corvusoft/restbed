/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <memory>
#include <thread>
#include <cstdlib>
#include <stdexcept>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>
#include <corvusoft/framework/http>

//System Namespaces
using std::thread;
using std::exception;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces
using namespace framework;

void faulty_method_handler( const shared_ptr< Session >& )
{
    throw 503;
}

void error_handler( const int, const exception&, const std::shared_ptr< Session >& session )
{
    session->close( 444 );
}

TEST_CASE( "overwrite existing resource", "[resource]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "test" );
    resource->set_method_handler( "GET", &faulty_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_root( "queues" );

    Service service;
    service.publish( resource );
    service.set_error_handler( &error_handler );

    thread service_thread( [ &service, settings ] ( )
    {
        service.start( settings );
    } );

    Http::Request request;
    request.method = "GET";
    request.port = 1984;
    request.host = "localhost";
    request.path = "/queues/test";

    auto response = Http::get( request );

    REQUIRE( 444 == response.status_code );
    
    service.stop( );
    service_thread.join( );
}
