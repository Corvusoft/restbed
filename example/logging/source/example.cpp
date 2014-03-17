#include "restbed"

using namespace std;
using namespace restbed;

Response get_method_handler( const Request& )
{
    Response response;
    response.set_body( "Hello, World!" );
    response.set_status_code( StatusCode::OK );

    return response;
}

int main( int, char** )
{
    Resource resource;
    resource.set_path( "/resource" );
    resource.set_method_handler( "GET", &get_method_handler );

    auto logger = make_shared< Logger >( );

    Settings settings;
    settings.set_port( 1984 );

    Service service( settings );
    service.publish( resource );
    service.set_logger( logger );
    service.start( );

    return EXIT_SUCCESS;
}
