/*
 * Example illustrating session data.
 *
 * Server Usage:
 *    ./distribution/example/session_data
 *
 * Client Usage:
 *    curl -w'\n' -v -X GET 'http://localhost:1984/resource?styled=true'
 */

#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    string styled = request->get_query_parameter( "styled", "false" );
    session->set( "styled", styled );
    
    //pause, for example backend processing...
    session->sleep_for( chrono::milliseconds( 500 ), [ ]( const shared_ptr< Session > session )
    {
        string value = session->get( "styled" );
        session->close( 200, "styled response body == " + value );
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
