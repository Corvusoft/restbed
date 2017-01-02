/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <map>
#include <thread>
#include <string>
#include <memory>
#include <ciso646>
#include <stdexcept>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::string;
using std::multimap;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_handler( const shared_ptr< Session > session )
{
    session->close( 200, "Hello, World!", { { "Content-Length", "13" } } );
}

SCENARIO( "publishing multi path resources", "[resource]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_paths( { "/resources/1", "/resources/one" } );
    resource->set_method_handler( "GET", get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I publish a resource at '/resources/1' and '/resources/one' with a HTTP 'GET' method handler" )
            {
                WHEN( "I perform a HTTP 'PATCH' request to '/resources/1'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resources/1" );
                    request->set_method( "PATCH" );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '501' (Not Implemented) status code" )
                    {
                        REQUIRE( 501 == response->get_status_code( ) );
                        REQUIRE( "Not Implemented" == response->get_status_message( ) );
                    }
                    
                    AND_THEN( "I should see an empty response body" )
                    {
                        REQUIRE( response->get_body( ).empty( ) );
                    }
                    
                    multimap< string, string > headers = response->get_headers( );
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = headers.find( "Connection" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "close" == headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should not see a 'Content-Length' header value" )
                    {
                        REQUIRE( headers.find( "Content-Length" ) == headers.end( ) );
                    }
                }
                
                WHEN( "I perform a HTTP 'PATCH' request to '/resources/one'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resources/one" );
                    request->set_method( "PATCH" );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '501' (Not Implemented) status code" )
                    {
                        REQUIRE( 501 == response->get_status_code( ) );
                        REQUIRE( "Not Implemented" == response->get_status_message( ) );
                    }
                    
                    AND_THEN( "I should see an empty response body" )
                    {
                        REQUIRE( response->get_body( ).empty( ) );
                    }
                    
                    multimap< string, string > headers = response->get_headers( );
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = headers.find( "Connection" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "close" == headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should not see a 'Content-Length' header value" )
                    {
                        REQUIRE( headers.find( "Content-Length" ) == headers.end( ) );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
