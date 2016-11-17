/*
 * Example illustrating signal handling.
 *
 * Server Usage:
 *    ./distribution/example/signal_handling
 *
 * Client Usage:
 *    kill -s SIGINT  <PID>
 *    kill -s SIGTERM <PID>
 */

#include <memory>
#include <cstdlib>
#include <restbed>
#include <csignal>
#include <sys/types.h>

#ifdef _WIN32
    #include <process.h>
#else
    #include <unistd.h>
#endif

using namespace std;
using namespace restbed;

void sighup_handler( const int signal_number )
{
    fprintf( stderr, "Received SIGINT signal number '%i'.\n", signal_number );
}

void sigterm_handler( const int signal_number )
{
    fprintf( stderr, "Received SIGTERM signal number '%i'.\n", signal_number );
}

void ready_handler( Service& )
{
#ifdef _WIN32
    fprintf( stderr, "Service PID is '%i'.\n", _getpid( ) );
#else
    fprintf( stderr, "Service PID is '%i'.\n", getpid( ) );
#endif
}

int main( const int, const char** )
{
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    Service service;
    service.set_ready_handler( ready_handler );
    service.set_signal_handler( SIGINT, sighup_handler );
    service.set_signal_handler( SIGTERM, sigterm_handler );
    service.start( settings );
    
    return EXIT_SUCCESS;
}
