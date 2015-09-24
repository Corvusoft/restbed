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
#pragma warning( disable:4702 )
#include <catch.hpp>
#pragma warning( restore:4702 )

//System Namespaces
using std::thread;
using std::string;
using std::function;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_method_handler( const shared_ptr< Session > session )
{
    const bool CASE_SENSITIVE = false;
    const auto request = session->get_request( );
    
    REQUIRE( "1" == request->get_path_parameter( "id", CASE_SENSITIVE ) );
    REQUIRE( "" == request->get_path_parameter( "ID", CASE_SENSITIVE ) );
    REQUIRE( "abc" == request->get_query_parameter( "q", CASE_SENSITIVE ) );
    REQUIRE( "" == request->get_query_parameter( "Q", CASE_SENSITIVE ) );
    
    session->close( OK, "Hello, World!", { { "Content-Length", "13" } } );
}

SCENARIO( "case sensitive service", "[service]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources/{id: [0-9]}" );
    resource->set_method_handler( "GET", get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_case_insensitive_uris( false );
    settings->set_default_header( "Connection", "close" );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I publish a resource at '/resources/{id: [0-9]}' with a HTTP 'GET' method handler" )
            {
                WHEN( "I perform a HTTP 'GET' request to '/resources/1?q=abc'" )
                {
                    Http::Request request;
                    request.port = 1984;
                    request.host = "localhost";
                    request.path = "/resources/1?q=abc";
                    
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
                
                WHEN( "I perform a HTTP 'GET' request to '/RESOURCES/1?q=abc'" )
                {
                    Http::Request request;
                    request.port = 1984;
                    request.host = "localhost";
                    request.path = "/RESOURCES/1?q=abc";
                    
                    auto response = Http::get( request );
                    
                    THEN( "I should see a '404' (Not Found) status code" )
                    {
                        REQUIRE( 404 == response.status_code );
                    }
                    
                    AND_THEN( "I should see an empty repsonse body" )
                    {
                        REQUIRE( response.body.empty( ) );
                    }
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = response.headers.find( "Connection" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "close" == response.headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should not see a 'Content-Length' header" )
                    {
                        REQUIRE( response.headers.find( "Content-Length" ) == response.headers.end( ) );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
