Overview
--------

HTTP compression improves transfer speed and reduces bandwidth use by compressing data before it is sent from the server to the client.

Browsers indicate which compression methods they support, and the server responds with a compatible compressed format. If a browser does not support compression, it receives uncompressed data.

Common compression methods include gzip and Deflate, with the complete list of supported schemes maintained by the Internet Assigned Numbers Authority (IANA).

Example
-------

```C++
#include <memory>
#include <cstdlib>
#include <ciso646>
#include <restbed>

#include <miniz/miniz.h>

using namespace std;
using namespace restbed;

void deflate_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );

    int content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes& body )
    {
        Bytes result = body;

        if ( request->get_header( "Content-Encoding" ) == "deflate" )
        {
            mz_ulong length = compressBound( static_cast< mz_ulong >( body.size( ) ) );
            unique_ptr< std::byte[ ] > data( new std::byte[ length ] );

            const int status = uncompress(
                ( unsigned char* )data.get( ),
                &length,
                ( const unsigned char* )body.data( ),
                static_cast< mz_ulong >( body.size( ) )
            );

            if ( status not_eq MZ_OK )
            {
                const auto message = "Failed to deflate: " + string( mz_error( status ) ) + "\n";
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
```

Build
-----

> $ git clone https://github.com/richgel999/miniz.git
> $ cd miniz
> $ mkdir build; cd build
> $ cmake -DBUILD_HEADER_ONLY=ON -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF ..
> $ make; sudo make install
>
> $ clang++ -std=c++20 -o example example.cpp -l restbed

Execution
---------

> $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
> $ ./example
>
> $ echo "Hello, World!" > test.data
> $ zlib-flate -compress < test.data > test.data.z
> $ curl -w'\n' -v -H"Content-Encoding: deflate" -X POST --data-binary @test.data.z 'http://localhost:1984/api/deflate'
