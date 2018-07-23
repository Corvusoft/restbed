Restbed [![Unix Build Status](https://travis-ci.org/Corvusoft/restbed.svg?branch=master)](https://travis-ci.org/Corvusoft/restbed)
[![Windows Build Status](https://ci.appveyor.com/api/projects/status/75wqogaks13xp817/branch/master?svg=true)](https://ci.appveyor.com/project/corvusoft/restbed/branch/master)
=============================================================================================================================

---

Restbed is a comprehensive and consistent programming model for building applications that require seamless and secure communication over HTTP, with the ability to model a range of business processes, designed to target mobile, tablet, desktop and embedded production environments.

> It's akin to embedding NGINX into your companies own product line. -- Solutions Architect, Bellrock Technology

Features
--------

| Feature                                                                                                                                                                                                       | Description                                                                                                                                                                                                                                                                                          |
|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [WebSockets](https://github.com/Corvusoft/restbed/blob/master/documentation/example/WEB_SOCKET.md)                                                                                                          | Full-duplex communication channels over a single TCP connection.                                                                                                                                                                                                                                     |
| [Server-Sent Events](https://github.com/Corvusoft/restbed/blob/master/documentation/example/SERVER_SIDE_EVENTS.md)                                                                                          | Server-Sent Events enables efficient server-to-client streaming of text-based event data—e.g., real-time notifications or updates generated on the server.                                                                                                                                           |
| [Comet](https://github.com/Corvusoft/restbed/blob/master/documentation/example/HTTP_PERSISTENT_CONNECTION.md)                                                                                                    | Long polling model to allow long-held HTTP requests for pushing data from the server to client.                                                                                                                                                                                                      |
| [SSL/TLS](https://github.com/Corvusoft/restbed/blob/master/documentation/example/HTTPS_SERVICE.md)                                                                                                          | Secure over the wire communication allowing you to transmit private data online.                                                                                                                                                                                                                     |
| [Session Management](https://github.com/Corvusoft/restbed/blob/master/documentation/example/SESSION_MANAGER.md)                                                                                             | Create custom HTTP session persistence and management logic.                                                                                                                                                                                                                                         |
| [HTTP Pipelining](https://github.com/Corvusoft/restbed/blob/master/documentation/example/HTTP_PIPELINING.md)                                                                                                | A technique allowing multiple HTTP requests to be sent on a single TCP connection without waiting for the corresponding responses.                                                                                                                                                                   |
| [Path Parameters](https://github.com/Corvusoft/restbed/blob/master/documentation/example/PATH_PARAMETERS.md)                                                                                                | Annotate URIs with custom path parameters such as resource keys, revisions, etc...                                                                                                                                                                                                                   |
| Query Parameters                                                                                                                                                                                              | Automated query parameter parsing.                                                                                                                                                                                                                                                                   |
| [Header Filters](https://github.com/Corvusoft/restbed/blob/master/documentation/example/RESOURCE_FILTERING.md)                                                                                              | Filter incoming HTTP requests by headers.                                                                                                                                                                                                                                                            |
| [Logging](https://github.com/Corvusoft/restbed/blob/master/documentation/example/LOGGING.md)                                                                                                                | Customise how and where log entries are created.                                                                                                                                                                                                                                                     |
| [Multi-Path Resources](https://github.com/Corvusoft/restbed/blob/master/documentation/example/MULTIPATH_RESOURCES.md)                                                                            | Give a resource multiple paths for improved readability.                                                                                                                                                                                                                                             |
| [Customisable Methods](https://github.com/Corvusoft/restbed/blob/master/documentation/example/CUSTOM_HTTP_METHOD.md)                                                                                            | Add your own custom HTTP methods.                                                                                                                                                                                                                                                                    |
| [Compression](https://github.com/Corvusoft/restbed/blob/master/documentation/example/COMPRESSION.md)                                                                                                        | Adaptability to address any form of compression GZip, Deflate, etc...                                                                                                                                                                                                                                |
| Encoding                                                                                                                                                                                                      | Adaptability to address any form of encoding UTF-32, ASCII, etc...                                                                                                                                                                                                                                   |
| [Rules Engine](https://github.com/Corvusoft/restbed/blob/master/documentation/example/RULES_ENGINE.md)                                                                                                      | Reduce complexity by processing incoming requests with readable units of code.                                                                                                                                                                                                                       |
| [HTTP](https://github.com/Corvusoft/restbed/blob/master/documentation/example/HTTP_CLIENT.md)/[HTTPS](https://github.com/Corvusoft/restbed/blob/master/example/https_client/source/verify_none.cpp) | Built in client capabilities with optional SSL peer certificate verification. Deprecated                                                                                                                                                                                                                       |
| IPv4/IPv6                                                                                                                                                                                                     | Internet Protocol Version 4/6 Network Support.                                                                                                                                                                                                                                                       |
| Architecture                                                                                                                                                                                                  | Asynchronous [single](https://github.com/Corvusoft/restbed/blob/master/example/publishing_resources/source/example.cpp) or [multi-threaded](https://github.com/Corvusoft/restbed/blob/master/documentation/example/MULTITHREADED_SERVICE.md) architecture, capable of addressing the C10K problem. |
| Converters                                                                                                                                                                                                    | Built-in Path, Query, and Header conversions for primary data-types.                                                                                                                                                                                                                                 |
| [Authentication](https://github.com/Corvusoft/restbed/blob/master/documentation/example/DIGEST_AUTHENTICATION.md)                                                                                                  | Separate Service and/or Resource level authentication.                                                                                                                                                                                                                                               |
| [Error Handling](https://github.com/Corvusoft/restbed/blob/master/documentation/example/ERROR_HANDLING.md)                                                                                                  | Separate Service and/or Resource level error handling.                                                                                                                                                                                                                                               |
| [Address Binding](https://github.com/Corvusoft/restbed/blob/master/documentation/example/ADDRESS_BINDING.md)                                                                                           | Bind HTTP and/or HTTPS services to separate IP addresses.                                                                                                                                                                                                                                            |
| [Signal Handling](https://github.com/Corvusoft/restbed/blob/master/documentation/example/SIGNAL_HANDLING.md)                                                                                                | Capture OS generated process signals.                                                                                                                                                                                                                                                                |
| [Documentation](https://github.com/Corvusoft/restbed/tree/master/documentation)                                                                                                                               | High-quality documentation covering the architecture and API.                                                                                                                                                                                                                                        |
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

    int content_length = request->get_header( "Content-Length", 0 );

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

More in-depth examples can be found [here](https://github.com/Corvusoft/restbed/tree/master/documentation/example). To see Restbed used in anger, please visit Corvusoft's [RestQ](https://github.com/corvusoft/restq) project.

License
-------

&copy; 2013-2018 Corvusoft Limited, United Kingdom. All rights reserved.

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
cmake [-DBUILD_SSL=NO] ..
make install
make test
```

You will now find all required components installed in the distribution folder.

Please submit all enhancements, proposals, and defects via the [issue](http://github.com/corvusoft/restbed/issues) tracker; Alternatively ask a question on [StackOverflow](http://stackoverflow.com/questions/ask) tagged [#restbed](http://stackoverflow.com/questions/tagged/restbed).

For Microsoft Visual Studio instructions please see feature [#17](https://github.com/Corvusoft/restbed/issues/17).

Documentation
-------------

This codebase is intended to be as self documenting as possible. We have supplied many [examples](https://github.com/Corvusoft/restbed/tree/master/documentation/example) and [test suites](https://github.com/corvusoft/restbed/tree/master/test) to help aid developers.

You can locate the latest design and API documentation [here](https://github.com/Corvusoft/restbed/tree/master/documentation).

Minimum Requirements
--------------------

| Resource | Requirement                                     |
|:--------:|:-----------------------------------------------:|
| Compiler |            C++11 compliant or above             |
|    OS    | BSD, Linux, Mac OSX, Windows, Raspbian          |

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
|             [4.5](https://github.com/Corvusoft/restbed/milestones/4.5)              |            API Documentation            |  complete   |
|             [4.5](https://github.com/Corvusoft/restbed/milestones/4.5)              |               Web Sockets               |  complete   |
|             [5.0](https://github.com/Corvusoft/restbed/milestones/5.0)              |      Client-side SSL certificates       | development |
|             [5.0](https://github.com/Corvusoft/restbed/milestones/5.0)              |            Resource Caching             | development |
|             [5.0](https://github.com/Corvusoft/restbed/milestones/5.0)              |          Runtime Modifications          | development |
|             [5.0](https://github.com/Corvusoft/restbed/milestones/5.0)              |            HTTP 2 compliance            | development |
|             [5.0](https://github.com/Corvusoft/restbed/milestones/5.0)              |         Refactor, Reduce, Reuse         |   pending   |

Contact
-------

| Method                                      | Description                                 |
|:--------------------------------------------|:--------------------------------------------|
| [Twitter](http://www.twitter.com/corvusoft) | Tweet us your questions & feature requests. |
| support@corvusoft.co.uk                     | Support related queries.                    |
| sales@corvusoft.co.uk                       | Sale related queries.                       |
