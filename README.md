# restbed

----------

> "It's akin to embedding NGINX into your companies own product line"
>  -- Solutions Architect, Bellrock Technology

## Features

 - HTTP 1.1 compliance
 - Asynchronous single threaded architecture
 - Path Parameters
 - Request filters
 - Custom Logging
 - Service & Resource level authentication
 - Service & Resource level error handling
 - Long Polling
 - Web Sockets

## Example


```
#!c++

#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session >& session )
{
    session->close( OK, "Hello, World!", { { "Content-Length", "13" } } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", &get_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( resource );
    service.start( settings );
    
    return EXIT_SUCCESS;
}
```


## License


## Support

| Install Base   |        Tickets      |      Anual Fee (inc vat)  |
| :------------: |:-------------------:|:-------------------------:| 
|     1-4      |          3          |         £1600             | 
|     5-10     |          3          |         £12               |
|     11+      |          3+         |         £1                |

purchase here or contact sales@corvusoft.co.uk for further information.

## Build

build instruction including how to install in an alternative directory.
cmake -DCMAKE_INSTALL_PREFIX=/tmp ..

ctest -N
ctest -R 'test name'

option to statically link the framework to reduce size further.

Please submit all enhancements, proposals, and issues via the issue tracker.

## Road Map