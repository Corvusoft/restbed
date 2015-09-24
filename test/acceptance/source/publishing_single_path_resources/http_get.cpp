/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <thread>
#include <string>
#include <memory>
#include <ciso646>
#include <stdexcept>
#include <functional>

//Project Includes
#include <restbed>
#include "http.hpp"

//External Includes
#pragma warning disable 4702
#include <catch.hpp>
#pragma warning restore 4702

//System Namespaces
using std::thread;
using std::string;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_handler( const shared_ptr< Session > session )
{
    session->close( 200, "Hello, World!", { { "Content-Length", "13" } } );
}

SCENARIO( "publishing single path resources", "[resource]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources/1" );
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
            GIVEN( "I publish a resource at '/resources/1' with a HTTP 'GET' method handler" )
            {
                WHEN( "I perform a HTTP 'GET' request to '/resources/1'" )
                {
                    Http::Request request;
                    request.port = 1984;
                    request.host = "localhost";
                    request.path = "/resources/1";
                    
                    auto response = Http::get( request );
                    
                    THEN( "I should see a '200' (OK) status code" )
                    {
                        REQUIRE( 200 == response.status_code );
                    }
                    
                    AND_THEN( "I should see a repsonse body of 'Hello, World!'" )
                    {
                        Bytes expection { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
                        REQUIRE( response.body == expection );
                    }
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = response.headers.find( "Connection" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "close" == response.headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should see a 'Content-Length' header value of '13'" )
                    {
                        auto header = response.headers.find( "Content-Length" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "13" == response.headers.find( "Content-Length" )->second );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
