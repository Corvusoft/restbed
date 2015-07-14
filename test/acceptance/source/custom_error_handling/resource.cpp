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
using std::exception;
using std::make_pair;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void resource_error_handler( const int, const exception&, const shared_ptr< Session >& session )
{
    session->close( 22, "overridden service handler!", { { "Content-Length", "27" } } );
}

void service_error_handler( const int, const exception&, const shared_ptr< Session >& session )
{
    session->close( 0, "I see nothing!", { { "Content-Length", "14" } } );
}

void faulty_method_handler( const shared_ptr< Session >& )
{
    throw SERVICE_UNAVAILABLE;
}

SCENARIO( "custom service error handler", "[service]" )
{
    GIVEN( "I publish no resources" )
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
        service.set_ready_handler( [ &worker ]( Service& service )
        {
            worker = make_shared< thread >( [ &service ] ( )
            {
                WHEN( "I perform a HTTP 'GET' request to '/resources/1'" )
                {
                    Http::Request request;
                    request.port = 1984;
                    request.host = "localhost";
                    request.path = "/resources/1";

                    auto response = Http::get( request );

                    THEN( "I should see a '0' (Custom Error) status code" )
                    {
                        REQUIRE( 22 == response.status_code );
                    }

                    AND_THEN( "I should see a repsonse body of 'I see nothing!'" )
                    {
                        Bytes expection { 'o', 'v', 'e', 'r', 'r', 'i', 'd', 'd', 'e', 'n', ' ', 's', 'e', 'r', 'v', 'i', 'c', 'e', ' ', 'h', 'a', 'n', 'd', 'l', 'e', 'r', '!' };
                        REQUIRE( response.body == expection );
                    }

                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = response.headers.find( "Connection" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "close" == response.headers.find( "Connection" )->second );
                    }

                    AND_THEN( "I should see a 'Content-Length' header value of '27'" )
                    {
                        auto header = response.headers.find( "Content-Length" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "27" == response.headers.find( "Content-Length" )->second );
                    }
                }

                service.stop( );
            } );
        } );
        service.start( settings );
        worker->join( );
    }
}
