/*
 * Example illustrating a HTTPS client authentication
 *
 * 0. Generate a CA
 *    mkdir -p /tmp/ssl/{client,server,CA}
 *    openssl genrsa -out /tmp/ssl/CA/ca.key 4096 
 *    openssl req -x509 -new -nodes -key /tmp/ssl/CA/ca.key -sha256 -days 1024 -out /tmp/ssl/CA/ca.pem -subj '/C=US/ST=Oregon/L=Portland/CN=FAKE ROOT'
 *    ln -s /tmp/ssl/CA/ca.pem /tmp/ssl/CA/`openssl x509 -hash -in /tmp/ssl/CA/ca.pem -noout`.0
 *
 * 1. genereate key and certificate:
 *
 *    openssl req -nodes -new -newkey rsa:2048 -keyout /tmp/ssl/client/key.key -out /tmp/ssl/client/certificate.csr -subj '/C=US/ST=Oregon/L=Portland/CN=Client'
 *
 *    openssl req -nodes -new -newkey rsa:2048 -keyout /tmp/ssl/server/key.key -out /tmp/ssl/server/certificate.csr -subj '/C=US/ST=Oregon/L=Portland/CN=localhost'
 *
 *    openssl x509 -req -in /tmp/ssl/client/certificate.csr -CA /tmp/ssl/CA/ca.pem -CAkey /tmp/ssl/CA/ca.key -CAcreateserial -days 500 -sha256 -out /tmp/ssl/client/certificate.crt
 *
 *    openssl x509 -req -in /tmp/ssl/server/certificate.csr -CA /tmp/ssl/CA/ca.pem -CAkey /tmp/ssl/CA/ca.key -CAcreateserial -days 500 -sha256 -out /tmp/ssl/server/certificate.crt
 *
 *    openssl dhparam 2048 -out /tml/ssl/client/dhparam.pem -outform PEM
 * 
 *
 * 2. start openssl debug server
 *    openssl s_server -accept 8080 -www -cert /tmp/ssl/server/certificate.crt -key /tmp/ssl/server/key.key -CApath /tmp/ssl/CA/ -tls1 -verify 2
 *
 * Usage:
 *    ./distribution/example/https_client_authentication
 */

#include <memory>
#include <cstdio>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

int main( const int, const char** )
{
    auto request = make_shared< Request >( Uri( "https://localhost:8080" ) );
    request->set_header( "Accept", "*/*" );
    request->set_header( "Host", "localhost" );
    
    auto ssl_settings = make_shared< SSLSettings >( );
    ssl_settings->set_client_authentication_enabled( true );
    ssl_settings->set_private_key( Uri( "file:///tmp/ssl/client/key.key" ) );
    ssl_settings->set_certificate( Uri( "file:///tmp/ssl/client/certificate.crt" ) );
    ssl_settings->set_certificate_authority_pool( Uri( "file:///tmp/ssl/CA/" ) );
    
    auto settings = make_shared< Settings >( );
    settings->set_ssl_settings( ssl_settings );
    
    auto response = Http::sync( request, settings );
    
    fprintf( stderr, "*** Response ***\n" );
    fprintf( stderr, "Status Code:    %i\n", response->get_status_code( ) );
    fprintf( stderr, "Status Message: %s\n", response->get_status_message( ).data( ) );
    fprintf( stderr, "HTTP Version:   %.1f\n", response->get_version( ) );
    fprintf( stderr, "HTTP Protocol:  %s\n", response->get_protocol( ).data( ) );
    
    for ( const auto header : response->get_headers( ) )
    {
        fprintf( stderr, "Header '%s' > '%s'\n", header.first.data( ), header.second.data( ) );
    }
    
    if ( response->has_header( "Transfer-Encoding" ) )
    {
        Http::fetch( "\r\n", response );
    }
    else
    {
        auto length = 0;
        response->get_header( "Content-Length", length );
        
        Http::fetch( length, response );
    }
    
    fprintf( stderr, "Body:           %.*s...\n", 3, response->get_body( ).data( ) );
    
    return EXIT_SUCCESS;
}
