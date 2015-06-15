# restbed

----------

> "It's akin to embedding NGINX into your companies own product line."
>  -- Solutions Architect, Bellrock Technology

## Features

 - Asynchronous single threaded architecture
 - Path Parameters
 - Built-in HTTP Header, Path/Query parameter conversions
 - Request filters
 - Custom Logging
 - Service & Resource level authentication
 - Service & Resource level error handling
 - Customisable HTTP methods
 - Long Polling
 - Web Sockets
 - Secure, Stable, and extensively tested over 3+ years
 - Flexibility to address HTTP 1.0/1.1+ compliance
 - Active and vibrant community

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

Please contact support@corvusoft.co.uk, for support options including bespoke software development, design consultation, training, mentoring and code review.

| Install Base   |        Tickets      |      Anual Fee (inc vat)  |
| :------------: |:-------------------:|:-------------------------:| 
|     1-3      |          3          |         £280.00            | 
|     4-10     |          3          |         £360.00               |
|     11+      |          3+         |  contact sales@corvusoft.co.uk |

purchase here or contact sales@corvusoft.co.uk for further information.

Are you a start-up? Contact sales@corvusoft.co.uk for discounts.

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

Compiler:  C++11 compliant or above.
CPU: Single core
RAM:
Disk: 1MB maximum
OS: BSD, Linux, Mac OSX, Solaris, Windows, Raspbian

## Road Map

 - Statically Link Framework
0.0  - asynchronous HTTP service
1.0  - HTTP 1.0 compliance
2.0  - HTTP 1.1 compliance
2.5  - Secure Socket Layer
3.0  - Session Management
3.5  - Resource Caching
4.0  - Dynamic runtime resource publishing/suppression
x.x  - HTTP 2.0 compliance