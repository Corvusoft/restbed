/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes

//Project Includes
#include <restbed>
#include "callbacks.h"

//External Includes

//System Namespaces

//Project Namespaces
using restbed::Mode;
using restbed::Service;
using restbed::Request;
using restbed::Response;
using restbed::Resource;
using restbed::Settings;

//External Namespaces

extern "C"
{
	Service* create_service( int port )
	{
		Settings settings;
		settings.set_port( port );
		settings.set_mode( Mode::ASYNCHRONOUS );

		Service* service = new Service( settings );
		service->start( );

		return service;
	}

	void release_service( Service* service )
	{
		delete service;
	}

	void publish_resource( Service* service, const char* path, const char* method )
	{
	    Resource* resource = new Resource( );
	    resource->set_path( path );
	    resource->set_method_handler( method, &callback_handler );

	    service->publish( *resource );
	}

	void suppress_method_handler( Service* service, const char* method )
	{

	}

	void publish_json_resource( Service* service, const char* path )
	{
		Resource* resource = new Resource( );
		resource->set_path( path );
		resource->set_method_handler( "GET", &json_callback_handler );
		resource->set_header_filter( "Content-Type", "application/json" );

		service->publish( *resource );
	}

	void publish_xml_resource( Service* service, const char* path )
	{
		Resource* resource = new Resource( );
		resource->set_path( path );
		resource->set_method_handler( "GET", &xml_callback_handler );
		resource->set_header_filter( "Content-Type", "application/xml" );

		service->publish( *resource );
	}

	void publish_api_1_0_resource( Service* service, const char* path )
	{
		Resource* resource = new Resource( );
		resource->set_path( path );
		resource->set_method_handler( "GET", &api_1_0_callback_handler );
		resource->set_header_filter( "api-version", "1.0" );

		service->publish( *resource );
	}
		
	void publish_api_1_1_resource( Service* service, const char* path )
	{
		Resource* resource = new Resource( );
		resource->set_path( path );
		resource->set_method_handler( "GET", &api_1_1_callback_handler );
		resource->set_header_filter( "api-version", "1.1" );

		service->publish( *resource );
	}
}
