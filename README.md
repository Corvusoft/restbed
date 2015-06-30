# Restbed

[![Join the chat at https://gitter.im/Corvusoft/restbed](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/Corvusoft/restbed?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

----------

> It's akin to embedding NGINX into your companies own product line.
>                                                       -- Solutions Architect, Bellrock Technology

## Features

 - Long Polling
 - Path Parameters
 - Query Parameters
 - Request filters
 - Custom Logging
 - Multi-path resources
 - Customisable HTTP methods
 - Compression GZip, Deflate, etc...
 - IPv4/IPv6 Network Support
 - Asynchronous single threaded architecture
 - Built-in Path, Query, and Header conversions
 - Service & Resource level authentication
 - Service & Resource level error handling
 - Secure, Stable, and extensively tested over 3+ years
 - Flexibility to address HTTP 1.0/1.1+ compliance
 - Active, vibrant community

## Example

```C++
#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session >& session )
{
    const auto request = session->get_request( );

    size_t content_length = 0;
    request->get_header( "Content-Length", content_length );

    session->fetch( content_length, [ ]( const shared_ptr< Session >& session,
                                         const Bytes& body )
    {
        fprintf( stdout, "%.*s\n", ( int ) body.size( ), body.data( ) );

        session->close( OK, "Hello, World!", { { "Content-Length", "13" } } );
    } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( resource );
    service.start( settings );
    
    return EXIT_SUCCESS;
}
```

More in-depth examples can be found [here](https://github.com/Corvusoft/restbed/tree/master/example).

## License

Copyright (c) 2013, 2014, 2015 Corvusoft Limited, United Kingdom. All rights reserved. 

The Restbed Framework is dual licensed; See LICENSE.md for full details.

## Support

Please contact sales@corvusoft.co.uk, for support options including bespoke software development, design consultation, training, mentoring and code review.

| Install Base   |        Tickets      |   Anual Fee Per Install (ex vat @20%)   |
| :------------: |:-------------------:|:---------------------------------------:| 
|     1-3        |          3          |                £280.00                  | 
|     4-10       |          3          |                £360.00                  |
|     11+        |          3+         |                 AABUS                   |                

purchase by contacting sales@corvusoft.co.uk for further information.

Are you a start-up?
Contact sales@corvusoft.co.uk for discounts.

## Build


```bash
git clone --recursive https://github.com/corvusoft/restbed.git
mkdir restbed/build
cd restbed/build
cmake [-DBUILD_TESTS=YES] [-DBUILD_EXAMPLES=YES] [-DCMAKE_INSTALL_PREFIX=/output-directory] ..
make install
make test
```

You will now find all required components installed in the restbed distribution folder.  Please submit all enhancements, proposals, and defects via the [issue](http://github.com/corvusoft/restbed/issues) tracker.

## Minimum Requirements

|     Resource   |                   Requirement                   |
|:--------------:|:-----------------------------------------------:| 
|       CPU      |                    40mhz                        |
|       RAM      |                     3mb                         |
|       Disk     |                     1mb                         |
|     Compiler   |          C++11 compliant or above               |
|        OS      | BSD, Linux, Mac OSX, Solaris, Windows, Raspbian |

## Road Map

|   MileStone   |                   Feature                       |      Status     |
|:-------------:|:-----------------------------------------------:|:---------------:| 
|     0.0       |         Asynchrounous HTTP Service              |     complete    |
|     1.0       |             HTTP 1.0 Compliance                 |     complete    |
|     2.0       |             HTTP 1.1 Compliance                 |     complete    |
|     2.5       |             Secure Socket Layer                 |        90%      |
|     2.5       |     Simultaneous Network Ports (HTTP/HTTPS)     |        99%      |
|     3.0       |                 Rules Engine                    |     pending     |
|     3.5       |             Session Management                  |     pending     |
|     3.6       |               Resource Caching                  |     pending     |
|     4.0       |                 Event Hooks                     |     pending     |
|     4.5       |                 Web Sockets                     |     pending     |
|     5.0       |             HTTP 2.0 compliance                 |     pending     |
|     5.x       | Dynamic runtime resource publishing/suppression |     pending     |
|     x.x       |         Statically Linked Framework             |     pending     |
|     x.x       |                 Localisation                    |     pending     |
