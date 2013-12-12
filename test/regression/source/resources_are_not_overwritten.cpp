/*
 * Copyright (c) 2013 Corvusoft
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

void setup( void );
void teardown( void );
Response initial_get_handler( const Request& );
Response secondary_get_handler( const Request& );

TEST( Resource, overwrite_existing_resource )
{
	setup( );

	int status_code = Http::get( "http://localhost:1984/TestResource" );
	
	EXPECT_EQ( 401, status_code );

	teardown( );
}

Response initial_get_handler( const Request& )
{
	Response response;
	response.set_status_code( StatusCode::OK );

	return response;
}

Response secondary_get_handler( const Request& )
{
	Response response;
	response.set_status_code( StatusCode::UNAUTHORIZED );

	return response;
}

void setup( void )
{
	Resource initial_resource;
	initial_resource.set_path( "TestResource" );
    initial_resource.set_method_handler( "GET", &initial_get_handler );

	Resource secondary_resource;
	initial_resource.set_path( "TestResource" );
    secondary_resource.set_method_handler( "GET", &secondary_get_handler );

    Settings settings;
    settings.set_port( 1984 );
    settings.set_mode( ASYNCHRONOUS );

    m_service = make_shared< Service >( settings );
    m_service->publish( initial_resource );
    m_service->publish( secondary_resource );
    m_service->start( );
}

void teardown( void )
{
	m_service->stop( );
}
