/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <map>
#include <chrono>
#include <thread>
#include <string>
#include <memory>
#include <ciso646>
#include <stdexcept>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::stoi;
using std::thread;
using std::string;
using std::multimap;
using std::to_string;
using std::shared_ptr;
using std::make_shared;
using std::chrono::milliseconds;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_handler( const shared_ptr< Session > session )
{
    session->sleep_for( milliseconds( 5 ), [ ]( const shared_ptr< Session > session )
    {
        session->close( 200, { { "Connection", "close" } } );
    } );
}

SCENARIO( "close active request", "[client]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I have started a service and perform a HTTP 'GET' request" )
            {
                auto request = make_shared< Request >( );
                request->set_port( 1984 );
                request->set_host( "localhost" );
                request->set_method( "GET" );
                request->set_path( "/resource" );
                
                auto response = Http::sync( request );
                
                WHEN( "I close the connection before seeing a response" )
                {
                    Http::close( request );
                    
                    THEN( "I should see the connection closed" )
                    {
                        REQUIRE( Http::is_open( request ) == false );
                        REQUIRE( Http::is_open( response ) == false );
                        REQUIRE( Http::is_closed( request ) == true );
                        REQUIRE( Http::is_closed( response ) == true );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}

SCENARIO( "close active response", "[client]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I have started a service and perform a HTTP 'GET' request" )
            {
                auto request = make_shared< Request >( );
                request->set_port( 1984 );
                request->set_host( "localhost" );
                request->set_method( "GET" );
                request->set_path( "/resource" );
                
                auto response = Http::sync( request );
                
                WHEN( "I close the connection before seeing a response" )
                {
                    Http::close( response );
                    
                    THEN( "I should see the connection closed" )
                    {
                        REQUIRE( Http::is_open( request ) == false );
                        REQUIRE( Http::is_open( response ) == false );
                        REQUIRE( Http::is_closed( request ) == true );
                        REQUIRE( Http::is_closed( response ) == true );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}

SCENARIO( "close inactive request", "[client]" )
{
    GIVEN( "I have not started a service and not perform a HTTP 'GET' request" )
    {
        auto request = make_shared< Request >( );
        request->set_port( 1984 );
        request->set_host( "localhost" );
        request->set_method( "GET" );
        request->set_path( "/resource" );
        
        WHEN( "I close the request socket" )
        {
            Http::close( request );
            
            THEN( "I should see the connection closed" )
            {
                REQUIRE( Http::is_open( request ) == false );
                REQUIRE( Http::is_closed( request ) == true );
            }
        }
    }
}

SCENARIO( "close inactive response", "[client]" )
{
    GIVEN( "I have a blank response" )
    {
        auto response = make_shared< Response >( );
        
        WHEN( "I close the response socket" )
        {
            Http::close( response );
            
            THEN( "I should see the connection closed" )
            {
                REQUIRE( Http::is_open( response ) == false );
                REQUIRE( Http::is_closed( response ) == true );
            }
        }
    }
}

SCENARIO( "close null request", "[client]" )
{
    GIVEN( "I have a null request" )
    {
        WHEN( "I close the request socket" )
        {
            shared_ptr< Request > request = nullptr;
            
            Http::close( request );
            
            THEN( "I should see the connection closed" )
            {
                REQUIRE( Http::is_open( request ) == false );
                REQUIRE( Http::is_closed( request ) == true );
            }
        }
    }
}

SCENARIO( "close null response", "[client]" )
{
    GIVEN( "I have a null response" )
    {
        WHEN( "I close the response socket" )
        {
            shared_ptr< Response > response = nullptr;
            
            Http::close( response );
            
            THEN( "I should see the connection closed" )
            {
                REQUIRE( Http::is_open( response ) == false );
                REQUIRE( Http::is_closed( response ) == true );
            }
        }
    }
}
