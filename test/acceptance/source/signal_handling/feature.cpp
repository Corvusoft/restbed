/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <map>
#include <thread>
#include <string>
#include <memory>
#include <chrono>
#include <ciso646>
#include <csignal>
#include <stdexcept>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::raise;
using std::thread;
using std::string;
using std::multimap;
using std::shared_ptr;
using std::make_shared;
using std::chrono::seconds;

//Project Namespaces
using namespace restbed;

//External Namespaces

int signal_number_actual = 0;

void signal_handler( const int signal_number )
{
    signal_number_actual = signal_number;
}

SCENARIO( "Handle specific signal", "[service]" )
{
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.set_signal_handler( SIGHUP, signal_handler );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I start a service with a 'SIGHUP' signal handler" )
            {
                WHEN( "I generate a 'SIGHUP' event" )
                {
                    THEN( "I should see a 'SIGHUP' signal number" )
                    {
                        signal_number_actual = 0;
                        REQUIRE( signal_number_actual == 0 );
                        
                        raise( SIGHUP );
                        
                        std::this_thread::sleep_for( seconds( 1 ) );
                        
                        REQUIRE( signal_number_actual == SIGHUP );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
