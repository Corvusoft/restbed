/*
 * Example illustrating how to wait for external events to complete.
 *
 * Server Usage:
 *    ./distribution/example/wait_for_external_event
 *
 * Client Usage:
 *    curl -w'\n' -v -X GET 'http://localhost:1984/products/4'
 */

#include <memory>
#include <future>
#include <chrono>
#include <cstdlib>
#include <restbed>
#include <functional>

using namespace std;
using namespace restbed;

void query_database( const string& key, /*out*/ shared_ptr< string > record )
{
    //simulate complex database query.
    this_thread::sleep_for( chrono::seconds( 30 ) );
    
    static map< string, string > records =
    {
        { "0", "appon" },
        { "1", "restq" },
        { "2", "shard" },
        { "3", "synapse" },
        { "4", "restbed" }
    };
    
    auto entry = records.find( key );
    *record = ( entry == records.end( ) ) ? "no product found." : entry->second;
}

chrono::seconds trigger( const chrono::seconds& current_delay, shared_ptr< future< void > > query )
{
    if ( query->wait_for( chrono::seconds::zero( ) ) == future_status::ready )
    {
        fprintf( stderr, "Database query complete, returning zero second delay.\n" );
        return chrono::seconds::zero( );
    }
    
    fprintf( stderr, "Database query incomplete, returning best educated guess for next delay...\n" );
    return current_delay + chrono::seconds( 5 );
}

void end_get_method_handler( const shared_ptr< Session >& session, const shared_ptr< string > record )
{
    const string body( "Product, " + *record );
    session->close( OK, body, { { "Content-Length", ::to_string( body.size( ) ) }, { "Connection", "close" } } );
}

void begin_get_method_handler( const shared_ptr< Session >& session )
{
    const auto request = session->get_request( );
    const auto key = request->get_path_parameter( "key" );
    
    auto record = make_shared< string >( "" );
    auto query = make_shared< future< void > >( );
    *query = async( launch::async, bind( query_database, key, record ) );
    
    session->wait_for( chrono::seconds( 5 ),
                       bind( end_get_method_handler, placeholders::_1, record ),
                       bind( trigger, placeholders::_1, query ) );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/products/{key: [0-4]}" );
    resource->set_method_handler( "GET", begin_get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    auto service = make_shared< Service >( );
    service->publish( resource );
    service->start( settings );
    
    return EXIT_SUCCESS;
}
