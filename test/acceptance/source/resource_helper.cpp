#include <restbed>

using namespace restbed;

//http://stackoverflow.com/questions/874245/python-ctypes-and-function-pointers
//http://docs.python.org/2/library/ctypes.html#callback-functions

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
		free resource;
	}

	void add_resource_header_filter( Resource* resource, const char* name, const char* value )
	{
		resource->set_header_filter(name, value);
	}

	void add_resource_method_handler( Resource* resource, const char* method, void* handler )
	{

	}
}
