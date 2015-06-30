/*
 * Example illustrating HTTPS service.
 *
 * Create Certificate
 *    cd /tmp
 *    openssl genrsa -out server.key 1024
 *    openssl req -new -key server.key -out server.csr
 *    openssl x509 -req -days 3650 -in server.csr -signkey server.key -out server.crt
 *    openssl dhparam -out dh512.pem 512
 *
 * Server Usage:
 *    sudo ./distribution/example/https_service
 *
 * Client Usage:
 *    curl -k -v -w'\n' -X GET 'https://localhost/resource'
 */

#include <memory>
#include <cstdlib>
#include <restbed>
#include <framework>

using namespace std;
using namespace restbed;
using namespace framework;

void get_method_handler( const shared_ptr< Session >& session )
{
    session->close( OK, "Hello, World!", { { "Content-Length", "13" }, { "Connection", "close" } } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_method_handler );

    auto settings = make_shared< SSLSettings >( );
    settings->set_private_key( Uri( "file:///tmp/server.key" ) );
    settings->set_certificate( Uri( "file:///tmp/server.crt" ) );
    settings->set_temporary_diffie_hellman( Uri( "file:///tmp/dh512.pem" ) );

    Service service;
    service.publish( resource );
    service.start( settings );
    
    return EXIT_SUCCESS;
}
