/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <chrono>
#include <thread>
#include <string>
#include <memory>
#include <vector>
#include <ciso646>
#include <stdexcept>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <asio.hpp>
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::chrono::seconds;

//Project Namespaces
using namespace restbed;

//External Namespaces
using asio::ip::tcp;
using asio::connect;
using asio::io_service;
using asio::socket_base;

void get_handler( const shared_ptr< Session > session )
{
    session->sleep_for( seconds( 4 ), [ ]( const shared_ptr< Session > session )
    {
        if ( session->is_open( ) )
        {
            session->close( 200 );
        }
    } );
}

SCENARIO( "validate connection timeout", "[socket]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_connection_timeout( seconds( 30 ) );
    settings->set_port( 1984 );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I create a service with a delayed 'GET' handler" )
            {
                WHEN( "I perform a request with a connection timeout of '2' seconds" )
                {
                    auto configuration = make_shared< Settings >( );
                    configuration->set_connection_timeout( seconds( 2 ) );
                    
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resource" );
                    
                    auto response = Http::sync( request, configuration );
                    
                    THEN( "I should see the service has closed the socket" )
                    {
                        REQUIRE( response->get_status_code( ) == 0 );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
