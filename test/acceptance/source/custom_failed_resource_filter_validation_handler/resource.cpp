/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <map>
#include <thread>
#include <string>
#include <memory>
#include <ciso646>
#include <utility>
#include <stdexcept>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::string;
using std::function;
using std::multimap;
using std::make_pair;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void resource_failed_filter_validation_handler( const shared_ptr< Session > session )
{
    session->close( -949, "Yikes! Filters Mismatched.", { { "Content-Length", "26" } } );
}

void service_failed_filter_validation_handler( const shared_ptr< Session > session )
{
    session->close( 500 );
}

void get_method_handler( const shared_ptr< Session > session )
{
    session->close( OK, "Hello, World!", { { "Content-Length", "32" } } );
}

SCENARIO( "custom resource failed filter validation handler", "[resource]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources/1" );
    resource->set_method_handler( "GET", { { "Content-Type", "application/csv" } }, get_method_handler );
    resource->set_failed_filter_validation_handler( resource_failed_filter_validation_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_failed_filter_validation_handler( service_failed_filter_validation_handler );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I publish a resource at '/resources/1' with a HTTP 'GET' method handler" )
            {
                WHEN( "I perform an valid HTTP 'GET' request to '/resources/1' with header 'Content-Type: application/csv'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resources/1" );
                    
                    multimap< string, string > headers;
                    headers.insert( make_pair( "Content-Type", "application/csv" ) );
                    request->set_headers( headers );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '200' (OK) status code" )
                    {
                        REQUIRE( 200 == response->get_status_code( ) );
                        REQUIRE( "OK" == response->get_status_message( ) );
                    }
                    
                    AND_THEN( "I should see a response body of 'Hello, World!'" )
                    {
                        auto actual = Http::fetch( 13, response );
                        Bytes expectation { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
                        REQUIRE( actual == expectation );
                    }
                    
                    headers = response->get_headers( );
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = headers.find( "Connection" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "close" == headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should see a 'Content-Length' header value of '32'" )
                    {
                        auto header = headers.find( "Content-Length" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "32" == headers.find( "Content-Length" )->second );
                    }
                }
                
                WHEN( "I perform an invalid HTTP 'GET' request to '/resources/1' with header 'Content-Type: application/yaml'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resources/1" );
                    
                    multimap< string, string > headers;
                    headers.insert( make_pair( "Content-Type", "application/yaml" ) );
                    request->set_headers( headers );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '-949' (No Appropriate Status Message Found) status code" )
                    {
                        REQUIRE( -949 == response->get_status_code( ) );
                        REQUIRE( "No Appropriate Status Message Found" == response->get_status_message( ) );
                    }
                    
                    AND_THEN( "I should see a response body of 'Yikes! Filters Mismatched.'" )
                    {
                        auto actual = Http::fetch( 26, response );
                        Bytes expectation { 'Y', 'i', 'k', 'e', 's', '!', ' ', 'F', 'i', 'l', 't', 'e', 'r', 's', ' ', 'M', 'i', 's', 'm', 'a', 't', 'c', 'h', 'e', 'd', '.' };
                        REQUIRE( actual == expectation );
                    }
                    
                    headers = response->get_headers( );
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = headers.find( "Connection" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "close" == headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should see a 'Content-Length' header value of '26'" )
                    {
                        auto header = headers.find( "Content-Length" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "26" == headers.find( "Content-Length" )->second );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
