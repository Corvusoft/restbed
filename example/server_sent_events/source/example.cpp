/*
 * Example illustrating server-sent events (SSE).
 *
 * Server Usage:
 *    ./distribution/example/server_sent_events
 *
 * Client Usage:
 *    open browser at 'restbed/distribution/resource/server_sent_events.html'
 *
 * Further Reading:
 *    https://www.w3.org/TR/eventsource
 *    https://hpbn.co/server-sent-events-sse
 *    https://www.html5rocks.com/en/tutorials/eventsource/basics
 *    https://html.spec.whatwg.org/multipage/comms.html#authors
 */

#include <map>
#include <chrono>
#include <string>
#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;
using namespace std::chrono;

vector< shared_ptr< Session > > sessions;

void register_event_source_handler( const shared_ptr< Session > session )
{
	const auto headers = multimap< string, string > {
		{ "Connection", "keep-alive" },
		{ "Cache-Control", "no-cache" },
		{ "Content-Type", "text/event-stream" },
		{ "Access-Control-Allow-Origin", "*" } //Only required for demo purposes.
	};

	session->yield( OK, headers, [ ]( const shared_ptr< Session > session )
	{
		sessions.push_back( session );
	} );
}

void event_stream_handler( void )
{
	static size_t counter = 0;
	const auto message = "data: event " + to_string( counter ) + "\n\n";

	for ( auto session : sessions )
	{
		session->yield( message );
	}

	counter++;
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/stream" );
    resource->set_method_handler( "GET", register_event_source_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    auto service = make_shared< Service >( );
    service->publish( resource );
    service->schedule( event_stream_handler, seconds( 2 ) );
    service->start( settings );
    
    return EXIT_SUCCESS;
}
