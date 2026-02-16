Overview
--------

HTTP Basic authentication (BA) is one of the simplest methods for controlling access to web resources. It does not rely on cookies, session identifiers, or dedicated login pages. Instead, it uses standard fields in the HTTP request header to transmit user credentials, eliminating the need for additional authentication handshakes.

Example
-------

```C++
#include <memory>
#include <cstdlib>
#include <ciso646>
#include <functional>
#include <restbed>

using namespace std;
using namespace restbed;

void service_authentication_handler( const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback )
{
    auto authorisation = session->get_request( )->get_header( "Authorization" );

    if ( authorisation not_eq "Basic YmVuOjEyMzQ=" and authorisation not_eq "Basic bGF1cmE6NDMyMQ==" )
    {
        session->close( UNAUTHORIZED, { { "WWW-Authenticate", "Basic realm=\"restbed\"" } } );
    }
    else
    {
        callback( session );
    }
}

void ben_authentication_handler( const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback )
{
    auto authorisation = session->get_request( )->get_header( "Authorization" );

    if ( authorisation not_eq "Basic YmVuOjEyMzQ=" )
    {
        session->close( FORBIDDEN );
    }
    else
    {
        callback( session );
    }
}

void laura_authentication_handler( const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback )
{
    auto authorisation = session->get_request( )->get_header( "Authorization" );

    if ( authorisation not_eq "Basic bGF1cmE6NDMyMQ==" )
    {
        session->close( FORBIDDEN );
    }
    else
    {
        callback( session );
    }
}

void get_ben_method_handler( const shared_ptr< Session > session )
{
    session->close( OK, "Hi, Ben.", { { "Content-Length", "8" } } );
}

void get_laura_method_handler( const shared_ptr< Session > session )
{
    session->close( OK, "Hi, Laura.", { { "Content-Length", "10" } } );
}

int main( const int, const char** )
{
    auto ben = make_shared< Resource >( );
    ben->set_path( "/ben" );
    ben->set_method_handler( "GET", get_ben_method_handler );
    ben->set_authentication_handler( ben_authentication_handler );

    auto laura = make_shared< Resource >( );
    laura->set_path( "/laura" );
    laura->set_method_handler( "GET", get_laura_method_handler );
    laura->set_authentication_handler( laura_authentication_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( ben );
    service.publish( laura );
    service.set_authentication_handler( service_authentication_handler );

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
> $ curl -w'\n' -v -XGET 'http://ben:1234@localhost:1984/ben'
> $ curl -w'\n' -v -XGET 'http://laura:4321@localhost:1984/laura'
