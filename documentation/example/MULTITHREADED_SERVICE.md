Overview
--------

"In computer architecture, multithreading is the ability of a central processing unit (CPU) or a single core in a multi-core processor to execute multiple processes or threads concurrently, appropriately supported by the operating system." -- [Wikipedia](https://en.wikipedia.org/wiki/Multithreading_(computer_architecture))

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
    auto body = String::format( "Hello From Thread %s\n", id.str( ).data( ) );
    
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

> $ clang++ -o example example.cpp -l restbed

Execution
---------

> $ ./example
>
> $ curl -w'\n' -v -X GET 'http://localhost:1984/resource'
