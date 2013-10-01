#include <iostream>
#include <restbed>

//TODO:
//web site
//ssl support

using namespace restbed;
            
Response get_handler( const Request& request )
{
    Response response;
    response.set_body( "hello from get handler" );
    response.set_header( "Forename", "Ben" );
    response.set_status_code( StatusCode::CREATED );

    std::cout << "hello from get handler" << std::endl;
    
    return response;
}
//exception trace!!!

//bug supply invalid regex for set path or set header filter.
//we need to validate the regex segments first!
//PathParam.parse( const std::string& path );
//throws on invalid?!?

int main( int, char** )
try
{
    Settings settings;
    settings.set_port( 1984 );
    settings.set_root( "resources" );

    Service service( settings );

    Resource resource;
    resource.set_path( "events/{type: [a-z]*}/{id: [0-9]*}" ); //make sure this check is also ignores case , remove space. also check for valid regex
    resource.set_header_filter( "Content-Type", "application/.*" ); //make sure this check is also ignores case.
    resource.set_method_handler( "GET", &get_handler );

    std::cout << "path: " << resource.get_path( ) << std::endl;

    service.publish( resource );

    service.start( );

    return EXIT_SUCCESS;
}
catch ( const std::exception& ex )
{
    std::cout << "restbed failed: " << ex.what( ) << std::endl;

    return EXIT_FAILURE;
}