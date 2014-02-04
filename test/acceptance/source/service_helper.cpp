/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <string>

//Project Includes
#include <restbed>
#include "callbacks.h"
#include "basic_auth_service.h"

//External Includes

//System Namespaces
using std::string;

//Project Namespaces
using restbed::Mode;
using restbed::Service;
using restbed::Request;
using restbed::Response;
using restbed::Resource;
using restbed::Settings;

//External Namespaces

const size_t NUMBER_OF_HTTP_METHODS = 8;

extern "C"
{
	Service* create_service( const int port )
	{
		Settings settings;
		settings.set_port( port );
		settings.set_mode( Mode::ASYNCHRONOUS );

		Service* service = new Service( settings );
		service->start( );

		return service;
	}

	Service* create_authenticated_service( const int port )
	{
		Settings settings;
		settings.set_port( port );
		settings.set_mode( Mode::ASYNCHRONOUS );

		Service* service = new BasicAuthService( settings );
		service->start( );

		return service;	
	}

	void release_service( Service* service )
	{
		service->stop( );
		
		delete service;
	}

	void publish_default_resource( Service* service )
	{
	    Resource* resource = new Resource( );

	    service->publish( *resource );	
	}

	void publish_resource( Service* service, const char* path, const char** methods )
	{
	    Resource* resource = new Resource( );
	    resource->set_path( path );

	    for ( size_t index = 0; index < NUMBER_OF_HTTP_METHODS and methods[ index ] not_eq nullptr; index++ ) 
	    {
	    	resource->set_method_handler( methods[ index ], &ok_callback_handler );
	    }

	    service->publish( *resource );
	}

	void publish_resource_with_response_header( Service* service, const char* name, const char* value )
	{
		Resource* resource = new Resource( );
		resource->set_method_handler( "GET", std::bind( &resource_with_response_header_handler, std::placeholders::_1, string( name ), string( value ) ) );
		resource->set_method_handler( "PUT", std::bind( &resource_with_response_header_handler, std::placeholders::_1, string( name ), string( value ) ) );
		resource->set_method_handler( "POST", std::bind( &resource_with_response_header_handler, std::placeholders::_1, string( name ), string( value ) ) );
		resource->set_method_handler( "HEAD", std::bind( &resource_with_response_header_handler, std::placeholders::_1, string( name ), string( value ) ) );
		resource->set_method_handler( "DELETE", std::bind( &resource_with_response_header_handler, std::placeholders::_1, string( name ), string( value ) ) );
		resource->set_method_handler( "OPTIONS", std::bind( &resource_with_response_header_handler, std::placeholders::_1, string( name ), string( value ) ) );
		resource->set_method_handler( "CONNECT", std::bind( &resource_with_response_header_handler, std::placeholders::_1, string( name ), string( value ) ) );

		service->publish( *resource );
	}

	void publish_json_resource( Service* service, const char* path )
	{
		Resource* resource = new Resource( );
		resource->set_path( path );
		resource->set_method_handler( "GET", &json_ok_callback_handler );

		service->publish( *resource );
	}

	void publish_xml_resource( Service* service, const char* path )
	{
		Resource* resource = new Resource( );
		resource->set_path( path );
		resource->set_method_handler( "GET", &xml_ok_callback_handler );

		service->publish( *resource );
	}

	void publish_json_resource_with_header_filter( Service* service )
	{
		Resource* resource = new Resource( );
		resource->set_method_handler( "GET", &json_ok_callback_handler );
		resource->set_header_filter( "Content-Type", "application/json" );

		service->publish( *resource );
	}

	void publish_xml_resource_with_header_filter( Service* service )
	{
		Resource* resource = new Resource( );
		resource->set_method_handler( "GET", &xml_ok_callback_handler );
		resource->set_header_filter( "Content-Type", "application/xml" );

		service->publish( *resource );
	}
}
