Restbed
=======

---

Restbed is a robust, enterprise-class framework for building server-side applications that demand secure, reliable, and scalable HTTP communication. It provides a flexible foundation for modeling complex business processes and is engineered to support deployment across mobile, tablet, desktop, and embedded environments.

> It's akin to embedding NGINX into your companies own product line. -- Solutions Architect, Bellrock Technology

Features
--------

| Feature                                                                                                                                                                                                       | Description                                                                                                                                                                                                                                                                                          |
|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [WebSockets](https://github.com/Corvusoft/restbed/blob/master/docs/example/WEB_SOCKET.md)                                                                                                            | Full-duplex communication channels over a single TCP connection.                                                                                                                                                                                                                                     |
| [Server-Sent Events](https://github.com/Corvusoft/restbed/blob/master/docs/example/SERVER_SIDE_EVENTS.md)                                                                                            | Server-Sent Events enables efficient server-to-client streaming of text-based event data—e.g., real-time notifications or updates generated on the server.                                                                                                                                           |
| [Comet](https://github.com/Corvusoft/restbed/blob/master/docs/example/HTTP_PERSISTENT_CONNECTION.md)                                                                                                 | Long polling model to allow long-held HTTP requests for pushing data from the server to client.                                                                                                                                                                                                      |
| [SSL/TLS](https://github.com/Corvusoft/restbed/blob/master/docs/example/HTTPS_SERVICE.md)                                                                                                            | Secure over the wire communication allowing you to transmit private data online.                                                                                                                                                                                                                     |
| [HTTP Pipelining](https://github.com/Corvusoft/restbed/blob/master/docs/example/HTTP_PIPELINING.md)                                                                                                  | A technique allowing multiple HTTP requests to be sent on a single TCP connection without waiting for the corresponding responses.                                                                                                                                                                   |
| [Path Parameters](https://github.com/Corvusoft/restbed/blob/master/docs/example/PATH_PARAMETERS.md)                                                                                                  | Annotate URIs with custom path parameters such as resource keys, revisions, etc...                                                                                                                                                                                                                   |
| Query Parameters                                                                                                                                                                                              | Automated query parameter parsing.                                                                                                                                                                                                                                                                   |
| [Logging](https://github.com/Corvusoft/restbed/blob/master/docs/example/LOGGING.md)                                                                                                                  | Customise how and where log entries are created.                                                                                                                                                                                                                                                     |
| [Multi-Path Resources](https://github.com/Corvusoft/restbed/blob/master/docs/example/MULTIPATH_RESOURCES.md)                                                                                         | Give a resource multiple paths for improved readability.                                                                                                                                                                                                                                             |
| [Customisable Methods](https://github.com/Corvusoft/restbed/blob/master/docs/example/CUSTOM_HTTP_METHOD.md)                                                                                          | Add your own custom HTTP methods.                                                                                                                                                                                                                                                                    |
| [Compression](https://github.com/Corvusoft/restbed/blob/master/docs/example/COMPRESSION.md)                                                                                                          | Adaptability to address any form of compression GZip, Deflate, etc...                                                                                                                                                                                                                                |
| Encoding                                                                                                                                                                                                      | Adaptability to address any form of encoding UTF-32, ASCII, etc...                                                                                                                                                                                                                                   |                                                                                                                                                                                                                   |
| IPv4/IPv6                                                                                                                                                                                                     | Internet Protocol Version 4/6 Network Support.                                                                                                                                                                                                                                                       |
| Architecture                                                                                                                                                                                                  | Asynchronous [single](https://github.com/Corvusoft/restbed/blob/master/example/publishing_resources/source/example.cpp) or [multi-threaded](https://github.com/Corvusoft/restbed/blob/master/docs/example/MULTITHREADED_SERVICE.md) architecture, capable of addressing the C10K problem.   |
| Converters                                                                                                                                                                                                    | Built-in Path, Query, and Header conversions for primary data-types.                                                                                                                                                                                                                                 |
| [Authentication](https://github.com/Corvusoft/restbed/blob/master/docs/example/DIGEST_AUTHENTICATION.md)                                                                                             | Separate Service and/or Resource level authentication.                                                                                                                                                                                                                                               |
| [Error Handling](https://github.com/Corvusoft/restbed/blob/master/docs/example/ERROR_HANDLING.md)                                                                                                    | Separate Service and/or Resource level error handling.                                                                                                                                                                                                                                               |
| [Address Binding](https://github.com/Corvusoft/restbed/blob/master/docs/example/ADDRESS_BINDING.md)                                                                                                  | Bind HTTP and/or HTTPS services to separate IP addresses.                                                                                                                                                                                                                                            |
| [Signal Handling](https://github.com/Corvusoft/restbed/blob/master/docs/example/SIGNAL_HANDLING.md)                                                                                                  | Capture OS generated process signals.                                                                                                                                                                                                                                                                |
| [Documentation](https://github.com/Corvusoft/restbed/tree/master/documentation)                                                                                                                               | High-quality documentation covering the architecture and API.                                                                                                                                                                                                                                        |
| Compliance                                                                                                                                                                                                    | Flexibility to address HTTP 1.0/1.1+ compliance.                                                                                                                                                                                                                                                     |
| Mature                                                                                                                                                                                                        | Secure, Stable, and extensively tested since 2013.                                                                                                                                                                                                                                                   |
| Community                                                                                                                                                                                                     | Active, vibrant and energetic open source community.                                                                                                                                                                                                                                                 |
| Support                                                                                                                                                                                                       | Commercial support is available from [Corvusoft](http://www.corvusoft.com).                                                                                                                                                                                                                        |

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

More in-depth examples can be found in the [documentation](https://github.com/Corvusoft/restbed/tree/master/docs/example).

License
-------

&copy; 2013-2026 Corvusoft Limited, United Kingdom. All rights reserved.

The Restbed framework is dual licensed; See [LICENSE](LICENSE) for full details.

Support
-------

Please contact sales@corvusoft.com, for support and licensing options including bespoke software development, testing, design consultation, training, mentoring and code review.

Please submit all enhancements, proposals, and defects via the [issue](http://github.com/corvusoft/restbed/issues) tracker; Alternatively ask a question on [StackOverflow](http://stackoverflow.com/questions/ask) tagged [#restbed](http://stackoverflow.com/questions/tagged/restbed).

Prerequisites
-------------

[Catch2](https://github.com/catchorg/Catch2) is a modern, C++-native, test framework for unit-tests, TDD, BDD, and benchmarks.
```
git clone https://github.com/catchorg/Catch2.git
cd Catch2
mkdir build
cd build
cmake ..
make install
```

[Asio](https://think-async.com/Asio/) is a cross-platform C++ library for network and low-level I/O programming that provides developers with a consistent asynchronous model using a modern C++ approach.
```
git clone https://github.com/chriskohlhoff/asio
cd asio/asio
./autogen.sh
./configure
make install
```

[OpenSSL](https://www.openssl.org/) is a robust, commercial-grade, full-featured Open Source Toolkit for the TLS (formerly SSL), DTLS and QUIC protocols.
```
git clone https://github.com/openssl/openssl.git
cd openssl
./config
make install
```

Build
-----

```bash
git clone https://github.com/corvusoft/restbed.git
cd restbed
mkdir restbed/build
cd restbed/build
cmake [-DBUILD_SSL=NO] [-DBUILD_TESTS=NO] ..
make install
make test
```

You will now find all required components installed in the distribution sub-folder.

Build Options
-------------

| Option               | Description                                | Default  |
| :------------------- | :----------------------------------------- | :------: |
| BUILD_SSL            | Enable SSL/TLS support.                    | Enabled  |
| BUILD_IPC            | Enable Unix domain sockets.                | Disabled |
| BUILD_TESTS          | Build project test suites.                 | Enabled  |
| BUILD_DEVEL_PACKAGE  | Install headers into CMAKE_INSTALL_PREFIX. | Enabled  |
| BUILD_SHARED_LIBRARY | Produce a shared build of restbed.         | Enabled  |
| BUILD_STATIC_LIBRARY | Produce a static build of restbed.         | Enabled  |

Windows Build Instructions
--------------------------

Prerequisites: Visual Studio 2022, CMake, GIT, Perl.

Using the x64 Native Tools Command Prompt begin by, if required, building OpenSSL.
```cmd
git clone --recursive https://github.com/openssl/openssl.git

cd openssl
perl Configure [no-]shared
nmake
nmake test
```

If you selected to use the default OpenSSL build (shared), you'll need to include the installation path in your environment.

```cmd
set PATH=openssl;%PATH%
```

If you selected to use the static OpenSSL build (no-shared), you'll need to include additional dependencies when linking your application code; See [OpenSSL project](https://github.com/openssl/openssl/pull/1062/files) for futher details.

```cmd
target_link_libraries( my_microservice restbed-static.lib ws2_32.lib advapi32.lib crypt32.lib gdi32.lib user32.lib )
```

Now proceed with the following Restbed build instructions.

```cmd
git clone --recursive https://github.com/corvusoft/restbed.git

mkdir restbed\build
cd restbed\build
cmake -G "Visual Studio 17 2022" [-DBUILD_SSL=NO] [-DBUILD_TESTS=NO] ..
cmake --build . --target ALL_BUILD --config Release
ctest
```

For Microsoft Visual Studio 14 2015 instructions, and further details, please see feature [#17](https://github.com/Corvusoft/restbed/issues/17).

Documentation
-------------

This codebase is intended to be as self documenting as possible. We have supplied many [examples](https://github.com/Corvusoft/restbed/tree/master/docs/example) and [test suites](https://github.com/corvusoft/restbed/tree/master/test) to help aid developers.

You can locate the latest design and API documentation [here](https://github.com/Corvusoft/restbed/tree/master/documentation).

Minimum Requirements
--------------------

| Resource | Requirement                                     |
|:--------:|:-----------------------------------------------:|
| Compiler |            C++23 compliant or above             |
|    OS    |         BSD, Linux, Mac OSX, Windows            |

Contact
-------

| Method                                      | Description                                 |
|:--------------------------------------------|:--------------------------------------------|
| support@corvusoft.com                       | Support related queries.                    |
| sales@corvusoft.com                         | Sale related queries.                       |
