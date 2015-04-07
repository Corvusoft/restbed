#include <string>
#include <cstdlib>

#include "restbed"

using namespace std;
using namespace restbed;

Response get_persistent_method_handler( const Request& )
{
    Response response;
    response.set_status_code( StatusCode::OK );
    response.set_header( "Connection", "keep-alive" );
    response.set_body( "persistent resource request" );

    return response;
}

Response get_intermittent_method_handler( const Request& )
{
    Response response;
    response.set_status_code( StatusCode::OK );
    response.set_body( "intermittent resource request" );

    return response;
}

int main( const int, const char** )
{
    Resource persistent;
    persistent.set_path( "/resources/persistent" );
    persistent.set_method_handler( "GET", &get_persistent_method_handler );

    Resource intermittent;
    intermittent.set_path( "/resources/intermittent" );
    intermittent.set_method_handler( "GET", &get_intermittent_method_handler );

    Settings settings;
    settings.set_port( 1984 );
    
    Service service( settings );
    service.publish( persistent );
    service.publish( intermittent );
    service.start( );
    
    return EXIT_SUCCESS;
}
