Overview
--------

"A web service is a service offered by an electronic device to another electronic device, communicating with each other via the World Wide Web. In a web service, the Web technology such as HTTP—originally designed for human-to-machine communication—is utilized for machine-to-machine communication, more specifically for transferring machine-readable file formats such as XML and JSON." -- [Wikipedia](https://en.wikipedia.org/wiki/Web_service)

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
        fprintf( stdout, "%.*s\n", ( int ) body.size( ), body.data( ) );
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

> $ clang++ -o example example.cpp -l restbed

Execution
---------

> $ ./example
>
> $ curl -w'\n' -v -X POST --data 'Hello, Restbed' 'http://localhost/resource'
