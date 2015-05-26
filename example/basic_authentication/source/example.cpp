#include <cstdlib>

#include "restbed"

using namespace restbed;

void authentication_handler( const Request& request, /*out*/ Response& response )
{
    auto authorisation = request.get_header( "Authorization" );
    
    if ( authorisation == "Basic Q29ydnVzb2Z0OkdsYXNnb3c=" )
    {
        response.set_status_code( 200 );
    }
    else
    {
        response.set_status_code( 401 );
        response.set_header( "WWW-Authenticate", "Basic realm=\"Restbed\"" );
    }
}

Response get_method_handler( const Request& )
{
    Response response;
    response.set_body( "Password Protected Hello, World!" );
    response.set_status_code( StatusCode::OK );
    
    return response;
}

int main( const int, const char** )
{
    Resource resource;
    resource.set_path( "/resource" );
    resource.set_method_handler( "GET", &get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    Service service( settings );
    service.set_authentication_handler( &authentication_handler );
    service.publish( resource );
    service.start( );
    
    return EXIT_SUCCESS;
}
