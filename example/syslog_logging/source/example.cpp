#include <memory>
#include <cstdarg>
#include <syslog.h>
#include <unistd.h>
#include <sys/types.h>

#include "restbed"

using namespace std;
using namespace restbed;

class SyslogLogger : public Logger
{
    public:
        SyslogLogger( void ) : Logger( )
        {
            //n/a
        }
        
        void log( const LogLevel level, const string format, ... ) noexcept
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
};


Response get_method_handler( const Request& )
{
    Response response;
    response.set_body( "Hello, World!" );
    response.set_status_code( StatusCode::OK );
    
    return response;
}

int main( const int, const char** )
{
    Resource resource;
    resource.set_path( "/resource" );
    resource.set_method_handler( "GET", &get_method_handler );
    
    auto logger = make_shared< SyslogLogger >( );
    
    Settings settings;
    settings.set_port( 1984 );
    
    Service service( settings );
    service.publish( resource );
    service.set_logger( logger );
    service.start( );
    
    return EXIT_SUCCESS;
}
