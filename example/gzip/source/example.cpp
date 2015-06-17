#include <map>
#include <memory>
#include <cstdlib>
#include <restbed>
#include <framework>

#include "miniz.h"

using namespace std;
using namespace restbed;
using namespace framework;

void unzip_method_handler( const shared_ptr< Session >& session )
{
    const auto request = session->get_request( );

    size_t content_length = 0;
    request->get_header( "Content-Length", content_length );

    session->fetch( content_length, [ request ]( const shared_ptr< Session >& session, const Bytes& body )
    {
        Bytes result = body;

        if ( request->get_header( "Content-Encoding", String::lowercase ) == "gzip" )
        {
            size_t length = body.size( );
            unsigned char* data = new unsigned char[ length + 1 ];
            const int status = uncompress( data, &length, body.data( ), length );

            if ( status not_eq MZ_OK )
            {
                const auto message = String::format( "Failed to unzip: %s\n", mz_error( status ) );
                session->close( 400, message, { { "Content-Length", ::to_string( message.length( ) ) }, { "Content-Type", "text/plain" } } );
                delete[ ] data;
                return;
            }

            result = Bytes( data, data + length );
            delete[ ] data;
        }

        session->close( 200, result, { { "Content-Length", ::to_string( body.size( ) ) }, { "Content-Type", request->get_header( "Content-Type" ) } } );
    } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/api/unzip" );
    resource->set_method_handler( "POST", &unzip_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( resource );
    service.start( settings );
    
    return EXIT_SUCCESS;
}
