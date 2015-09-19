/*
 * Example illustrating custom HTTP status codes.
 *
 * Server Usage:
 *    ./distribution/example/custom_status_codes
 *
 * Client Usage:
 *    curl -w'\n' -v -X GET 'http://localhost:1984/resource'
 */

#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session > session )
{
    session->close( 418 );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    settings->set_status_message( 418, "I'm a teapot" );
    
    Service service;
    service.publish( resource );
    service.start( settings );
    
    return EXIT_SUCCESS;
}
