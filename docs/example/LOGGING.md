Overview
--------

Logging is the process of recording events or messages in a system, often written to a log file.

A transaction log is a specific type of log that records interactions (transactions) between a system and its users. It can automatically capture details such as:

- Type of transaction
- Content of the transaction
- Time the transaction occurred

Transaction logs are commonly used to monitor activity, troubleshoot issues, and maintain a record of system usage for auditing or recovery purposes.

Example
-------

```C++
#include <memory>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

class CustomLogger : public Logger
{
    public:
        void stop( void )
        {
            return;
        }

        void start( const shared_ptr< const Settings >& )
        {
            return;
        }

        void log( const Level, const char* format, ... )
        {
            va_list arguments;
            va_start( arguments, format );

            vfprintf( stderr, format, arguments );
            fprintf( stderr, "\n" );

            va_end( arguments );
        }

        void log_if( bool expression, const Level level, const char* format, ... )
        {
            if ( expression )
            {
                va_list arguments;
                va_start( arguments, format );
                log( level, format, arguments );
                va_end( arguments );
            }
        }
};

void get_method_handler( const shared_ptr< Session > session )
{
    session->close( OK, "Hello, World!", { { "Content-Length", "13" } } );
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
    service.set_logger( make_shared< CustomLogger >( ) );

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
> $ curl -w'\n' -v -XGET 'http://localhost:1984/resource'
