/*
 * Example illustrating how to schedule work on service runloop.
 *
 * Server Usage:
 *    ./distribution/example/schedule_work_on_service_runloop
 *
 * Client Usage:
 *    curl -w'\n' -v -X GET 'http://localhost:1984/api/create/task1'
 */

#include <memory>
#include <string>
#include <vector>
#include <cstdlib>
#include <restbed>
#include <functional>

using namespace std;
using namespace restbed;

vector< string > tasks;

void worker( const shared_ptr< Service >& service )
{
    if ( not tasks.empty( ) )
    {
        fprintf( stderr, "processed task '%s'\n", tasks.front( ).data( ) );
    }
}

void create( const shared_ptr< Session >& session )
{
    auto request = session->get_request( );
    auto name = request->get_path_parameter( "name" );
    tasks.push_back( name );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/api/create/{name: [a-z]*}" );
    resource->set_method_handler( "GET", create );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    auto service = make_shared< Service >( );
    service->publish( resource );
    service->schedule( bind( worker, service ) );
    service->start( settings );
    
    return EXIT_SUCCESS;
}
