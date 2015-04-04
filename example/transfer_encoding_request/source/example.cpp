#include <string>
#include <cstdlib>

#include "restbed"

using namespace std;
using namespace restbed;

Response post_method_handler( const Request& request )
{
    Response response;
    response.set_status_code( StatusCode::BAD_REQUEST );

    if ( request.has_header( "Transfer-Encoding" ) )
    {
        const auto header = request.get_header( "Transfer-Encoding" );

        if ( header == "chunked" )
        {
            framework::Bytes body = request.get_body( "\r\n" );
            auto chunk_size = stoul( string( body.begin( ), body.end( ) ), nullptr, 16 );

            while ( chunk_size not_eq 0 )
            {
                body = request.get_body( chunk_size + strlen( "\r\n" ) );
                fprintf( stdout, "Partial Body Content: %.*s", ( int )body.size( ), body.data( ) );

                body = request.get_body( "\r\n" );
                chunk_size = stoul( string( body.begin( ), body.end( ) ), nullptr, 16 );
            }

            response.set_status_code( StatusCode::OK );
        }
        //else 400 Bad Request
    }
    else if ( request.has_header( "Content-Length" ) )
    {
        framework::Bytes body = request.get_body( );

        fprintf( stderr, "Complete Body Content: %.*s\n", ( int )body.size( ), body.data( ) );

        response.set_body( body );
        response.set_status_code( StatusCode::OK );
    }
    //else 400 Bad Request
    
    return response;
}

int main( const int, const char** )
{
    Resource resource;
    resource.set_path( "/resources/item" );
    resource.set_method_handler( "POST", &post_method_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    
    Service service( settings );
    service.publish( resource );
    service.start( );
    
    return EXIT_SUCCESS;
}
