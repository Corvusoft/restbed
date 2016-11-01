/*
 * Example illustrating a HTTPS client with peer verification.
 *
 * 1. Download the certificate authority for the desired peer.
 *    You can find this information via 'openssl s_client -connect www.google.com:443 -showcerts'
 * 2. Test you have the correct certificate 'openssl s_client -connect www.google.com:443 -showcerts -CAfile Equifax_Secure_Certificate_Authority.pem'
 * 3. OpenSSL requires a link to the certiciate using the subject hash and a '.0' extension.
 *    The hash can be generated using 'openssl x509 -in Equifax_Secure_Certificate_Authority.pem -noout -subject_hash'
 * 4. ln -s Equifax_Secure_Certificate_Authority.pem 578d5c04.0
 * 5. Verify your setup 'openssl s_client -showcerts  -CApath ./DIRECTORY_WHERE_CERTFICIATE_LIVES -connect google.com:443'
 * 6. Make sure the file permissions are correct for the CA certificate
 *
 * Usage:
 *    ./distribution/example/https_client_verify_peer
 */

#include <memory>
#include <cstdio>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

int main( const int, const char** )
{
    auto request = make_shared< Request >( Uri( "https://www.google.com" ) );
    request->set_header( "Accept", "*/*" );
    request->set_header( "Host", "www.google.com" );
    request->set_query_parameter( "query", "search term" );

    auto ssl_settings = make_shared< SSLSettings >( );
    ssl_settings->set_certificate_authority_pool( Uri( "file://distribution/resource/certificates", Uri::Relative ) );

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
        auto length = response->get_header( "Content-Length", 0 );

        Http::fetch( length, response );
    }

    fprintf( stderr, "Body:           %.*s...\n", 3, response->get_body( ).data( ) );

    return EXIT_SUCCESS;
}
