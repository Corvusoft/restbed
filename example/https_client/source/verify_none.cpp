/*
 * Example illustrating a HTTPS client with no peer verification.
 *
 * Usage:
 *    ./distribution/example/https_client_verify_none
 */

#include <memory>
#include <cstdio>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

int main( const int, const char** )
{
    auto request = make_shared< Request >( Uri( "https://www.google.co.nz/" ) );
    request->set_header( "Accept", "*/*" );
    request->set_header( "Host", "www.google.co.nz" );
    request->set_query_parameter( "query", "search term" );

    auto response = Http::sync( request );

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
