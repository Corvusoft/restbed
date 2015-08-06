/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <thread>
#include <string>
#include <memory>
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
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_handler( const shared_ptr< Session >& session )
{
    const auto request = session->get_request( );
    
    int id = 0;
    request->get_path_parameter( "id", id );
    REQUIRE( 100 == id );
    
    REQUIRE( "events" == request->get_path_parameter( "name" ) );
    
    session->close( 204 );
}

SCENARIO( "request path parameters", "[resource]" )
{
    GIVEN( "I publish a resource at '/resources/queues/{name: [a-z]*}/messages/{id: [0-9]*}' with a HTTP 'GET' method handler" )
    {
        auto resource = make_shared< Resource >( );
        resource->set_path( "/resources/queues/{name: [a-z]*}/messages/{id: [0-9]*}" );
        resource->set_method_handler( "GET", get_handler );
        resource->set_default_header( "Connection", "close" );
        
        auto settings = make_shared< Settings >( );
        settings->set_port( 1984 );
        
        shared_ptr< thread > worker = nullptr;
        
        Service service;
        service.publish( resource );
        service.set_ready_handler( [ &worker ]( Service & service )
        {
            worker = make_shared< thread >( [ &service ] ( )
            {
                WHEN( "I perform a HTTP 'GET' request to '/resources/queues/events/messages/100'" )
                {
                    Http::Request request;
                    request.port = 1984;
                    request.host = "localhost";
                    request.path = "/resources/queues/events/messages/100";
                    
                    auto response = Http::get( request );
                    
                    THEN( "I should see a '204' (No Content) status code" )
                    {
                        REQUIRE( 204 == response.status_code );
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
                }
                
                service.stop( );
            } );
        } );
        service.start( settings );
        worker->join( );
    }
}
