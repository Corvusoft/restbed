Overview
--------

HTTPS (Hypertext Transfer Protocol Secure) is the secure version of HTTP used to transmit data between a web browser and a web server.

It works by encrypting communication using Transport Layer Security (TLS), which replaced the older Secure Sockets Layer (SSL). For this reason, HTTPS is sometimes called HTTP over TLS or HTTP over SSL.

HTTPS provides:
- Confidentiality – Data is encrypted so others cannot read it.
- Integrity – Data cannot be altered during transmission.
- Authentication – Verifies the identity of the website.

Example
-------

```C++
#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session > session )
{
    session->close( OK, "Hello, World!", { { "Content-Length", "13" }, { "Connection", "close" } } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_method_handler );

    auto ssl_settings = make_shared< SSLSettings >( );
    ssl_settings->set_http_disabled( true );
    ssl_settings->set_private_key( Uri( "file:///tmp/server.key" ) );
    ssl_settings->set_certificate( Uri( "file:///tmp/server.crt" ) );
    ssl_settings->set_temporary_diffie_hellman( Uri( "file:///tmp/dh2048.pem" ) );

    auto settings = make_shared< Settings >( );
    settings->set_ssl_settings( ssl_settings );

    Service service;
    service.publish( resource );
    service.start( settings );

    return EXIT_SUCCESS;
}
```

Build
-----

> $ clang++ -std=c++20 -o example example.cpp -l restbed

Execution
---------

> $ cd /tmp
>
> $ openssl genrsa -out server.key 2048
> $ openssl req -new -key server.key -out server.csr
> $ openssl x509 -req -days 3650 -in server.csr -signkey server.key -out server.crt
> $ openssl dhparam -out dh2048.pem 2048
>
> $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
> $ ./example
>
> $ curl -k -v -w'\n' -X GET 'https://localhost/resource'
