#include <string>
#include <memory>
#include <cstdlib>
#include <restbed>
#include <framework>

using namespace std;
using namespace restbed;
using namespace framework;

void post_method_handler( const shared_ptr< Session >& );
void read_chunk( const shared_ptr< Session >&, const shared_ptr< Bytes >& );
void read_chunk_size( const shared_ptr< Session >&, const shared_ptr< Bytes >& );

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources" );
    resource->set_method_handler( "POST", &post_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( resource );
    service.start( settings );

    return EXIT_SUCCESS;
}

void post_method_handler( const shared_ptr< Session >& session )
{
    const auto request = session->get_request( );

    if ( request->get_header( "Transfer-Encoding", &String::lowercase ) == "chunked" )
    {
        session->fetch( "\r\n", &read_chunk_size );
    }
    else if ( request->has_header( "Content-Length" ) )
    {
        int length = 0;
        request->get_header( "Content-Length", length );

        session->fetch( length, [ ]( const shared_ptr< Session >& session, const shared_ptr< Bytes >& )
        {
            const auto request = session->get_request( );
            const auto body = request->get_body( );

            fprintf( stdout, "Complete body content: %.*s\n", ( int )body->size( ), body->data( ) );
            session->close( OK );
        } );
    }
    else
    {
        session->close( BAD_REQUEST );
    }
}

void read_chunk_size( const shared_ptr< Session >& session, const shared_ptr< Bytes >& data )
{
    fprintf ( stderr, "chunk size read caled\n" );

    if ( data not_eq nullptr and not data->empty( ) )
    {
        string length( data->begin( ), data->end( ) );

        fprintf( stderr, "Data length: %s\n", length.data( ) );

        const auto chunk_size = stoul( length, nullptr, 16 );

        if ( chunk_size not_eq 0 )
        {
            session->fetch( chunk_size, &read_chunk );
            return;
        }
    }

    session->close( OK );

    const auto request = session->get_request( );
    auto body = request->get_body( );
    fprintf( stdout, "Complete body content: %.*s\n", ( int )body->size( ), body->data( ) );
}

void read_chunk( const shared_ptr< Session >& session, const shared_ptr< Bytes >& data )
{
    fprintf( stdout, "Partial body chunk: %lu bytes", data->size( ) );

    //if expect header yield

    session->fetch( "\r\n", &read_chunk_size );
}
