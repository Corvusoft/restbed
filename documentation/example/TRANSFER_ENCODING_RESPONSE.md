Overview
--------

"Chunked transfer encoding is a streaming data transfer mechanism available in version 1.1 of the Hypertext Transfer Protocol (HTTP). In chunked transfer encoding, the data stream is divided into a series of non-overlapping "chunks". The chunks are sent out and received independently of one another. No knowledge of the data stream outside the currently-being-processed chunk is necessary for both the sender and the receiver at any given time.

Each chunk is preceded by its size in bytes. The transmission ends when a zero-length chunk is received. The chunked keyword in the Transfer-Encoding header is used to indicate chunked transfer." -- [Wikipedia](https://en.wikipedia.org/wiki/Chunked_transfer_encoding)

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
        //pause to simulate backend processing.
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

> $ clang++ -o example example.cpp -l restbed

Execution
---------

> $ ./example
>
> $ curl -w'\n' -v -XGET 'http://localhost:1984/resources/item'
