/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

/*
 * See issue tracker bug #3 for details.
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes
#include <memory>

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

shared_ptr< Service > m_service;

Response json_get_handler( const Request& )
{
    Response response;
    response.set_status_code( StatusCode::OK );
    response.set_body( "{ name: \"value\" }" );
    
    return response;
}

Response xml_get_handler( const Request& )
{
    Response response;
    response.set_status_code( StatusCode::UNAUTHORIZED );
    response.set_body( "<name>value</value>" );
    
    return response;
}

TEST( Resource, overwrite_existing_resource )
{
    Resource initial_resource;
    initial_resource.set_path( "TestResource" );
    initial_resource.set_method_handler( "GET", &json_get_handler );
    
    Resource secondary_resource;
    secondary_resource.set_path( "TestResource" );
    secondary_resource.set_method_handler( "GET", &xml_get_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    settings.set_mode( ASYNCHRONOUS );
    
    m_service = make_shared< Service >( settings );
    m_service->publish( initial_resource );
    m_service->publish( secondary_resource );
    m_service->start( );
    
    auto response = Http::get( "http://localhost:1984/TestResource" );
    
    EXPECT_EQ( "401", response[ "Status Code" ] );
    
    m_service->stop( );
}

TEST( Resource, add_alternative_resource )
{
    Resource initial_resource;
    initial_resource.set_path( "TestResource" );
    initial_resource.set_header_filter( "Content-Type", "application/json" );
    initial_resource.set_method_handler( "GET", &json_get_handler );
    
    Resource secondary_resource;
    secondary_resource.set_path( "TestResource" );
    secondary_resource.set_header_filter( "Content-Type", "application/xml" );
    secondary_resource.set_method_handler( "GET", &xml_get_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    settings.set_mode( ASYNCHRONOUS );
    
    m_service = make_shared< Service >( settings );
    m_service->publish( initial_resource );
    m_service->publish( secondary_resource );
    m_service->start( );
    
    auto response = Http::get( "http://localhost:1984/TestResource", { { "Content-Type", "application/xml" } } );
    
    EXPECT_EQ( "401", response[ "Status Code" ] );
    
    m_service->stop( );
}
