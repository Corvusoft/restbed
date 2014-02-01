/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <string>

//Project Includes
#include <restbed>
#include "callbacks.h"

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

//BasicAuthService
class AuthenticatedService : public Service
{
	public:
		AuthenticatedService( const Settings& settings ) : Service( settings )
		{
			//n/a
		}

	protected:
		virtual void authentication_handler( const Request& request, /*out*/ Response& response )
		{
			auto authorisation = request.get_header( "Authorization" );

			if ( authorisation == "Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==" )
			{
				response.set_status_code( 200 );
			}
			else
			{
				response.set_status_code( 401 );
				response.set_header( "WWW-Authenticate", "Basic realm=\"Restbed\"" );
			}
		}
};


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

	Service* create_authenticated_service( int port )
	{
		Settings settings;
		settings.set_port( port );
		settings.set_mode( Mode::ASYNCHRONOUS );

		Service* service = new AuthenticatedService( settings );
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

	void publish_resource( Service* service, const char* path, const char* method )
	{
	    Resource* resource = new Resource( );
	    resource->set_path( path );
	    resource->set_method_handler( method, &callback_handler );

	    service->publish( *resource );
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

	//really need to clean up these method names/options
	void publish_resource_with_response_header( Service* service, const char* name, const char* value ) //string?
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
}
