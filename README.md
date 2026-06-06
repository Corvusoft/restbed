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

Please submit all enhancements, proposals, and defects via the [issue](http://github.com/corvusoft/restbed/issues) tracker.

Prerequisites
-------------

Restbed is built with GNU Autotools and depends on:

- A C++23 compiler (GCC >= 13, Clang >= 17, AppleClang >= 15)
- [Asio](https://think-async.com/Asio/) (standalone, header-only)
- [OpenSSL](https://www.openssl.org/) (optional — required when SSL/TLS support is enabled, on by default)
- [Catch2](https://github.com/catchorg/Catch2) >= 3.0 (optional — required when the test suite is enabled, on by default)
- `autoconf`, `automake`, `libtool`, `pkg-config`, `make`

Install the toolchain and dependencies via your package manager:

Debian / Ubuntu:
```bash
sudo apt-get install -y \
    autoconf automake libtool pkg-config make g++ \
    libasio-dev libssl-dev catch2
```

macOS (Homebrew):
```bash
brew install autoconf automake libtool pkg-config asio openssl@3 catch2
export PKG_CONFIG_PATH="$(brew --prefix openssl@3)/lib/pkgconfig"
```

Windows (vcpkg, see [Windows Build Instructions](#windows-build-instructions) below):
```cmd
vcpkg install
```

Build
-----

```bash
git clone https://github.com/corvusoft/restbed.git
cd restbed
./autogen.sh
./configure
make
sudo make install
make check
```

`./autogen.sh` regenerates `configure` and supporting scripts via `autoreconf -fiv`; it only needs to be run from a fresh clone or after editing `configure.ac` / `Makefile.am`. Released tarballs ship with `configure` already generated, so end users can skip straight to `./configure`.

Installation honours the standard GNU directory layout — override with `./configure --prefix=...`, `DESTDIR=...`, etc. A `restbed.pc` file is installed for `pkg-config` consumers:

```bash
pkg-config --cflags --libs restbed
```

Build Options
-------------

Pass these to `./configure`:

| Option           | Description                                                                  | Default  |
| :--------------- | :--------------------------------------------------------------------------- | :------: |
| `--disable-ssl`  | Disable SSL/TLS support (drops the OpenSSL dependency).                      | Enabled  |
| `--enable-ipc`   | Enable Unix domain socket support.                                           | Disabled |
| `--disable-tests`| Skip building the Catch2 test suite (drops the Catch2 dependency).           | Enabled  |
| `--enable-shared` / `--disable-shared` | libtool: produce a shared library.                     | Enabled  |
| `--enable-static` / `--disable-static` | libtool: produce a static library.                     | Enabled  |
| `--with-asio-include=DIR` | Path to ASIO headers if not on the default include search path.     | —        |

Run `./configure --help` for the full list, including standard GNU directory variables (`--prefix`, `--libdir`, etc.).

Windows Build Instructions
--------------------------

The autotools build runs under [MSYS2](https://www.msys2.org/) or Cygwin. Native MSVC support has been removed alongside CMake; the `vcpkg.json` manifest is retained to provision dependencies (Asio, OpenSSL, Catch2) on MSYS2.

From an MSYS2 UCRT64 shell:

```bash
pacman -S --needed \
    base-devel mingw-w64-ucrt-x86_64-toolchain \
    mingw-w64-ucrt-x86_64-asio \
    mingw-w64-ucrt-x86_64-openssl \
    mingw-w64-ucrt-x86_64-catch

git clone https://github.com/corvusoft/restbed.git
cd restbed
./autogen.sh
./configure
make
make check
```

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
