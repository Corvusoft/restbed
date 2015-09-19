/*
 * Example illustrating path parameters.
 *
 * Server Usage:
 *    ./distribution/example/path_parameters
 *
 * Client Usage:
 *    curl -w'\n' -v -XGET 'http://localhost:1984/resource/<YOUR NAME HERE>'
 */

#include <string>
#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session > session )
{
    const auto& request = session->get_request( );
    
    const string body = "Hello, " + request->get_path_parameter( "name" );
    session->close( OK, body, { { "Content-Length", ::to_string( body.size( ) ) } } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource/{name: .*}" );
    resource->set_method_handler( "GET", get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    Service service;
    service.publish( resource );
    service.start( settings );
    
    return EXIT_SUCCESS;
}
