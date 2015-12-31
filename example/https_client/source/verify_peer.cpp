/*
 * Example illustrating a HTTPS client with peer verification.
 *
 * Get CA certifiate (http://gagravarr.org/writing/openssl-certs/general.shtml)
 * note the subject hash never seems to match?!? use dtruss/strace to see what it wants to load. Its also more reliable
 * to download the certificate straight from the CA (for google.com its https://www.geotrust.com/resources/root-certificates/)
 *
 * http://stackoverflow.com/questions/23343910/verify-errornum-20-when-connecting-to-gateway-sandbox-push-apple-com
 * 1. openssl s_client -connect www.google.com:443 -showcerts
 * 2. download root CA
 * 3. test root CA, openssl s_client -connect www.google.com:443 -showcerts -CAfile ./certs/Equifax_Secure_Certificate_Authority.pem
 * Each file in the directory must contain a single certificate.
 * The files must be named using the subject name's hash and an extension of ".0".
 * 4. openssl x509 -in certs/Equifax_Secure_Certificate_Authority.pem -noout -subject_hash (also see c_rehash)
 * can be used to generate the subject name hash(e.g. e5d93f80). Just append ".0" to this value and create a softlink with this name(e5d93f80.0) to the CA file. If there are more than one CA files with same the subject name hash value, their extensions should be different(e.g. e5d93f80.1). The search is performed in the ordering of the extension number.
 * opensssl has introduced this technique to reduce the the CA file look up time. Otherwise openssl may have to read all files in the CApath to find the matching CA file.
 * 5. ln -s Equifax_Secure_Certificate_Authority.pem 594f1775.0
 * 6. verify its all setup correct, openssl s_client -showcerts  -CApath ./certs -connect google.com:443
 * 7. make sure the file permissions are correct for the CA root cert (http://stackoverflow.com/questions/15936668/boostasiosslcontextadd-verify-path)
 *
 * to confirm loading of the right hash use strace or dtruss (on mac) to verifiy the hash file being loaded.
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
    
    auto settings = make_shared< SSLSettings >( );
    settings->set_certificate_authority_pool( Uri( "file://distribution/resource/certificates", Uri::Relative ) );
    
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
