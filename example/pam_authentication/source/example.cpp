#include <string>
#include <utility>
#include <cstdlib>
#include "pam.h"
#include "base64.h"

#include "restbed"

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

void authentication_handler( const Request& request, /*out*/ Response& response )
{
    auto credentials = decode_header( request.get_header( "Authorization" ) );

    if ( pam_authorisation( credentials.first, credentials.second ) )
    {
        response.set_status_code( 200 );
    }
    else
    {
        response.set_status_code( 401 );
        response.set_header( "WWW-Authenticate", "Basic realm=\"Restbed\"" );
    }
}

Response get_method_handler( const Request& )
{
    Response response;
    response.set_body( "Password Protected Hello, World!" );
    response.set_status_code( StatusCode::OK );
    
    return response;
}

int main( const int, const char** )
{
    Resource resource;
    resource.set_path( "/resource" );
    resource.set_method_handler( "GET", &get_method_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    
    Service service( settings );
    service.set_authentication_handler( &authentication_handler );
    service.publish( resource );
    service.start( );
    
    return EXIT_SUCCESS;
}
