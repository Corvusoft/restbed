Overview
--------

A web service is a service provided by one electronic device to another over the Web. It uses web technologies—most commonly HTTP—to enable machine-to-machine communication.

Although HTTP was originally designed for human-to-machine interaction, web services use it to exchange machine-readable data formats such as XML and JSON.

Example
-------

```C++
#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void post_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );

    size_t content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes & body )
    {
        fprintf( stdout, "%.*s\n", ( int ) body.size( ), ( const char* ) body.data( ) );
        session->close( OK, "Hello, World!", { { "Content-Length", "13" }, { "Connection", "close" } } );
    } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "POST", post_method_handler );

    Service service;
    service.publish( resource );
    service.start( );

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
> $ curl -w'\n' -v -X POST --data 'Hello, Restbed' 'http://localhost/resource'
