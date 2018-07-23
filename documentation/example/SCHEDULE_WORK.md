Overview
--------

"Run loops are part of the fundamental infrastructure associated with threads. A run loop is an event processing loop that you use to schedule work and coordinate the receipt of incoming events. The purpose of a run loop is to keep your thread busy when there is work to do and put your thread to sleep when there is none." -- [Apple](https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/Multithreading/RunLoopManagement/RunLoopManagement.html)

Example
-------

```C++
#include <chrono>
#include <memory>
#include <string>
#include <cstdlib>
#include <restbed>
#include <functional>

using namespace std;
using namespace restbed;

void multi_run_task( void )
{
    fprintf( stderr, "multi run task executed.\n" );
}

void single_run_task( void )
{
    fprintf( stderr, "single run task executed.\n" );
}

void get_method_handler( const shared_ptr< Session > session )
{
    session->close( 200 );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/api" );
    resource->set_method_handler( "GET", get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    auto service = make_shared< Service >( );
    service->publish( resource );
    service->schedule( single_run_task );
    service->schedule( multi_run_task, chrono::milliseconds( 1000 ) );
    service->start( settings );
    
    return EXIT_SUCCESS;
}
```

Build
-----

> $ clang++ -o example example.cpp -l restbed

Execution
---------

> $ ./example
