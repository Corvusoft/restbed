/*
 * Example illustrating custom service and resource error hanlding.
 *
 * Server Usage:
 *    ./distribution/example/error_handling
 *
 * Client Usage:
 *    curl -w'\n' -v -XGET 'http://localhost:1984/resources/1'
 *    curl -w'\n' -v -XGET 'http://localhost:1984/resources/2'
 */

#include <memory>
#include <cstdlib>
#include <stdexcept>
#include <restbed>

using namespace std;
using namespace restbed;

void faulty_method_handler( const shared_ptr< Session > )
{
    throw SERVICE_UNAVAILABLE;
}

void resource_error_handler( const int, const exception&, const shared_ptr< Session > session )
{
    if ( session->is_open( ) )
    {
        session->close( 6000, "Custom Resource Internal Server Error", { { "Content-Length", "37" } } );
    }
    else
    {
        fprintf( stderr, "Custom Resource Internal Server Error\n" );
    }
}

void service_error_handler( const int, const exception&, const shared_ptr< Session > session )
{
    if ( session->is_open( ) )
    {
        session->close( 5000, "Custom Service Internal Server Error", { { "Content-Length", "36" } } );
    }
    else
    {
        fprintf( stderr, "Custom Service Internal Server Error\n" );
    }
}

int main( const int, const char** )
{
    auto one = make_shared< Resource >( );
    one->set_path( "/resources/1" );
    one->set_method_handler( "GET", faulty_method_handler );
    
    auto two = make_shared< Resource >( );
    two->set_path( "/resources/2" );
    two->set_method_handler( "GET", faulty_method_handler );
    two->set_error_handler( &resource_error_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    Service service;
    service.publish( one );
    service.publish( two );
    service.set_error_handler( service_error_handler );
    
    service.start( settings );
    
    return EXIT_SUCCESS;
}
