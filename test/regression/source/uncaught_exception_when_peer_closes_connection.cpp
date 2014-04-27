/*
 * Copyright (c) 2013, 2014 Corvusoft
 *
 * bug tracker issue #29
 */

//System Includes
#include <thread>
#include <memory>
#include <unistd.h>
#include <functional>

//Project Includes
#include <restbed>
#include "helpers/http.h"

//External Includes
#include <asio.hpp>
#include <gtest/gtest.h>

//System Namespaces
using std::thread;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces
using asio::ip::tcp;
using asio::system_error;

bool exception_was_thrown = false;

void worker( shared_ptr< Service > service )
{
    try
    {   
        service->start( );
    }
    catch( const system_error& se )
    {
        if ( se.code( ) == asio::error::eof )
        {
            exception_was_thrown = true;  
        }
    }
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

    // A short delay is required to allow threaded service to initialise.
    // Without this, the test will ALWAYS pass.
    sleep(1); 

    asio::io_service io_service;
    tcp::socket socket( io_service );
    tcp::resolver resolver( io_service );
    asio::connect( socket, resolver.resolve( { "localhost", "1984" } ) );

    socket.close( );

    service->stop( );

    restbed_thread.join( );

    ASSERT_FALSE( exception_was_thrown );
}
