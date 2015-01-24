/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 *
 * bug tracker issue #3
 */

//System Includes
#include <memory>

//Project Includes
#include <restbed>

//External Includes
#include <gtest/gtest.h>
#include <corvusoft/framework/http>

//System Namespaces
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces
using namespace framework;

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

    Http::Request request;
    request.method = "GET";
    request.port = 1984;
    request.host = "localhost";
    request.path = "/TestResource";

    auto response = Http::get( request );
    
    EXPECT_EQ( 401, response.status_code );
    
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

    Http::Request request;
    request.method = "GET";
    request.port = 1984;
    request.host = "localhost";
    request.path = "/TestResource";
    request.headers = { { "Content-Type", "application/xml" } };

    auto response = Http::get( request );
    
    EXPECT_EQ( 401, response.status_code );
    
    m_service->stop( );
}
