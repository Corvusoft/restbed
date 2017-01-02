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

//External Includes
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::string;
using std::function;
using std::multimap;
using std::make_pair;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void method_not_implemented_handler( const shared_ptr< Session > session )
{
    session->close( -232, "Banned Method", { { "Content-Length", "13" } } );
}

SCENARIO( "custom resource method not implemented handler", "[resource]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources/1" );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_method_not_implemented_handler( method_not_implemented_handler );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I publish a resource at '/resources/1' without a HTTP 'GET' method handler" )
            {
                WHEN( "I perform a HTTP 'PUT' request to '/resources/1'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_method( "PUT" );
                    request->set_path( "/resources/1" );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '-232' (No Appropriate Status Message Found) status code" )
                    {
                        REQUIRE( -232 == response->get_status_code( ) );
                        REQUIRE( "No Appropriate Status Message Found" == response->get_status_message( ) );
                    }
                    
                    AND_THEN( "I should see a response body of 'Banned Method'" )
                    {
                        auto actual = Http::fetch( 13, response );
                        Bytes expectation { 'B', 'a', 'n', 'n', 'e', 'd', ' ', 'M', 'e', 't', 'h', 'o', 'd' };
                        REQUIRE( actual == expectation );
                    }
                    
                    multimap< string, string > headers = response->get_headers( );
                    
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
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
