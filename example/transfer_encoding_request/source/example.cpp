/*
 * Example illustrating Transfer-Encoding request processing.
 *
 * Server Usage:
 *    ./distribution/example/transfer_encoding_request
 *
 * Client Usage:
 *    curl -w'\n' -v -X POST --header "Transfer-Encoding: chunked" -d @distribution/resource/request.txt 'http://localhost:1984/resources'
 */

#include <string>
#include <memory>
#include <cstring>
#include <cstdlib>
#include <ciso646>
#include <iostream>
#include <restbed>

using namespace std;
using namespace restbed;

void post_method_handler( const shared_ptr< Session > );
void read_chunk( const shared_ptr< Session >, const Bytes& );
void read_chunk_size( const shared_ptr< Session >, const Bytes& );

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources" );
    resource->set_method_handler( "POST", post_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( resource );
    service.start( settings );

    return EXIT_SUCCESS;
}

void post_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );

    if ( request->get_header( "Transfer-Encoding", String::lowercase ) == "chunked" )
    {
        session->fetch( "\r\n", read_chunk_size );
    }
    else if ( request->has_header( "Content-Length" ) )
    {
        int length = request->get_header( "Content-Length", 0 );

        session->fetch( length, [ ]( const shared_ptr< Session > session, const Bytes& )
        {
            const auto request = session->get_request( );
            const auto body = request->get_body( );

            fprintf( stdout, "Complete body content: %.*s\n", static_cast< int >( body.size( ) ), body.data( ) );
            session->close( OK );
        } );
    }
    else
    {
        session->close( BAD_REQUEST );
    }
}

void read_chunk_size( const shared_ptr< Session > session, const Bytes& data )
{
    if ( not data.empty( ) )
    {
        const string length( data.begin( ), data.end( ) );

        if ( length not_eq "0\r\n" )
        {
            const auto chunk_size = stoul( length, nullptr, 16 ) + strlen( "\r\n" );
            session->fetch( chunk_size, read_chunk );
            return;
        }
    }

    session->close( OK );

    const auto request = session->get_request( );
    const auto body = request->get_body( );

    fprintf( stdout, "Complete body content: %.*s\n", static_cast< int >( body.size( ) ), body.data( ) );
}

void read_chunk( const shared_ptr< Session > session, const Bytes& data )
{
    cout << "Partial body chunk: " << data.size( ) << " bytes" << endl;

    session->fetch( "\r\n", read_chunk_size );
}
