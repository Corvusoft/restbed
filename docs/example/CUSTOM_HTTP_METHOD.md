Overview
--------

A key constraint of HTTP and a core principle of REST is the uniform interface: a small, fixed set of methods applied consistently to all resources.

This standardisation simplifies system design and improves interoperability, but it can also limit flexibility in certain use cases.

Example
-------

```C++
#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void nop_method_handler( const shared_ptr< Session > session )
{
    session->close( 666 );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "NOP", nop_method_handler );

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
> $ curl -w'\n' -v -X NOP 'http://localhost:1984/resource'
