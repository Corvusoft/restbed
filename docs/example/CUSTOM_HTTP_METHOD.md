Overview
--------

"One of the fundamental constraints of HTTP and the central design feature of REST is a uniform interface provided by (among other things) a small, fixed set of methods that apply universally to all resources. The uniform interface constraint has a number of upsides and downsides." -- [StackExchange](https://softwareengineering.stackexchange.com/questions/193821/are-there-any-problems-with-implementing-custom-http-methods)

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

> $ clang++ -o example example.cpp -l restbed

Execution
---------

> $ ./example
>
> $ curl -w'\n' -v -X NOP 'http://localhost:1984/resource'
