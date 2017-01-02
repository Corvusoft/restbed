/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <memory>
#include <stdexcept>

//Project Includes
#include <corvusoft/restbed/service.hpp>
#include <corvusoft/restbed/settings.hpp>
#include <corvusoft/restbed/ssl_settings.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;

//Project Namespaces
using restbed::Service;
using restbed::Settings;
using restbed::SSLSettings;

//External Namespaces

#ifdef BUILD_SSL
TEST_CASE( "validate runtime_error is not thrown when SSLSettings passed into start", "[service]" )
{
    const auto ssl_settings = make_shared< SSLSettings >( );
    ssl_settings->set_port( 1989 );
    
    const auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_ssl_settings( ssl_settings );
    
    Service service;
    service.set_ready_handler( [ ]( Service & service )
    {
        service.stop( );
    } );
    
    REQUIRE_NOTHROW( service.start( settings ) );
}
#else
TEST_CASE( "validate runtime_error is thrown when SSLSettings passed into start", "[service]" )
{
    const auto settings = make_shared< Settings >( );
    settings->set_ssl_settings( make_shared< SSLSettings >( ) );
    
    Service service;
    REQUIRE_THROWS_AS( service.start( settings ), runtime_error );
    
    service.stop( );
}
#endif
