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

void resource_failed_filter_validation_handler( const shared_ptr< Session >& session )
{
    session->close( -949, "Yikes! Filters Mismatched.", { { "Content-Length", "26" } } );
}

void service_failed_filter_validation_handler( const shared_ptr< Session >& session )
{
    session->close( 500 );
}

void get_method_handler( const shared_ptr< Session >& session )
{
    session->close( OK, "Hello, World!", { { "Content-Length", "32" } } );
}

SCENARIO( "custom resource failed filter validation handler", "[resource]" )
{
    GIVEN( "I publish a resource at '/resources/1' with a HTTP 'GET' method handler" )
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
        service.set_ready_handler( [ &worker ]( Service& service )
        {
            worker = make_shared< thread >( [ &service ] ( )
            {
                WHEN( "I perform an valid HTTP 'GET' request to '/resources/1' with header 'Content-Type: application/csv'" )
                {
                    Http::Request request;
                    request.port = 1984;
                    request.host = "localhost";
                    request.path = "/resources/1";
                    request.headers.insert( make_pair( "Content-Type", "application/csv" ) );

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

                    AND_THEN( "I should see a 'Content-Length' header value of '32'" )
                    {
                        auto header = response.headers.find( "Content-Length" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "32" == response.headers.find( "Content-Length" )->second );
                    }
                }

                WHEN( "I perform an invalid HTTP 'GET' request to '/resources/1' with header 'Content-Type: application/yaml'" )
                {
                    Http::Request request;
                    request.port = 1984;
                    request.host = "localhost";
                    request.path = "/resources/1";
                    request.headers.insert( make_pair( "Content-Type", "application/yaml" ) );

                    auto response = Http::get( request );

                    THEN( "I should see a '-949' (Failed Filter Validation) status code" )
                    {
                        REQUIRE( -949 == response.status_code );
                    }

                    AND_THEN( "I should see a repsonse body of 'Yikes! Filters Mismatched.'" )
                    {
                        Bytes expection { 'Y', 'i', 'k', 'e', 's', '!', ' ', 'F', 'i', 'l', 't', 'e', 'r', 's', ' ', 'M', 'i', 's', 'm', 'a', 't', 'c', 'h', 'e', 'd', '.' };
                        REQUIRE( response.body == expection );
                    }

                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = response.headers.find( "Connection" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "close" == response.headers.find( "Connection" )->second );
                    }

                    AND_THEN( "I should see a 'Content-Length' header value of '26'" )
                    {
                        auto header = response.headers.find( "Content-Length" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "26" == response.headers.find( "Content-Length" )->second );
                    }
                }

                service.stop( );
            } );
        } );
        service.start( settings );
        worker->join( );
    }
}
