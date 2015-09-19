/*
 * Example illustrating Transfer-Encoding response processing.
 *
 * Server Usage:
 *    ./distribution/example/transfer_encoding_response
 *
 * Client Usage:
 *    curl -w'\n' -v -XGET 'http://localhost:1984/resources/item'
 */

#include <string>
#include <chrono>
#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session > session )
{
    session->yield( OK, "8\r\nrestbed \r\n", { { "Transfer-Encoding", "chunked" } }, [ ]( const shared_ptr< Session > session )
    {
        session->sleep_for( chrono::milliseconds( 500 ), [ ]( const shared_ptr< Session > session )
        {
            session->yield( "10\r\nchunked encoding\r\n", [ ]( const shared_ptr< Session > session )
            {
                session->close( "0\r\n\r\n" );
            } );
        } );
    } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources/item" );
    resource->set_method_handler( "GET", get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    Service service;
    service.publish( resource );
    service.start( settings );
    
    return EXIT_SUCCESS;
}
