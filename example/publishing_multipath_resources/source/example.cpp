/*
 * Example illustrating multi-path resources.
 *
 * Server Usage:
 *    ./distribution/example/publishing_multipath_resources
 *
 * Client Usage:
 *    curl -w'\n' -v 'http://localhost:1984/messages'
 *    curl -w'\n' -v 'http://localhost:1984/queues/12/messages'
 */

#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session > session )
{
    session->close( OK, "Hello, World!", { { "Content-Length", "13" } } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_paths( { "/messages", "/queues/{id: [0-9]*}/messages" } );
    resource->set_method_handler( "GET", get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    Service service;
    service.publish( resource );
    service.start( settings );
    
    return EXIT_SUCCESS;
}
