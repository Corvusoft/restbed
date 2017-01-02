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
using std::exception;
using std::make_pair;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void resource_error_handler( const int, const exception&, const shared_ptr< Session > session )
{
    session->close( 22, "overridden service handler!", { { "Content-Length", "27" } } );
}

void service_error_handler( const int, const exception&, const shared_ptr< Session > session )
{
    session->close( 0, "I see nothing!", { { "Content-Length", "14" } } );
}

void faulty_method_handler( const shared_ptr< Session > )
{
    throw SERVICE_UNAVAILABLE;
}

SCENARIO( "custom service error handler", "[service]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources/1" );
    resource->set_method_handler( "GET", faulty_method_handler );
    resource->set_error_handler( resource_error_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_error_handler( service_error_handler );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I publish a faulty resource and set a resource error handler" )
            {
                WHEN( "I perform a HTTP 'GET' request to '/resources/1'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resources/1" );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '0' (No Appropriate Status Message Found) status code" )
                    {
                        REQUIRE( 22 == response->get_status_code( ) );
                        REQUIRE( "No Appropriate Status Message Found" == response->get_status_message( ) );
                    }
                    
                    AND_THEN( "I should see a response body of 'I see nothing!'" )
                    {
                        auto actual = Http::fetch( 27, response );
                        Bytes expectation { 'o', 'v', 'e', 'r', 'r', 'i', 'd', 'd', 'e', 'n', ' ', 's', 'e', 'r', 'v', 'i', 'c', 'e', ' ', 'h', 'a', 'n', 'd', 'l', 'e', 'r', '!' };
                        REQUIRE( actual == expectation );
                    }
                    
                    multimap< string, string > headers = response->get_headers( );
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = headers.find( "Connection" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "close" == headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should see a 'Content-Length' header value of '27'" )
                    {
                        auto header = headers.find( "Content-Length" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "27" == headers.find( "Content-Length" )->second );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
