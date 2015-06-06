#include <memory>
#include <cstdlib>
#include <stdexcept>
#include <restbed>

using namespace std;
using namespace restbed;

void faulty_method_handler( const shared_ptr< Session >& )
{
    throw SERVICE_UNAVAILABLE;
}

void error_handler( const int status_code, const exception& error, const shared_ptr< Session >& session )
{
    session->close( 5000, "Custom Internal Server Error", { { "Content-Length", "28" } } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources/item" );
    resource->set_method_handler( "GET", &faulty_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( resource );
    service.set_error_handler( &error_handler );

    service.start( settings );

    return EXIT_SUCCESS;
}
