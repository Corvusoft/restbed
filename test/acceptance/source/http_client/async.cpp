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
                    
                    auto future = Http::async( request, [ &service ]( const shared_ptr< Request >, const shared_ptr< Response > response )
                    {
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
                    } );
                    
                    auto response = future.get( );
                    
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
                    
                    service.stop( );
                }
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
