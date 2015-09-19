/*
 * Example illustrating PAM (Portable Authentication Module) authentication.
 *
 * Server Usage:
 *    ./distribution/example/pam_authentication
 *
 * Client Usage:
 *    curl -w'\n' -v -XGET 'http://<USERNAME>:<PASSWORD>@localhost:1984/resource'
 */

#include <string>
#include <memory>
#include <utility>
#include <cstdlib>
#include <restbed>

#include "pam.h"
#include "base64.h"

using namespace std;
using namespace restbed;

pair< string, string > decode_header( const string& value )
{
    auto data = base64_decode( value.substr( 6 ) );
    auto delimiter = data.find_first_of( ':' );
    auto username = data.substr( 0, delimiter );
    auto password = data.substr( delimiter + 1 );
    
    return make_pair( username, password );
}

void authentication_handler( const shared_ptr< Session > session,
                             const function< void ( const shared_ptr< Session > ) >& callback )
{
    const auto request = session->get_request( );
    const auto credentials = decode_header( request->get_header( "Authorization" ) );
    
    bool authorised = pam_authorisation( credentials.first, credentials.second );
    
    if ( not authorised )
    {
        session->close( UNAUTHORIZED, { { "WWW-Authenticate", "Basic realm=\"Restbed\"" } } );
    }
    else
    {
        callback( session );
    }
}

void get_method_handler( const shared_ptr< Session > session )
{
    session->close( OK, "Password Protected Hello, World!", { { "Content-Length", "32" } } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    Service service;
    service.publish( resource );
    service.set_authentication_handler( authentication_handler );
    
    service.start( settings );
    
    return EXIT_SUCCESS;
}
