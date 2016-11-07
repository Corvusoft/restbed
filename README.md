Restbed [![Build Status](https://travis-ci.org/Corvusoft/restbed.svg?branch=master)](https://travis-ci.org/Corvusoft/restbed)
=============================================================================================================================

---

Restbed is a comprehensive and consistent programming model for building applications that require seamless and secure communication over HTTP, with the ability to model a range of business processes, designed to target mobile, tablet, desktop and embedded production environments.

> It's akin to embedding NGINX into your companies own product line. -- Solutions Architect, Bellrock Technology

Features
--------

| Feature                                                                                                                                                                                                       | Description                                                                                                                                                                                                                                                                                          |
|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [WebSockets](https://github.com/Corvusoft/restbed/blob/master/example/web_socket/source/example.cpp)                                                                                                          | Full-duplex communication channels over a single TCP connection.                                                                                                                                                                                                                                     |
| [Server-Side Events](https://github.com/Corvusoft/restbed/blob/master/example/server_sent_events/source/example.cpp)                                                                                          | Server-Sent Events enables efficient server-to-client streaming of text-based event data—e.g., real-time notifications or updates generated on the server.                                                                                                                                           |
| [Comet](https://github.com/Corvusoft/restbed/blob/master/example/persistent_connection/source/example.cpp)                                                                                                    | Long polling model to allow long-held HTTP requests for pushing data from the server to client.                                                                                                                                                                                                      |
| [SSL/TLS](https://github.com/Corvusoft/restbed/blob/master/example/https_service/source/example.cpp)                                                                                                          | Secure over the wire communication allowing you to transmit private data online.                                                                                                                                                                                                                     |
| [Session Management](https://github.com/Corvusoft/restbed/blob/master/example/session_manager/source/example.cpp)                                                                                             | Create custom HTTP session persistence and management logic.                                                                                                                                                                                                                                         |
| [Path Parameters](https://github.com/Corvusoft/restbed/blob/master/example/path_parameters/source/example.cpp)                                                                                                | Annotate URIs with custom path parameters such as resource keys, revisions, etc...                                                                                                                                                                                                                   |
| Query Parameters                                                                                                                                                                                              | Automated query parameter parsing.                                                                                                                                                                                                                                                                   |
| [Header Filters](https://github.com/Corvusoft/restbed/blob/master/example/resource_filtering/source/example.cpp)                                                                                              | Filter incoming HTTP requests by headers.                                                                                                                                                                                                                                                            |
| [Logging](https://github.com/Corvusoft/restbed/blob/master/example/logging/source/example.cpp)                                                                                                                | Customise how and where log entries are created.                                                                                                                                                                                                                                                     |
| [Multi-Path Resources](https://github.com/Corvusoft/restbed/blob/master/example/publishing_multipath_resources/source/example.cpp)                                                                            | Give a resource multiple paths for improved readability.                                                                                                                                                                                                                                             |
| [Customisable Methods](https://github.com/Corvusoft/restbed/blob/master/example/custom_methods/source/example.cpp)                                                                                            | Add your own custom HTTP methods.                                                                                                                                                                                                                                                                    |
| [Compression](https://github.com/Corvusoft/restbed/blob/master/example/compression/source/example.cpp)                                                                                                        | Adaptability to address any form of compression GZip, Deflate, etc...                                                                                                                                                                                                                                |
| Encoding                                                                                                                                                                                                      | Adaptability to address any form of encoding UTF-32, ASCII, etc...                                                                                                                                                                                                                                   |
| [Rules Engine](https://github.com/Corvusoft/restbed/blob/master/example/rules_engine/source/example.cpp)                                                                                                      | Reduce complexity by processing incoming requests with readable units of code.                                                                                                                                                                                                                       |
| [HTTP](https://github.com/Corvusoft/restbed/blob/master/example/http_client/source/example.cpp)/[HTTPS](https://github.com/Corvusoft/restbed/blob/master/example/https_client_verify_none/source/example.cpp) | Built in client capabilities with optional SSL peer certificate verification.                                                                                                                                                                                                                        |
| IPv4/IPv6                                                                                                                                                                                                     | Internet Protocol Version 4/6 Network Support.                                                                                                                                                                                                                                                       |
| Architecture                                                                                                                                                                                                  | Asynchronous [single](https://github.com/Corvusoft/restbed/blob/master/example/publishing_resources/source/example.cpp) or [multi-threaded](https://github.com/Corvusoft/restbed/blob/master/example/multithreaded_service/source/example.cpp) architecture, capable of addressing the C10K problem. |
| Converters                                                                                                                                                                                                    | Built-in Path, Query, and Header conversions for primary data-types.                                                                                                                                                                                                                                 |
| [Authentication](https://github.com/Corvusoft/restbed/blob/master/example/authentication/source/example.cpp)                                                                                                  | Separate Service and/or Resource level authentication.                                                                                                                                                                                                                                               |
| [Error Handling](https://github.com/Corvusoft/restbed/blob/master/example/error_handling/source/example.cpp)                                                                                                  | Separate Service and/or Resource level error handling.                                                                                                                                                                                                                                               |
| [Address Binding](https://github.com/Corvusoft/restbed/blob/master/example/bind_service_address/source/example.cpp)                                                                                           | Bind HTTP and/or HTTPS services to separate IP addresses.                                                                                                                                                                                                                                            |
| [Signal Handling](https://github.com/Corvusoft/restbed/blob/master/example/signal_handling/source/example.cpp)                                                                                                | Capture OS generated process signals.                                                                                                                                                                                                                                                                |
| Compliance                                                                                                                                                                                                    | Flexibility to address HTTP 1.0/1.1+ compliance.                                                                                                                                                                                                                                                     |
| Mature                                                                                                                                                                                                        | Secure, Stable, and extensively tested since 2013.                                                                                                                                                                                                                                                   |
| Community                                                                                                                                                                                                     | Active, vibrant and energetic open source community.                                                                                                                                                                                                                                                 |
| Support                                                                                                                                                                                                       | Commercial support is available from [Corvusoft](http://www.corvusoft.co.uk).                                                                                                                                                                                                                        |

Example
-------

```C++
#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void post_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );

    int content_length = 0;
    request->get_header( "Content-Length", content_length );

    session->fetch( content_length, [ ]( const shared_ptr< Session > session, const Bytes & body )
    {
        fprintf( stdout, "%.*s\n", ( int ) body.size( ), body.data( ) );
        session->close( OK, "Hello, World!", { { "Content-Length", "13" } } );
    } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "POST", post_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( resource );
    service.start( settings );

    return EXIT_SUCCESS;
}
```

More in-depth examples can be found [here](https://github.com/corvusoft/restbed/tree/master/example). To see Restbed used in anger, please visit Corvusoft's [RestQ](https://github.com/corvusoft/restq) project.

License
-------

&copy; 2013-2016 Corvusoft Limited, United Kingdom. All rights reserved.

The Restbed framework is dual licensed; See [LICENSE](LICENSE) for full details.

Support
-------

Please contact sales@corvusoft.co.uk, for support and licensing options including bespoke software development, testing, design consultation, training, mentoring and code review.

Build
-----

```bash
git clone --recursive https://github.com/corvusoft/restbed.git
mkdir restbed/build
cd restbed/build
cmake [-DBUILD_TESTS=YES] [-DBUILD_EXAMPLES=YES] [-DBUILD_SSL=NO] [-DBUILD_SHARED=YES] [-DCMAKE_INSTALL_PREFIX=/output-directory] ..
make [-j CPU_CORES+1] install
make test
```

You will now find all required components installed in the distribution folder.

Please submit all enhancements, proposals, and defects via the [issue](http://github.com/corvusoft/restbed/issues) tracker; Alternatively ask a question on [StackOverflow](http://stackoverflow.com/questions/ask) tagged [#restbed](http://stackoverflow.com/questions/tagged/restbed).

For Microsoft Visual Studio instructions please see feature [#17](https://github.com/Corvusoft/restbed/issues/17).

Documentation
-------------

This codebase is intended to be as self documenting as possible. We have supplied many [examples](https://github.com/corvusoft/restbed/tree/master/example) and [test suites](https://github.com/corvusoft/restbed/tree/master/test) to help aid developers.

We are currently working on textual API documentation, however it's subject to erratic and frequent alteration; you've been warned.

Minimum Requirements
--------------------

| Resource | Requirement                                     |
|:--------:|:-----------------------------------------------:|
| Compiler |            C++11 compliant or above             |
|    OS    | BSD, Linux, Mac OSX, Solaris, Windows, Raspbian |

Road Map
--------

| Milestone                                                                           | Feature                                 | Status      |
|:-----------------------------------------------------------------------------------:|:---------------------------------------:|:-----------:|
|                                         0.0                                         |        Asynchronous HTTP Service        |  complete   |
|                                         1.0                                         |           HTTP 1.0 Compliance           |  complete   |
|                                         2.0                                         |           HTTP 1.1 Compliance           |  complete   |
|                                         2.5                                         |           Secure Socket Layer           |  complete   |
|                                         2.5                                         | Simultaneous Network Ports (HTTP/HTTPS) |  complete   |
|                                         3.0                                         |              Rules Engine               |  complete   |
| [3.5](https://github.com/Corvusoft/restbed/issues?utf8=%E2%9C%93&q=milestone%3A3.5) |   Schedule Tasks on Service run-loop    |  complete   |
| [3.5](https://github.com/Corvusoft/restbed/issues?utf8=%E2%9C%93&q=milestone%3A3.5) |    Multi-Threaded service capability    |  complete   |
| [3.5](https://github.com/Corvusoft/restbed/issues?utf8=%E2%9C%93&q=milestone%3A3.5) |    Bind Service to specific Address     |  complete   |
| [3.5](https://github.com/Corvusoft/restbed/issues?utf8=%E2%9C%93&q=milestone%3A3.5) |           Session Management            |  complete   |
|             [4.0](https://github.com/Corvusoft/restbed/milestones/4.0)              |               HTTP Client               |  complete   |
|             [4.0](https://github.com/Corvusoft/restbed/milestones/4.0)              |             Signal Handling             |  complete   |
|             [4.5](https://github.com/Corvusoft/restbed/milestones/4.5)              |            API Documentation            | development |
|             [4.5](https://github.com/Corvusoft/restbed/milestones/4.5)              |               Web Sockets               |  complete   |
|             [5.0](https://github.com/Corvusoft/restbed/milestones/5.0)              |      Client-side SSL certificates       |   pending   |
|             [5.0](https://github.com/Corvusoft/restbed/milestones/5.0)              |            Resource Caching             |   pending   |
|             [5.0](https://github.com/Corvusoft/restbed/milestones/5.0)              |          Runtime Modifications          |   pending   |
|             [5.0](https://github.com/Corvusoft/restbed/milestones/5.0)              |            HTTP 2 compliance            |   pending   |
|             [5.0](https://github.com/Corvusoft/restbed/milestones/5.0)              |         Refactor, Reduce, Reuse         |   pending   |

Contact
-------

| Method                                      | Description                                 |
|:--------------------------------------------|:--------------------------------------------|
| [Twitter](http://www.twitter.com/corvusoft) | Tweet us your questions & feature requests. |
| support@corvusoft.co.uk                     | Support related queries.                    |
| sales@corvusoft.co.uk                       | Sale related queries.                       |
