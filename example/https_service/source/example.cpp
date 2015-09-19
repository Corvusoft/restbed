/*
 * Example illustrating HTTPS service.
 *
 * Create Certificate
 *    cd /tmp
 *    openssl genrsa -out server.key 1024
 *    openssl req -new -key server.key -out server.csr
 *    openssl x509 -req -days 3650 -in server.csr -signkey server.key -out server.crt
 *    openssl dhparam -out dh768.pem 768
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

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session > session )
{
    session->close( OK, "Hello, World!", { { "Content-Length", "13" }, { "Connection", "close" } } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_method_handler );
    
    auto ssl_settings = make_shared< SSLSettings >( );
    ssl_settings->set_http_disabled( true );
    ssl_settings->set_private_key( Uri( "file:///tmp/server.key" ) );
    ssl_settings->set_certificate( Uri( "file:///tmp/server.crt" ) );
    ssl_settings->set_temporary_diffie_hellman( Uri( "file:///tmp/dh768.pem" ) );
    
    auto settings = make_shared< Settings >( );
    settings->set_ssl_settings( ssl_settings );
    
    Service service;
    service.publish( resource );
    service.start( settings );
    
    return EXIT_SUCCESS;
}
