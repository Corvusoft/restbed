/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <thread>
#include <string>
#include <memory>
#include <ciso646>
#include <utility>
#include <stdexcept>
#include <functional>

//Project Includes
#include <restbed>
#include "http.hpp"
#include "content_type_rule.hpp"
#include "content_length_rule.hpp"

//External Includes
#pragma warning( disable:4702 )
#include <catch.hpp>
#pragma warning( restore:4702 )

//System Namespaces
using std::thread;
using std::string;
using std::function;
using std::make_pair;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_method_handler( const shared_ptr< Session > session )
{
    session->close( OK, "Hello, World!", { { "Content-Length", "13" } } );
}

SCENARIO( "resource rules engine", "[resource]" )
{
    const auto content_type = make_shared< ContentTypeRule >( );
    
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources" );
    resource->set_method_handler( "POST", get_method_handler );
    resource->add_rule( content_type );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    shared_ptr< thread > worker = nullptr;
    const auto content_length = make_shared< ContentLengthRule >( );
    
    Service service;
    service.publish( resource );
    service.add_rule( content_length );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I publish a resource at '/resources' with a HTTP 'POST' method handler" )
            {
                WHEN( "I perform an HTTP 'POST' request to '/resources' with headers 'Content-Type: application/csv, Content-Length: 0'" )
                {
                    Http::Request request;
                    request.port = 1984;
                    request.host = "localhost";
                    request.path = "/resources";
                    request.headers.insert( make_pair( "Content-Length", "0" ) );
                    request.headers.insert( make_pair( "Content-Type", "application/csv" ) );
                    
                    auto response = Http::post( request );
                    
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
                
                WHEN( "I perform an HTTP 'POST' request to '/resources' with headers 'Content-Type: application/json, Content-Length: 0'" )
                {
                    Http::Request request;
                    request.port = 1984;
                    request.host = "localhost";
                    request.path = "/resources";
                    request.headers.insert( make_pair( "Content-Length", "0" ) );
                    request.headers.insert( make_pair( "Content-Type", "application/json" ) );
                    
                    auto response = Http::post( request );
                    
                    THEN( "I should see a '415' (Unsupported Media Type) status code" )
                    {
                        REQUIRE( 415 == response.status_code );
                    }
                    
                    AND_THEN( "I should see a repsonse body of 'Unsupported Media Type, must be 'application/csv'.'" )
                    {
                        string body( response.body.begin( ), response.body.end( ) );
                        REQUIRE( body == "Unsupported Media Type, must be 'application/csv'." );
                    }
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = response.headers.find( "Connection" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "close" == response.headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should see a 'Content-Type' header value of 'text/plain'" )
                    {
                        auto header = response.headers.find( "Content-Type" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "text/plain" == response.headers.find( "Content-Type" )->second );
                    }
                    
                    AND_THEN( "I should see a 'Content-Length' header value of '50'" )
                    {
                        auto header = response.headers.find( "Content-Length" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "50" == response.headers.find( "Content-Length" )->second );
                    }
                }
                
                WHEN( "I perform an HTTP 'POST' request to '/resources' with headers 'Content-Type: application/csv, Content-Length: 4' and body 'data'" )
                {
                    Http::Request request;
                    request.port = 1984;
                    request.host = "localhost";
                    request.path = "/resources";
                    request.body = { 'd', 'a', 't', 'a' };
                    request.headers.insert( make_pair( "Content-Length", "4" ) );
                    request.headers.insert( make_pair( "Content-Type", "application/csv" ) );
                    
                    auto response = Http::post( request );
                    
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
                
                WHEN( "I perform an HTTP 'POST' request to '/resources' with headers 'Content-Type: application/csv' and body 'data'" )
                {
                    Http::Request request;
                    request.port = 1984;
                    request.host = "localhost";
                    request.path = "/resources";
                    request.body = { 'd', 'a', 't', 'a' };
                    request.headers.insert( make_pair( "Content-Type", "application/csv" ) );
                    
                    auto response = Http::post( request );
                    
                    THEN( "I should see a '411' (Length Required) status code" )
                    {
                        REQUIRE( 411 == response.status_code );
                    }
                    
                    AND_THEN( "I should see a repsonse body of 'Length Required.'" )
                    {
                        string body( response.body.begin( ), response.body.end( ) );
                        REQUIRE( body == "Length Required." );
                    }
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = response.headers.find( "Connection" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "close" == response.headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should see a 'Content-Type' header value of 'text/plain'" )
                    {
                        auto header = response.headers.find( "Content-Type" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "text/plain" == response.headers.find( "Content-Type" )->second );
                    }
                    
                    AND_THEN( "I should see a 'Content-Length' header value of '16'" )
                    {
                        auto header = response.headers.find( "Content-Length" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "16" == response.headers.find( "Content-Length" )->second );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
