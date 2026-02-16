Overview
--------

Chunked transfer encoding is a streaming data transfer mechanism introduced in HTTP/1.1. It allows data to be sent in a series of independent, non-overlapping "chunks" rather than as a single continuous block.

Each chunk is preceded by its size (in bytes), enabling the receiver to process data incrementally without knowing the total content length in advance. The transmission ends when a zero-length chunk is sent. The use of chunked transfer encoding is indicated by the `Transfer-Encoding: chunked` header.

Example
-------

```C++
#include <string>
#include <memory>
#include <cstring>
#include <cstdlib>
#include <ciso646>
#include <iostream>
#include <restbed>

using namespace std;
using namespace restbed;

void read_chunk( const shared_ptr< Session > session, const Bytes& );

void read_chunk_size( const shared_ptr< Session > session, const Bytes& data )
{
    if ( not data.empty( ) )
    {
        const string length( (const char*)data.data( ), data.size( ) );

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

    fprintf( stdout, "Complete body content: %.*s\n", static_cast< int >( body.size( ) ), (const char*) body.data( ) );
}

void read_chunk( const shared_ptr< Session > session, const Bytes& data )
{
    cout << "Partial body chunk: " << data.size( ) << " bytes" << endl;

    session->fetch( "\r\n", read_chunk_size );
}

void post_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );

    if ( request->get_header( "Transfer-Encoding" ) == "chunked" )
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

            fprintf( stdout, "Complete body content: %.*s\n", static_cast< int >( body.size( ) ), (const char*) body.data( ) );
            session->close( OK );
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
    resource->set_method_handler( "POST", post_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( resource );
    service.start( settings );

    return EXIT_SUCCESS;
}
```

Build
-----

> $ clang++ -std=c++20 -o example example.cpp -l restbed

Execution
---------

> $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
> $ ./example
>
> $ echo "My really large file..." > bigfile.txt
> $ curl -w'\n' -v -X POST --header "Transfer-Encoding: chunked" -d @bigfile.txt 'http://localhost:1984/resources'
