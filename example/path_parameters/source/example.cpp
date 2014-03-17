#include <string>
#include "restbed"

using namespace std;
using namespace restbed;

Response get_method_handler( const Request& );

int main( int, char** )
{
    Resource resource;
    resource.set_path( "/resource/{name: .*}" );
    resource.set_method_handler( "GET", &get_method_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    
    Service service( settings );
    service.publish( resource );
    service.start( );
    
    return EXIT_SUCCESS;
}

Response get_method_handler( const Request& request )
{
    string body = "Hello, ";
    body += request.get_path_parameter( "name" ) + "!";
    
    Response response;
    response.set_body( body );
    response.set_status_code( StatusCode::OK );
    
    return response;
}
