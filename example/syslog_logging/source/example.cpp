/*
 * Example illustrating custom logging with syslog.
 *
 * Server Usage:
 *    ./distribution/example/syslog_logging
 *
 * Client Usage:
 *    curl -v -XGET 'http://localhost:1984/resource'
 */

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

        void log( const Level level, const string format, ... )
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

            vsyslog( priority, format.data( ), arguments );

            va_end( arguments );

            closelog( );
        }

        void log_if( bool expression, const Level level, const string format, ... )
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

void get_method_handler( const shared_ptr< Session >& session )
{
    session->close( OK, "Hello, World!", { { "Content-Length", "13" } } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", &get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    Service service;
    service.publish( resource );
    service.set_logger( make_shared< SyslogLogger >( ) );

    service.start( settings );
    
    return EXIT_SUCCESS;
}
