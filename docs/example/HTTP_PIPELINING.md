Overview
--------

HTTP pipelining allows a client to send multiple HTTP requests over a single TCP connection without waiting for each corresponding response. This can reduce latency by minimising idle time between requests.

However, due to practical issues—such as buggy proxy servers and head-of-line (HOL) blocking—HTTP pipelining has not been enabled by default in modern browsers since around 2017.

Example
-------

```C++
#include <memory>
#include <cstdlib>
#include <restbed>
#include <stdexcept>

using namespace std;
using namespace restbed;

void get_method_handler_one( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );

    if ( request->get_header( "Connection" ) == "keep-alive" )
    {
        session->yield( OK, "Hello, from first resource.\n", { { "Content-Length", "28" }, { "Connection", "keep-alive" } } );
    }
    else
    {
        session->close( BAD_REQUEST );
    }
}

void get_method_handler_two( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );

    if ( request->get_header( "Connection" ) == "keep-alive" )
    {
        session->yield( OK, "Hello, from second resource.\n", { { "Content-Length", "29" }, { "Connection", "keep-alive" } } );
    }
    else
    {
        session->close( BAD_REQUEST );
    }
}

void get_method_handler_three( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );

    if ( request->get_header( "Connection" ) == "keep-alive" )
    {
        session->yield( OK, "Hello, from third resource.\n", { { "Content-Length", "28" }, { "Connection", "keep-alive" } } );
    }
    else
    {
        session->close( BAD_REQUEST );
    }
}

void error_handler( const int status_code, const exception error, const shared_ptr< Session > session )
{
    if ( session not_eq nullptr and session->is_open( ) )
    {
        string message = error.what( );
        message.push_back( '\n' );

        // we must leave the socket intact on error,
        // otherwise follow up messages will be lost.
        session->yield( status_code, message, { { "Content-Length", ::to_string( message.length( ) ) }, { "Connection", "keep-alive" } } );
    }
}

int main( const int, const char** )
{
    auto resource_one = make_shared< Resource >( );
    resource_one->set_path( "/resource/1" );
    resource_one->set_method_handler( "GET", get_method_handler_one );

    auto resource_two = make_shared< Resource >( );
    resource_two->set_path( "/resource/2" );
    resource_two->set_method_handler( "GET", get_method_handler_two );

    auto resource_three = make_shared< Resource >( );
    resource_three->set_path( "/resource/3" );
    resource_three->set_method_handler( "GET", get_method_handler_three );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( resource_one );
    service.publish( resource_two );
    service.publish( resource_three );
    service.set_error_handler( error_handler );
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
> $ (echo -e "GET /resource/1 HTTP/1.1\r\nHost: localhost\r\nConnection: keep-alive\r\n\r\nGET /resource/2 HTTP/1.1\r\nConnection: keep-alive\r\nHost: localhost\r\n\r\nGET /resource/3 HTTP/1.1\r\nHost: localhost\r\nConnection: keep-alive\r\n\r\n"; sleep 5) | netcat localhost 1984
>
> $ (echo -e "GET &&%$£% /resource/1 HTTP/1.1\r\nHost: localhost\r\nConnection: keep-alive\r\n\r\nGET /resource/2 HTTP/1.1\r\nConnection: keep-alive\r\nHost: localhost\r\n\r\nGET /resource/3 HTTP/1.1\r\nHost: localhost\r\nConnection: keep-alive\r\n\r\n"; sleep 5) | netcat localhost 1984
