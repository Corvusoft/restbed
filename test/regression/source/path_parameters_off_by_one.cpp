/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <thread>
#include <memory>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::function;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void single_paramater_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    
    if ( "index.html" == request->get_path_parameter( "filename" ) )
    {
        session->close( 200 );
    }
    else
    {
        session->close( 400 );
    }
}

TEST_CASE( "single path parameter with root are off by one", "[request]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/static/{filename: [a-z]*\\.html}" );
    resource->set_method_handler( "GET", single_paramater_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_root( "/ssv/" );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            auto request = make_shared< Request >( );
            request->set_port( 1984 );
            request->set_host( "localhost" );
            request->set_path( "/ssv/static/index.html" );
            
            auto response = Http::sync( request );
            
            REQUIRE( 200 == response->get_status_code( ) );
            
            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}

void multiple_paramaters_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    
    if ( "10" == request->get_path_parameter( "number" ) and "index.html" == request->get_path_parameter( "filename" ) )
    {
        session->close( 200 );
    }
    else
    {
        session->close( 400 );
    }
}

TEST_CASE( "multiple path parameters with root are off by one", "[request]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/static/{number: [0-9]+}/{filename: [a-z]*\\.html}" );
    resource->set_method_handler( "GET", multiple_paramaters_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_root( "/ssv/" );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            auto request = make_shared< Request >( );
            request->set_port( 1984 );
            request->set_host( "localhost" );
            request->set_path( "/ssv/static/10/index.html" );
            
            auto response = Http::sync( request );
            
            REQUIRE( 200 == response->get_status_code( ) );
            
            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}
