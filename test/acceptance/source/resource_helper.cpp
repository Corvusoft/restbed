/*
 * Copyright (c) 2013 Corvusoft
 */
 
#include <restbed>

using namespace restbed;

extern "C"
{
	Resource* create_resource( const char* path )
	{
	    Resource* resource = new Resource();
	    resource->set_path( path );

	    return resource;
	}

	void release_resource( Resource* resource )
	{
		delete resource;
	}

	void add_resource_header_filter( Resource* resource, const char* name, const char* value )
	{
		resource->set_header_filter(name, value);
	}

	void add_resource_method_handler( Resource* resource, const char* method, Response (*handler)(Request) )
	{

	}
}
