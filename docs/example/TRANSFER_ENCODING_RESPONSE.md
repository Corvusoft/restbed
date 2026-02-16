Overview
--------

Chunked transfer encoding is a streaming data transfer mechanism introduced in HTTP/1.1. It allows data to be sent in a series of independent, non-overlapping "chunks" rather than as a single continuous block.

Each chunk is preceded by its size (in bytes), enabling the receiver to process data incrementally without knowing the total content length in advance. The transmission ends when a zero-length chunk is sent. The use of chunked transfer encoding is indicated by the `Transfer-Encoding: chunked` header.

Example
-------

```C++
#include <string>
#include <chrono>
#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session > session )
{
    session->yield( OK, "8\r\nrestbed \r\n", { { "Transfer-Encoding", "chunked" } }, [ ]( const shared_ptr< Session > session )
    {
        // Pause to simulate backend processing.
        session->sleep_for( chrono::milliseconds( 500 ), [ ]( const shared_ptr< Session > session )
        {
            session->yield( "10\r\nchunked encoding\r\n", [ ]( const shared_ptr< Session > session )
            {
                session->close( "0\r\n\r\n" );
            } );
        } );
    } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources/item" );
    resource->set_method_handler( "GET", get_method_handler );

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
> $ curl -w'\n' -v -XGET 'http://localhost:1984/resources/item'
