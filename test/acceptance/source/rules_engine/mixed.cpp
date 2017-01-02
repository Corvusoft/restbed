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
#include "content_type_rule.hpp"
#include "content_length_rule.hpp"

//External Includes
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::string;
using std::multimap;
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
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resources" );
                    request->set_method( "POST" );
                    
                    multimap< string, string > headers;
                    headers.insert( make_pair( "Content-Length", "0" ) );
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
                    
                    AND_THEN( "I should see a 'Content-Length' header value of '13'" )
                    {
                        auto header = headers.find( "Content-Length" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "13" == headers.find( "Content-Length" )->second );
                    }
                }
                
                WHEN( "I perform an HTTP 'POST' request to '/resources' with headers 'Content-Type: application/json, Content-Length: 0'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resources" );
                    request->set_method( "POST" );
                    
                    multimap< string, string > headers;
                    headers.insert( make_pair( "Content-Length", "0" ) );
                    headers.insert( make_pair( "Content-Type", "application/json" ) );
                    request->set_headers( headers );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '415' (Unsupported Media Type) status code" )
                    {
                        REQUIRE( 415 == response->get_status_code( ) );
                        REQUIRE( "Unsupported Media Type" == response->get_status_message( ) );
                    }
                    
                    AND_THEN( "I should see a response body of 'Unsupported Media Type, must be 'application/csv'.'" )
                    {
                        auto actual = Http::fetch( 50, response );
                        string body( actual.begin( ), actual.end( ) );
                        REQUIRE( body == "Unsupported Media Type, must be 'application/csv'." );
                    }
                    
                    headers = response->get_headers( );
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = headers.find( "Connection" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "close" == headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should see a 'Content-Type' header value of 'text/plain'" )
                    {
                        auto header = headers.find( "Content-Type" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "text/plain" == headers.find( "Content-Type" )->second );
                    }
                    
                    AND_THEN( "I should see a 'Content-Length' header value of '50'" )
                    {
                        auto header = headers.find( "Content-Length" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "50" == headers.find( "Content-Length" )->second );
                    }
                }
                
                WHEN( "I perform an HTTP 'POST' request to '/resources' with headers 'Content-Type: application/csv, Content-Length: 4' and body 'data'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resources" );
                    request->set_body( Bytes( { 'd', 'a', 't', 'a' } ) );
                    request->set_method( "POST" );
                    
                    multimap< string, string > headers;
                    headers.insert( make_pair( "Content-Length", "4" ) );
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
                    
                    AND_THEN( "I should see a 'Content-Length' header value of '13'" )
                    {
                        auto header = headers.find( "Content-Length" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "13" == headers.find( "Content-Length" )->second );
                    }
                }
                
                WHEN( "I perform an HTTP 'POST' request to '/resources' with headers 'Content-Type: application/csv' and body 'data'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resources" );
                    request->set_body( Bytes( { 'd', 'a', 't', 'a' } ) );
                    request->set_method( "POST" );
                    
                    multimap< string, string > headers;
                    headers.insert( make_pair( "Content-Type", "application/csv" ) );
                    request->set_headers( headers );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '411' (Length Required) status code" )
                    {
                        REQUIRE( 411 == response->get_status_code( ) );
                        REQUIRE( "Length Required" == response->get_status_message( ) );
                    }
                    
                    AND_THEN( "I should see a response body of 'Length Required.'" )
                    {
                        auto actual = Http::fetch( 16, response );
                        Bytes expectation { 'L', 'e', 'n', 'g', 't', 'h', ' ', 'R', 'e', 'q', 'u', 'i', 'r', 'e', 'd', '.' };
                        REQUIRE( actual == expectation );
                    }
                    
                    headers = response->get_headers( );
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = headers.find( "Connection" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "close" == headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should see a 'Content-Type' header value of 'text/plain'" )
                    {
                        auto header = headers.find( "Content-Type" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "text/plain" == headers.find( "Content-Type" )->second );
                    }
                    
                    AND_THEN( "I should see a 'Content-Length' header value of '16'" )
                    {
                        auto header = headers.find( "Content-Length" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "16" == headers.find( "Content-Length" )->second );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
