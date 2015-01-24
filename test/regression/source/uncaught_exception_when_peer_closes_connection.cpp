/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 *
 * bug tracker issue #29
 */

//System Includes
#include <thread>
#include <chrono>
#include <memory>
#include <unistd.h>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <asio.hpp>
#include <gtest/gtest.h>

//System Namespaces
using std::thread;
using std::shared_ptr;
using std::make_shared;
using std::chrono::seconds;

//Project Namespaces
using namespace restbed;

//External Namespaces
using asio::ip::tcp;
using asio::system_error;
using namespace framework;

bool exception_was_thrown = false;

void worker( shared_ptr< Service > service )
{
    try
    {
        service->start( );
    }
    catch ( const system_error& se )
    {
        if ( se.code( ) == asio::error::eof )
        {
            exception_was_thrown = true;
        }
    }
}

void wait_for_service_initialisation( void )
{
    std::this_thread::sleep_for( seconds( 1 ) );
}

TEST( Service, peer_closes_connection_without_sending_data )
{
    Resource resource;
    resource.set_path( "test" );
    
    Settings settings;
    settings.set_port( 1984 );
    settings.set_mode( SYNCHRONOUS );
    
    auto service = make_shared< Service >( settings );
    service->publish( resource );
    
    thread restbed_thread( worker, service );
    
    wait_for_service_initialisation( );
    
    asio::io_service io_service;
    tcp::socket socket( io_service );
    tcp::resolver resolver( io_service );
    asio::connect( socket, resolver.resolve( { "localhost", "1984" } ) );
    
    socket.close( );
    
    service->stop( );
    
    restbed_thread.join( );
    
    ASSERT_FALSE( exception_was_thrown );
}
