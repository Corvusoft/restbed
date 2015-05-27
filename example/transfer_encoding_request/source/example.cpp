#include <string>
#include <memory>
#include <cstdlib>
#include <restbed>
#include <corvusoft/framework>

using namespace std;
using namespace restbed;
using namespace framework;

void read_chunk_size( const shared_ptr< Session >& session )
{
    const auto request = session->get_request( );

    string body = String::empty;
    request->get_body( body, "0" );

    const auto chunk_size = stoul( body, nullptr, 16 );

    if ( chunk_size not_eq 0 )
    {
        session->fetch( chunk_size, read_chunk );
    }

    session->close( OK );

    request->get_body( body );
    fprintf( "Complete body content: %.*s\n", body.size( ), body.data( ) );
}

void read_chunk( const shared_ptr< Session >& session )
{
    const auto request = session->get_request( );
    const Bytes body = request->get_body( );

    fprintf( stdout, "Partial body chunk: %lu bytes", body.size( ) );

    session->fetch( "\r\n", read_chunk_size );
}

void post_method_handler( const shared_ptr< Session >& session )
{
    const auto request = session->get_request( );

    if ( request->get_header( "Transfer-Encoding", String::lowercase ) == "chunked" )
    {
        session->fetch( "\r\n", &read_chunk_size );
    }
    else if ( request->has_header( "Content-Length" ) )
    {
        const auto length = 0;
        request->get_header( "Content-Length", length );

        session->fetch( length, [ ]( const shared_ptr< Session >& session )
        {
            const auto request = session->get_request( );
            const Bytes body = request.get_body( );

            fprintf( stderr, "Complete body content: %.*s\n", ( int )body.size( ), body.data( ) );
            session->close( OK, body );
        } );
    }
    else
    {
        session->close( BAD_REQUEST );
    }
}

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
