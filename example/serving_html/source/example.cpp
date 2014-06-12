#include <string>
#include <cstdlib>
#include <fstream>
#include <streambuf>

#include "restbed"

using namespace std;
using namespace restbed;

Response get_method_handler( const Request& request )
{
    string filename = request.get_path_parameter( "filename" );
    
    ifstream stream( "../../resource/" + filename, ifstream::in );
    
    Response response;
    response.set_header( "Content-Type", "text/html" );
    
    if ( stream.is_open( ) )
    {
        response.set_body( string( istreambuf_iterator< char >( stream ), istreambuf_iterator< char >( ) ) );
        response.set_status_code( StatusCode::OK );
    }
    else
    {
        response.set_status_code( StatusCode::NOT_FOUND );
    }
    
    return response;
}

int main( int, char** )
{
    Resource resource;
    resource.set_path( "/static/{filename: [a-z]*\\.html}" );
    resource.set_method_handler( "GET", &get_method_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    
    Service service( settings );
    service.publish( resource );
    service.start( );
    
    return EXIT_SUCCESS;
}
