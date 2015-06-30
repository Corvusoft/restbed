/*
 * Example illustrating custom logging.
 *
 * Server Usage:
 *    ./distribution/example/logging
 *
 * Client Usage:
 *    curl -w'\n' -v -XGET 'http://localhost:1984/resource'
 */

#include <memory>
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

        void log( const Level, const string format, ... )
        {
            va_list arguments;
            va_start( arguments, format );

            vfprintf( stderr, format.data( ), arguments );
            fprintf( stderr, "\n" );

            va_end( arguments );
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
