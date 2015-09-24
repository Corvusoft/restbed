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
#pragma warning( disable:4702 )
#include <catch.hpp>
#pragma warning( restore:4702 )

//System Namespaces
using std::thread;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    
    REQUIRE( "/uri test" == request->get_path( ) );
    REQUIRE( "@30" == request->get_query_parameter( "ben crowhurst" ) );
    
    session->close( 200 );
}

TEST_CASE( "encoded uri test", "[request]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "uri test" );
    resource->set_method_handler( "GET", get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 8989 );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            Http::Request request;
            request.method = "GET";
            request.port = 8989;
            request.host = "localhost";
            request.path = "/uri%20test?ben+crowhurst=%4030";
            
            auto response = Http::get( request );
            
            REQUIRE( 200 == response.status_code );
            
            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}
