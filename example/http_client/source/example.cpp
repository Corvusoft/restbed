/*
 * Example illustrating HTTP client.
 *
 * Server Usage:
 *    sudo ./distribution/example/http_client
 */

#include <memory>
#include <cstdio>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

int main( const int, const char** )
{
    auto request = make_shared< Request >( );
    request->set_port( 80 );
    request->set_path( "/" );
    request->set_version( 1.1 );
    request->set_protocol( "HTTP" );
    request->set_host( "corvusoft.co.uk" );
    request->set_header( "Accept", "*/*" );
    request->set_header( "Host", "www.corvusoft.co.uk" );
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
    
    auto length = 0;
    response->get_header( "Content-Length", length );
    
    Http::fetch( length, response );
    
    fprintf( stderr, "Body:           %.*s...\n", 25, response->get_body( ).data( ) );
    
    return EXIT_SUCCESS;
}
