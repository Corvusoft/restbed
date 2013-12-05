#include <iostream>
#include <restbed>
#include <thread>
#include <memory>

using namespace restbed;
            
Response get_handler( const Request& request )
{
    Response response;
    response.set_body( "hello from get handler" );
    response.set_header( "Forename", "Ben" );
    response.set_status_code( StatusCode::CREATED );

    std::cout << "hello from get handler" << std::endl;

    for ( auto parameter : request.get_path_parameters( ) )
    {
        std::cout << "parameter name: " << parameter.first << std::endl;
        std::cout << "parameter value: " << parameter.second << std::endl;
    }

    for ( auto parameter : request.get_query_parameters( ) )
    {
        std::cout << "query name: " << parameter.first << std::endl;
        std::cout << "query value: " << parameter.second << std::endl;
    }


    std::cout << "Bytes" << std::endl;
    std::cout << request.to_bytes().data() << std::endl;
    
    return response;
}

int main( int, char** )
try
{
    Settings settings;
    settings.set_port( 1984 );
    settings.set_root( "resources" );

    Service service( settings );

    Resource resource;
    resource.set_path( "events/{type: [a-z]*}/{id: [0-9]*}" );
    resource.set_header_filter( "Content-Type", "application/.*" );
    resource.set_method_handler( "GET", &get_handler );

    std::cout << "path: " << resource.get_path( ) << std::endl;

    service.publish( resource );

    service.start( );

    std::cout << "out of start!" << std::endl;

    return EXIT_SUCCESS;
}
catch ( const std::exception& ex )
{
    std::cout << "restbed failed: " << ex.what( ) << std::endl;

    return EXIT_FAILURE;
}