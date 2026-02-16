Overview
--------

Each network interface on a host usually has a unique IP address. Sockets with wildcard local addresses can receive messages sent to any of the host's addresses on a specific port. For example, if a host has two interfaces with addresses 128.32.0.4 and 10.0.0.78, a socket bound to a wildcard address can accept connections on either. To restrict connections to a specific network, a server binds to the interface address of the desired network.

Example
-------

```C++
#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session > session )
{
    session->close( OK, "Hello, World!", { { "Content-Length", "13" } } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_bind_address( "127.0.0.1" );
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
> $ curl -w'\n' -v -XGET 'http://127.0.0.1:1984/resource'
