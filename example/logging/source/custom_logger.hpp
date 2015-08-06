#include <memory>
#include <cstdio>
#include <cstdarg>
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
