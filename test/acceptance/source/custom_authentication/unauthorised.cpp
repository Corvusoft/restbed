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

void authentication_handler( const shared_ptr< Session >& session, const function< void ( const shared_ptr< Session >& ) >& callback )
{
    auto authorisation = session->get_request( )->get_header( "Authorization" );

    if ( authorisation not_eq "Basic Q29ydnVzb2Z0OkdsYXNnb3c=" )
    {
        session->close( UNAUTHORIZED, { { "WWW-Authenticate", "Basic realm=\"restbed\"" } } );
    }

    callback( session );
}

void get_method_handler( const shared_ptr< Session >& session )
{
    session->close( OK, "Password Protected Hello, World!", { { "Content-Length", "32" } } );
}

SCENARIO( "custom resource authentication", "[resource]" )
{
    GIVEN( "I publish a secure resource at '/resources/1' with a HTTP 'GET' method handler" )
    {
        auto resource = make_shared< Resource >( );
        resource->set_path( "/resources/1" );
        resource->set_method_handler( "GET", &get_method_handler );

        auto settings = make_shared< Settings >( );
        settings->set_port( 1984 );
        settings->set_default_header( "Connection", "close" );

        Service service;
        service.publish( resource );
        service.set_authentication_handler( &authentication_handler );

        thread service_thread( [ &service, settings ] ( )
        {
            service.start( settings );
        } );

        WHEN( "I perform a HTTP 'GET' request to '/resources/1' with header 'Authorization: Basic Q29y28fsoOkdsYXNnb3c'" )
        {
            Http::Request request;
            request.port = 1984;
            request.host = "localhost";
            request.path = "/resources/1";
            request.headers.insert( make_pair( "Authorization", "Basic Q29y28fsoOkdsYXNnb3c" ) );

            auto response = Http::get( request );

            THEN( "I should see a '401' (Unauthorized) status code" )
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
        service_thread.join( );
    }
}
