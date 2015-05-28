#include <string>
#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session >& session )
{
    session->yield( OK, "7\r\nrestbed\r\n", { { "Transfer-Encoding", "chunked" } } );

    restbed::wait_for( seconds( 5 ), [ ]( const shared_ptr< Session >& session )
    {
        session->yield( "16\r\nchunked encoding\r\n" );

        restbed::wait_for( seconds( 2 ), [ ]( const shared_ptr< Session >& session
        {
            session->close( "0\r\n\r\n" );
        } ) );
    } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources/item" );
    resource->set_method_handler( "GET", &get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    Service service;
    service.publish( resource );
    service.start( settings );
    
    return EXIT_SUCCESS;
}
