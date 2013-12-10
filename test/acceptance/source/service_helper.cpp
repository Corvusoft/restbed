/*
 * Copyright (c) 2013 Corvusoft
 */

#include <restbed>

using namespace restbed;

Response callback_handler( const Request& )
{
	Response response;
	response.set_status_code( 200 );

	return response;
}

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

	void publish_method_handler( Service* service, char* method )
	{
	    Resource* resource = new Resource( );
	    resource->set_method_handler( method, &callback_handler );

	    service->publish( *resource );
	}

	void suppress_method_handler( Service* service, char* method )
	{

	}
}
