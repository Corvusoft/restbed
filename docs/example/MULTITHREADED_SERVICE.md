Overview
--------

Multithreading in computer architecture is the ability of a CPU (or a single core in a multi-core processor) to execute multiple threads or processes at the same time.

In essence, it’s a way for a processor to do more work simultaneously without needing additional cores.

Example
-------

```C++
#include <memory>
#include <thread>
#include <cstdlib>
#include <restbed>
#include <sstream>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session > session )
{
    stringstream id;
    id << ::this_thread::get_id( );
    auto body = "Hello From Thread " + id.str( ) + "\n";

    session->close( OK, body, { { "Content-Length", ::to_string( body.length( ) ) } } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_worker_limit( 4 );
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
> $ curl -w'\n' -v -X GET 'http://localhost:1984/resource'
