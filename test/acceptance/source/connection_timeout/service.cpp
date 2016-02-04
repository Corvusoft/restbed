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
#include <asio.hpp>
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::string;
using std::multimap;
using std::shared_ptr;
using std::make_shared;
using std::chrono::seconds;

//Project Namespaces
using namespace restbed;

//External Namespaces
using asio::ip::tcp;
using asio::connect;
using asio::io_service;

void get_handler( const shared_ptr< Session > session )
{
    session->close( 200 );
}

SCENARIO( "validate connection timeout", "[service]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_connection_timeout( seconds( 5 ) );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I create a service with a socket connection timeout of '5' seconds" )
            {
                WHEN( "I perform establish a network connection and wait '5' seconds" )
                {
                    io_service io_service;
                    tcp::socket socket( io_service );
                    tcp::resolver resolver( io_service );
                    connect( socket, resolver.resolve( { "localhost", "1984" } ) );
                    
                    std::this_thread::sleep_for( seconds( 60 ) );
                    
                    THEN( "I should see the socket closed by the peer" )
                    {
                        REQUIRE( false == socket.is_open( ) );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
