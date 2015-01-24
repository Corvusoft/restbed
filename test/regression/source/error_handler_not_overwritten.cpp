/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 *
 * bug tracker issue #56
 */

//System Includes
#include <memory>
#include <cstdlib>

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
bool error_handler_called = false;

Response faulty_method_handler( const Request& )
{
    throw StatusCode::SERVICE_UNAVAILABLE;
    
    Response response;
    return response;
}

void error_handler( const int status_code, const Request&, /*out*/ Response& response )
{
    error_handler_called = true;

    response.set_status_code( status_code );
    response.set_body( StatusCode::to_string( status_code ) );
}

TEST( Resource, overwrite_existing_resource )
{
    Resource resource;
    resource.set_path( "TestResource" );
    resource.set_method_handler( "GET", &faulty_method_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    settings.set_mode( ASYNCHRONOUS );
    
    m_service = make_shared< Service >( settings );
    m_service->set_error_handler( &error_handler );
    m_service->publish( resource );
    m_service->start( );

    Http::Request request;
    request.method = "GET";
    request.port = 1984;
    request.host = "localhost";
    request.path = "/TestResource";

    auto response = Http::get( request );
    
    EXPECT_EQ( true, error_handler_called );
    
    m_service->stop( );
}
