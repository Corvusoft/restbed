Overview
--------

In computing, syslog is a standard protocol for message logging. It separates the system components that generate log messages from those that store, analyse, or report on them. Each message includes a *facility code* (identifying the source software type) and a *severity level* (indicating the importance of the event).

System designers use syslog for system management, security auditing, debugging, and general informational messages. Many devices—such as printers, routers, and servers—support the syslog standard, allowing logs from diverse systems to be centralised in a single repository. Syslog implementations are available for many operating systems.


Example
-------

```C++
#include <memory>
#include <cstdarg>
#include <cstdlib>
#include <restbed>
#include <syslog.h>
#include <unistd.h>
#include <sys/types.h>

using namespace std;
using namespace restbed;

class SyslogLogger : public Logger
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

        void log( const Level level, const char* format, ... )
        {
            setlogmask( LOG_UPTO( LOG_DEBUG ) );

            openlog( "Corvusoft Restbed", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1 );

            int priority = 0;

            switch ( level )
            {
                case FATAL:
                    priority = LOG_CRIT;
                    break;

                case ERROR:
                    priority = LOG_ERR;
                    break;

                case WARNING:
                    priority = LOG_WARNING;
                    break;

                case SECURITY:
                    priority = LOG_ALERT;
                    break;

                case INFO:
                case DEBUG:
                default:
                    priority = LOG_NOTICE;
            }

            va_list arguments;

            va_start( arguments, format );

            vsyslog( priority, format, arguments );

            va_end( arguments );

            closelog( );
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
    service.set_logger( make_shared< SyslogLogger >( ) );

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
>
> $ cat var/log/syslog
