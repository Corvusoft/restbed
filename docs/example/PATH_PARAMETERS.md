Overview
--------

A URI path parameter is a value included within a path segment of a URI, immediately following its name. Path parameters can control how a resource is represented, but since they cannot be modified by standard web forms, they must be constructed separately. Unlike query strings, path parameters are part of the URI path itself and are interpreted in sequence.

Example
-------

```C++
#include <string>
#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session > session )
{
    const auto& request = session->get_request( );

    const string body = "Hello, " + request->get_path_parameter( "name" );
    session->close( OK, body, { { "Content-Length", ::to_string( body.size( ) ) } } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource/{name: .*}" );
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
> $ curl -w'\n' -v -XGET 'http://localhost:1984/resource/<YOUR NAME HERE>'
