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
using std::stoi;
using std::thread;
using std::string;
using std::multimap;
using std::to_string;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_handler( const shared_ptr< Session > session )
{
    session->close( 200, "Hello, World!", { { "Content-Length", "13" }, { "Connection", "close" } } );
}

SCENARIO( "establish connection to reachable server", "[client]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
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
            GIVEN( "I have started a service" )
            {
                WHEN( "I perform a HTTP 'GET' request" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_method( "GET" );
                    request->set_path( "/resource" );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '200' (OK) status code" )
                    {
                        REQUIRE( 200 == response->get_status_code( ) );
                    }
                    
                    AND_THEN( "I should see a response body of 'Hello, World!'" )
                    {
                        auto actual = Http::fetch( 13, response );
                        Bytes expectation { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
                        REQUIRE( actual == expectation );
                    }
                    
                    multimap< string, string > headers = response->get_headers( );
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = headers.find( "Connection" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "close" == headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should see a 'Content-Length' header value of '13'" )
                    {
                        auto header = headers.find( "Content-Length" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "13" == headers.find( "Content-Length" )->second );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}

SCENARIO( "establish connection to unreachable server", "[client]" )
{
    GIVEN( "I have not started a service" )
    {
        WHEN( "I perform a HTTP 'GET' request" )
        {
            auto request = make_shared< Request >( );
            request->set_port( 1984 );
            request->set_protocol( "HTTP" );
            request->set_version( 1.1 );
            request->set_host( "localhost" );
            request->set_method( "GET" );
            request->set_path( "/resource" );
            
            auto response = Http::sync( request );
            
            THEN( "I should see a '0' (Error) status code" )
            {
                REQUIRE( 0 == response->get_status_code( ) );
                REQUIRE( "Error" == response->get_status_message( ) );
            }
            
            AND_THEN( "I should see a 'HTTP' response protocol" )
            {
                REQUIRE( "HTTP" == response->get_protocol( ) );
            }
            
            AND_THEN( "I should see a '1.1' response version" )
            {
                REQUIRE( 1.1 == response->get_version( ) );
            }
            
            multimap< string, string > headers = response->get_headers( );
            
            AND_THEN( "I should see a 'Content-Type' header value of 'text/plain; utf-8'" )
            {
                auto header = headers.find( "Content-Type" );
                REQUIRE( header not_eq headers.end( ) );
                REQUIRE( "text/plain; utf-8" == headers.find( "Content-Type" )->second );
            }
            
            AND_THEN( "I should see a 'Content-Length' header value greater than zero" )
            {
                auto header = headers.find( "Content-Length" );
                REQUIRE( header not_eq headers.end( ) );
                REQUIRE( stoi( headers.find( "Content-Length" )->second ) > 0 );
            }
            
            AND_THEN( "I should see a response body detailing the error" )
            {
                REQUIRE( response->get_body( ).size( ) > 0 );
            }
        }
    }
}
