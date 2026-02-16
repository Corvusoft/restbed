Overview
--------

HTTP persistent connections (also called keep-alive or connection reuse) allow multiple HTTP request–response exchanges to occur over a single TCP connection, instead of creating a new connection for each request. This reduces latency and improves efficiency.

The newer HTTP/2 protocol extends this concept by enabling multiple concurrent requests and responses to be multiplexed over a single connection, further improving performance.

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

> $ clang++ -std=c++20 -o example example.cpp -l restbed

Execution
---------

> $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
> $ ./example
>
> $ curl -w'\n' -v 'http://localhost:1984/resources/persistent' 'http://localhost:1984/resources/intermittent'
