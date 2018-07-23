Overview
--------

"In computing, syslog is a standard for message logging. It allows separation of the software that generates messages, the system that stores them, and the software that reports and analyzes them. Each message is labeled with a facility code, indicating the software type generating the message, and assigned a severity label.

Computer system designers may use syslog for system management and security auditing as well as general informational, analysis, and debugging messages. A wide variety of devices, such as printers, routers, and message receivers across many platforms use the syslog standard. This permits the consolidation of logging data from different types of systems in a central repository. Implementations of syslog exist for many operating systems." -- [Wikipedia](https://en.wikipedia.org/wiki/Syslog)

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

> $ clang++ -o example example.cpp -l restbed

Execution
---------

> $ ./example
>
> $ curl -w'\n' -v -XGET 'http://localhost:1984/resource'
