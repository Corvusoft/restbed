#include <regex>
#include <string>
#include <cstdlib>

#include "restbed"

using namespace std;
using namespace restbed;

string build_authenticate_header( void )
{
    string header = "Digest realm=\"Restbed\",";
    header += "algorithm=\"MD5\",";
    header += "stale=false,";
    header += "opaque=\"0000000000000000\",";
    header += "nonce=\"Ny8yLzIwMDIgMzoyNjoyNCBQTQ\"";
    
    return header;
}

void authentication_handler( const Request& request, /*out*/ Response& response )
{
    if ( request.has_header( "Authorization" ) )
    {
        auto authorisation = request.get_header( "Authorization" );
        
        bool authorised = regex_match( authorisation, regex( ".*response=\"02863beb15feb659dfe4703d610d1b73\".*" ) );
        
        if ( authorised )
        {
            response.set_status_code( 200 );
        }
        else
        {
            response.set_status_code( 401 );
        }
    }
    else
    {
        response.set_status_code( 401 );
        response.set_header( "WWW-Authenticate", build_authenticate_header( ) );
    }
}

Response get_method_handler( const Request& )
{
    Response response;
    response.set_body( "Password Protected Hello, World!" );
    response.set_status_code( StatusCode::OK );
    
    return response;
}

int main( int, char** )
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
