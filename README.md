# restbed

----------

> "It's akin to embedding NGINX into your companies own product line."
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
 - Extensively tested & developed over 3+ years

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

Find more examples [here](http://google.com)

## License

Copyright (c) 2013, 2014, 2015 Corvusoft Limited, United Kingdom. All rights reserved. 

The Restbed Framework is dual licensed; See LICENSE.md for full details.

## Support

| Install Base   |        Tickets      |      Anual Fee (inc vat)  |
| :------------: |:-------------------:|:-------------------------:| 
|     1-4      |          3          |         £1600             | 
|     5-10     |          3          |         £12               |
|     11+      |          3+         |         £1                |

purchase here or contact sales@corvusoft.co.uk for further information.

## Build


```
#!bash

git clone --recursive http://github.com/corvusoft/restbed.git
mkdir restbed/build
cd restbed/build
cmake [-DBUILD_TESTS=YES] [-DBUILD_EXAMPLES=YES] [-DCMAKE_INSTALL_PREFIX=/output-directory] ..
make install
make test
```


You will now find all required components installed in the restbed distribution folder.  Please submit all enhancements, proposals, and issues via the issue tracker.

## Minimum Requirements

## Road Map

 - Statically Link Framework