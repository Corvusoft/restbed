Overview
--------

Error handling is the process of anticipating, detecting, and resolving errors in software and communication systems.

Specialised components, called error handlers, help manage these issues. Effective error handling aims to prevent errors when possible, recover from them without stopping the application, and—if recovery is not possible—shut down gracefully while recording details in a log for later analysis.

Example
-------

```C++
#include <memory>
#include <cstdlib>
#include <stdexcept>
#include <restbed>

using namespace std;
using namespace restbed;

void faulty_method_handler( const shared_ptr< Session > )
{
    throw SERVICE_UNAVAILABLE;
}

void resource_error_handler( const int, const exception&, const shared_ptr< Session > session )
{
    if ( session->is_open( ) )
        session->close( 600, "Custom Resource Internal Server Error", { { "Content-Length", "37" } } );
    else
        fprintf( stderr, "Custom Resource Internal Server Error\n" );
}

void service_error_handler( const int, const exception&, const shared_ptr< Session > session )
{
    if ( session->is_open( ) )
        session->close( 601, "Custom Service Internal Server Error", { { "Content-Length", "36" } } );
    else
        fprintf( stderr, "Custom Service Internal Server Error\n" );
}

int main( const int, const char** )
{
    auto one = make_shared< Resource >( );
    one->set_path( "/resources/1" );
    one->set_method_handler( "GET", faulty_method_handler );

    auto two = make_shared< Resource >( );
    two->set_path( "/resources/2" );
    two->set_method_handler( "GET", faulty_method_handler );
    two->set_error_handler( &resource_error_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( one );
    service.publish( two );
    service.set_error_handler( service_error_handler );

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
> $ curl -w'\n' -v -XGET 'http://localhost:1984/resources/1'
>
> $ curl -w'\n' -v -XGET 'http://localhost:1984/resources/2'
