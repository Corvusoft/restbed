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

//External Includes
#include <catch.hpp>
#include <corvusoft/framework/http>

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
using namespace framework;

void not_found_handler( const shared_ptr< Session >& session )
{
    session->close( 0, "I see nothing!", { { "Content-Length", "14" } } );
}

SCENARIO( "custom resource not found handler", "[resource]" )
{
    GIVEN( "I publish no resources" )
    {
        auto settings = make_shared< Settings >( );
        settings->set_port( 1984 );
        settings->set_default_header( "Connection", "close" );

        shared_ptr< thread > worker = nullptr;

        Service service;
        service.set_not_found_handler( not_found_handler );
        service.set_ready_handler( [ &worker ]( Service& service )
        {
            worker = make_shared< thread >( [ &service ] ( )
            {
                WHEN( "I perform a HTTP 'PUT' request to '/resources/1'" )
                {
                    Http::Request request;
                    request.port = 1984;
                    request.host = "localhost";
                    request.path = "/resources/1";

                    auto response = Http::put( request );

                    THEN( "I should see a '0' (Saw Nothing) status code" )
                    {
                        REQUIRE( 0 == response.status_code );
                    }

                    AND_THEN( "I should see a repsonse body of 'I see nothing!'" )
                    {
                        Bytes expection { 'I', ' ', 's', 'e', 'e', ' ', 'n', 'o', 't', 'h', 'i', 'n', 'g', '!' };
                        REQUIRE( response.body == expection );
                    }

                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = response.headers.find( "Connection" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "close" == response.headers.find( "Connection" )->second );
                    }

                    AND_THEN( "I should see a 'Content-Length' header value of '14'" )
                    {
                        auto header = response.headers.find( "Content-Length" );
                        REQUIRE( header not_eq response.headers.end( ) );
                        REQUIRE( "14" == response.headers.find( "Content-Length" )->second );
                    }
                }

                service.stop( );
            } );
        } );
        service.start( settings );
        worker->join( );
    }
}
