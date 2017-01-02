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
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    const auto path_parameters = request->get_path_parameters( );
    
    REQUIRE( path_parameters.at( "id" ) == "123" );
    REQUIRE( path_parameters.at( "key" ) == "abc" );
    
    const auto query_paramters = request->get_query_parameters( );
    
    REQUIRE( query_paramters.count( "name" ) == 1 );
    REQUIRE( query_paramters.find( "name" )->second == "test item" );
    
    REQUIRE( query_paramters.count( "style" ) == 1 );
    REQUIRE( query_paramters.find( "style" )->second == "true" );
    
    session->close( 200 );
}

TEST_CASE( "request get parameters fails to return data", "[request]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources/{id: .*}/messages/{key: .*}" );
    resource->set_method_handler( "GET", get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
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
            request->set_path( "/resources/123/messages/abc?style=true&name=test%20item" );

            auto response = Http::sync( request );

            REQUIRE( 200 == response->get_status_code( ) );
            
            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}
