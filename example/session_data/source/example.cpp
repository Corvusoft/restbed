/*
 * Example illustrating session data.
 *
 * Server Usage:
 *    ./distribution/example/session_data
 *
 * Client Usage:
 *    curl -w'\n' -v -X GET 'http://localhost:1984/resource'
 */

#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session >& session )
{
    session->set( "session-data-value", string( "corvusoft" ) );

    session->wait_for( chrono::seconds( 5 ), [ ]( const shared_ptr< Session >& session )
    {
        if ( session->has( "session-data-value" ) ) 
        {
            string value = session->get( "session-data-value" );
            session->close( 200, "session data value: " + value );
            return;
        }

        session->close( 200, "session data value: empty" );
    } );
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
    service.start( settings );
    
    return EXIT_SUCCESS;
}
