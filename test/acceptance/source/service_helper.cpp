#include <restbed>

using namespace restbed;

extern "C"
{
	Service* create_service( int port )
	{
		Settings settings;
		settings.set_port( port );

		return new Service( settings );
	}

	void release_service( Service* service )
	{
		free service;
	}

	void add_service_resource( Service* service, Resource* resource )
	{
		service->publish( resource );
	}

	void remove_service_resource( Service* service, Resource* resource )
	{
		service->suppress( resource );
	}
}
