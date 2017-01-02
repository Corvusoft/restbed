/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <memory>
#include <chrono>
#include <thread>
#include <ciso646>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::shared_ptr;
using std::make_shared;
using std::chrono::seconds;

//Project Namespaces
using namespace restbed;

//External Namespaces

SCENARIO( "Report service status", "[service]" )
{
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            std::this_thread::sleep_for( seconds( 1 ) );
            
            REQUIRE( service.is_up( ) );
            REQUIRE_FALSE( service.is_down( ) );
            REQUIRE( service.get_uptime( ) not_eq seconds( 0 ) );
            
            service.stop( );
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
