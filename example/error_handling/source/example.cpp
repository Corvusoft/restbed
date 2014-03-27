#include "restbed"

using namespace restbed;

Response faulty_method_handler( const Request& )
{
    throw StatusCode::SERVICE_UNAVAILABLE;

    Response response;
    return response;
}

void error_handler( const int status_code, const Request&, /*out*/ Response& response )
{
    response.set_status_code( status_code );
    response.set_body( StatusCode::to_string( status_code ) );
}

int main( int, char** )
{
    Resource resource;
    resource.set_method_handler( "GET", &faulty_method_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    
    Service service( settings );
    service.set_error_handler( &error_handler );
    service.publish( resource );
    service.start( );
    
    return EXIT_SUCCESS;
}
