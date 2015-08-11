/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <thread>
#include <string>
#include <memory>
#include <utility>
#include <stdexcept>
#include <functional>

//Project Includes
#include <restbed>
#include "http.hpp"

//External Includes
#include <catch.hpp>

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

void authentication_handler( const shared_ptr< Session >& session, const function< void ( const shared_ptr< Session >& ) >& callback )
{
    auto authorisation = session->get_request( )->get_header( "Authorization" );
    
    if ( authorisation not_eq "Basic Q29ydnVzb2Z0OkdsYXNnb3c=" )
    {
        session->close( UNAUTHORIZED, { { "WWW-Authenticate", "Basic realm=\"restbed\"" } } );
    }
    else
    {
        callback( session );
    }
}

void get_method_handler( const shared_ptr< Session >& session )
{
    session->close( OK, "Password Protected Hello, World!", { { "Content-Length", "32" } } );
}

SCENARIO( "custom service authentication", "[service]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources/1" );
    resource->set_method_handler( "GET", get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_authentication_handler( authentication_handler );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I publish a secure resource at '/resources/1' with a HTTP 'GET' method handler" )
            {
                WHEN( "I perform an authorised HTTP 'GET' request to '/resources/1' with header 'Authorization: Basic Q29ydnVzb2Z0OkdsYXNnb3c='" )
                {
                    Http::Request request;
                    request.port = 1984;
                    request.host = "localhost";
                    request.path = "/resources/1";
                    request.headers.insert( make_pair( "Authorization", "Basic Q29ydnVzb2Z0OkdsYXNnb3c=" ) );
                    
                    auto response = Http::get( request );
                    
                    THEN( "I should see a '200' (OK) status code" )
                    {
                        REQUIRE( 200 == response.status_code );
                    }
                    
                    AND_THEN( "I should see a repsonse body of 'Password Protected Hello, World!'" )
                    {
                        Bytes expection { 'P', 'a', 's', 's', 'w', 'o', 'r', 'd', ' ', 'P', 'r', 'o', 't', 'e', 'c', 't', 'e', 'd', ' ', 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
                        REQUIRE( response.body == expection );
                    }
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = response.headers.find( "Connection" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "close" == response.headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should see a 'Content-Length' header value of '32'" )
                    {
                        auto header = response.headers.find( "Content-Length" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "32" == response.headers.find( "Content-Length" )->second );
                    }
                }
                
                WHEN( "I perform an unauthorised HTTP 'GET' request to '/resources/1' with header 'Authorization: Basic Q29ydndsYXNnb3c='" )
                {
                    Http::Request request;
                    request.port = 1984;
                    request.host = "localhost";
                    request.path = "/resources/1";
                    request.headers.insert( make_pair( "Authorization", "Basic Q29ydndsYXNnb3c=" ) );
                    
                    auto response = Http::get( request );
                    
                    THEN( "I should see a '401' (Unauthorization) status code" )
                    {
                        REQUIRE( 401 == response.status_code );
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
                    
                    AND_THEN( "I should see a 'WWW-Authenticate' header value of 'Basic realm=\"restbed\"'" )
                    {
                        auto header = response.headers.find( "WWW-Authenticate" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "Basic realm=\"restbed\"" == response.headers.find( "WWW-Authenticate" )->second );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
