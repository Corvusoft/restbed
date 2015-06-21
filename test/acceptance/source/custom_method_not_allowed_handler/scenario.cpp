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

void method_not_allowed_handler( const shared_ptr< Session >& session )
{
    session->close( -400, "Banned Method", { { "Content-Length", "13" } } );
}

void jack_of_all_trades_method_handler( const shared_ptr< Session >& session )
{
    session->close( OK );
}

SCENARIO( "custom resource method not allowed handler", "[resource]" )
{
    GIVEN( "I publish two resources with differing HTTP methods" )
    {
        auto resource_one = make_shared< Resource >( );
        resource_one->set_path( "/resources/1" );
        resource_one->set_method_handler( "GET", jack_of_all_trades_method_handler );

        auto resource_two = make_shared< Resource >( );
        resource_two->set_path( "/resources/2" );
        resource_two->set_method_handler( "PUT", jack_of_all_trades_method_handler );

        auto settings = make_shared< Settings >( );
        settings->set_port( 1984 );
        settings->set_default_header( "Connection", "close" );

        Service service;
        service.publish( resource_one );
        service.publish( resource_two );
        service.set_method_not_allowed_handler( method_not_allowed_handler );

        thread service_thread( [ &service, settings ] ( )
        {
            service.start( settings );
        } );

        WHEN( "I perform a HTTP 'PUT' request to '/resources/1'" )
        {
            Http::Request request;
            request.port = 1984;
            request.host = "localhost";
            request.path = "/resources/1";

            auto response = Http::put( request );

            THEN( "I should see a '-400' (Banned Method) status code" )
            {
                REQUIRE( -400 == response.status_code );
            }

            AND_THEN( "I should see a repsonse body of 'Banned Method'" )
            {
                Bytes expection { 'B', 'a', 'n', 'n', 'e', 'd', ' ', 'M', 'e', 't', 'h', 'o', 'd' };
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
        service_thread.join( );
    }
}
