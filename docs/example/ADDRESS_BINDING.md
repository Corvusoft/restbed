Overview
--------

"Each network interface on a host typically has a unique IP address. Sockets with wildcard local addresses can receive messages directed to the specified port number and sent to any of the possible addresses assigned to a host. For example, if a host has two interfaces with addresses 128.32.0.4 and 10.0.0.78, and a socket is bound as in Example 2-17, the process can accept connection requests addressed to 128.32.0.4 or 10.0.0.78. To allow only hosts on a specific network to connect to it, a server binds the address of the interface on the appropriate network." -- [Oracle](https://docs.oracle.com/cd/E19455-01/806-1017/sockets-47146/index.html)

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

> $ clang++ -o example example.cpp -l restbed

Execution
---------

> $ ./example
>
> $ curl -w'\n' -v -XGET 'http://127.0.0.1:1984/resource'
