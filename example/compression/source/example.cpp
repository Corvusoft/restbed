/*
 * Example illustrating the use of deflate compression (RFC 1950-1952).
 *
 * Server Usage:
 *    ./distribution/example/compression
 *
 * Client Usage:
 *    curl -w'\n' -v -H"Content-Encoding: deflate" -X POST --data-binary @'distribution/resource/data.zlib' 'http://localhost:1984/api/deflate'
 */

#include <map>
#include <memory>
#include <cstdlib>
#include <ciso646>
#include <restbed>
#include "miniz_wrapper.h"

using namespace std;
using namespace restbed;

void deflate_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );

    int content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes & body )
    {
        Bytes result = body;

        if ( request->get_header( "Content-Encoding", String::lowercase ) == "deflate" )
        {
            mz_ulong length = compressBound( static_cast< mz_ulong >( body.size( ) ) );
            unique_ptr< unsigned char[ ] > data( new unsigned char[ length ] );
            const int status = uncompress( data.get( ), &length, body.data( ), static_cast< mz_ulong >( body.size( ) ) );

            if ( status not_eq MZ_OK )
            {
                const auto message = String::format( "Failed to deflate: %s\n", mz_error( status ) );
                session->close( 400, message, { { "Content-Length", ::to_string( message.length( ) ) }, { "Content-Type", "text/plain" } } );
                return;
            }

            result = Bytes( data.get( ), data.get( ) + length );
        }

        session->close( 200, result, { { "Content-Length", ::to_string( result.size( ) ) }, { "Content-Type", "text/plain" } } );
    } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/api/deflate" );
    resource->set_method_handler( "POST", deflate_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( resource );
    service.start( settings );

    return EXIT_SUCCESS;
}
