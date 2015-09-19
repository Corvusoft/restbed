/*
 * Example illustrating custom HTTP methods.
 *
 * Server Usage:
 *    ./distribution/example/custom_methods
 *
 * Client Usage:
 *    curl -w'\n' -v -X NOP 'http://localhost:1984/resource'
 */

#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void nop_method_handler( const shared_ptr< Session > session )
{
    session->close( 666 );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "NOP", nop_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    Service service;
    service.publish( resource );
    service.start( settings );
    
    return EXIT_SUCCESS;
}
