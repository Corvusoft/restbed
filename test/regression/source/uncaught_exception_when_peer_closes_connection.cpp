/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

/*
 * See issue tracker bug #29 for details.
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes
#include <memory>
#include <functional>
#include <thread>
#include <unistd.h>

//Project Includes
#include <restbed>
#include "helpers/http.h"

//External Includes
#include <gtest/gtest.h>
#include <asio.hpp>

//System Namespaces
using std::shared_ptr;
using std::make_shared;
using asio::ip::tcp;
using std::thread;

//Project Namespaces
using namespace restbed;

//External Namespaces

bool exception_was_thrown = false;

void worker( shared_ptr<Service> service )
{
    try
    {   
        service->start( );
    }
    catch( const asio::system_error &asio_error )
    {
        if ( asio_error.code() == asio::error::eof )
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

    asio::io_service io_service;
    tcp::socket s( io_service );
    tcp::resolver resolver( io_service );
    asio::connect( s, resolver.resolve( { "localhost", "1984" } ) );
    
    sleep(1);
    s.close( );

    service->stop();
    restbed_thread.join();

    ASSERT_FALSE( exception_was_thrown );

}
