#include <cstdlib>

#include "restbed"

using namespace restbed;

Response get_method_handler( const Request& )
{
    Response response;
    response.set_body( StatusCode::to_string( 418 ) );
    response.set_status_code( 418 );
    
    return response;
}

int main( const int, const char** )
{
    auto status_code_mappings = StatusCode::get_mappings( );
    status_code_mappings[ 418 ] = "I'm a teapot";
    
    StatusCode::set_mappings( status_code_mappings );
    
    Resource resource;
    resource.set_method_handler( "GET", &get_method_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    
    Service service( settings );
    service.publish( resource );
    service.start( );
    
    return EXIT_SUCCESS;
}
