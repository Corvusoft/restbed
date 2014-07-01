/*
 * Copyright (c) 2013, 2014 Corvusoft
 *
 * bug tracker issue #53
 */

//System Includes
#include <memory>
#include <functional>

//Project Includes
#include <restbed>
#include "helpers/http.h"

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

Response get_handler( const Request& )
{
    Response response;
    response.set_status_code( StatusCode::OK );
    
    return response;
}

TEST( Service, with_space_in_path )
{
    Resource resource;
    resource.set_path( "test queue" );
    resource.set_method_handler( "GET", &get_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    settings.set_root( "queues" );
    settings.set_mode( ASYNCHRONOUS );
    
    auto service = make_shared< Service >( settings );
    service->publish( resource );
    
    service->start( );
    
    auto response = Http::get( "http://localhost:1984/queues/test queue" );
    
    EXPECT_EQ( "400", response[ "Status Code" ] );
    
    service->stop( );
}

TEST( Service, without_space_in_path )
{
    Resource resource;
    resource.set_path( "testQueue" );
    resource.set_method_handler( "GET", &get_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    settings.set_root( "queues" );
    settings.set_mode( ASYNCHRONOUS );
    
    auto service = make_shared< Service >( settings );
    service->publish( resource );
    
    service->start( );
    
    auto response = Http::get( "http://localhost:1984/queues/testQueue" );
    
    EXPECT_EQ( "200", response[ "Status Code" ] );
    
    service->stop( );
}
