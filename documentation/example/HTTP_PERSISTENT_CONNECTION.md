Overview
--------

"HTTP persistent connection, also called HTTP keep-alive, or HTTP connection reuse, is the idea of using a single TCP connection to send and receive multiple HTTP requests/responses, as opposed to opening a new connection for every single request/response pair. The newer HTTP/2 protocol uses the same idea and takes it further to allow multiple concurrent requests/responses to be multiplexed over a single connection." -- [Wikipedia](https://en.wikipedia.org/wiki/HTTP_persistent_connection)

Example
-------

```C++
#include <string>
#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_intermittent_method_handler( const shared_ptr< Session > session )
{
    session->close( OK, "intermittent resource request", { { "Content-Length", "29" }, { "Connection", "close" } } );
}

void get_persistent_method_handler( const shared_ptr< Session > session )
{
    session->yield( OK, "persistent resource request", { { "Content-Length", "27" }, { "Connection", "keep-alive" } } );
}

int main( const int, const char** )
{
    auto persistent = make_shared< Resource >( );
    persistent->set_path( "/resources/persistent" );
    persistent->set_method_handler( "GET", get_persistent_method_handler );
    
    auto intermittent = make_shared< Resource >( );
    intermittent->set_path( "/resources/intermittent" );
    intermittent->set_method_handler( "GET", get_intermittent_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    Service service;
    service.publish( persistent );
    service.publish( intermittent );
    
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
> $ curl -w'\n' -v 'http://localhost:1984/resources/persistent' 'http://localhost:1984/resources/intermittent'
