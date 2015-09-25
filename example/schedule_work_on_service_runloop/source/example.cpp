/*
 * Example illustrating how to schedule work on the service runloop.
 *
 * Server Usage:
 *    ./distribution/example/schedule_work_on_service_runloop
 *
 * Client Usage:
 *    Watch service console output to ensure tasks run.
 */

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
