#include <string>
#include <memory>
#include <cstdlib>

#include "restbed"

using namespace std;
using namespace restbed;

Response get_method_handler( const Request& )
{
    Response response;
    response.set_status_code( StatusCode::OK );
    response.set_header( "Transfer-Encoding", "chunked" );
    response.set_body( [ ]( void ) -> framework::Bytes
    {
        string data = "";
        string chunk = "";
        static int count = 0;

        switch ( count++ )
        {
            case 0:
                data = "restbed";
                chunk = ::to_string( data.length( ) ) + "\r\n";
                chunk += data + "\r\n";
                break;
            case 1:
                data = " chunked\n";
                chunk = ::to_string( data.length( ) ) + "\r\n";
                chunk += data + "\r\n";
                break;
            case 2:
                chunk = "0\r\n\r\n";
                break;
            default:
                count = 0;
                chunk = "";
        }

        return framework::Bytes( chunk.begin( ), chunk.end( ) );
    } );

    return response;
}

int main( const int, const char** )
{
    Resource resource;
    resource.set_path( "/resources/item" );
    resource.set_method_handler( "GET", &get_method_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    
    Service service( settings );
    service.publish( resource );
    service.start( );
    
    return EXIT_SUCCESS;
}
