Overview
--------

"SSEs are sent over traditional HTTP. That means they do not require a special protocol or server implementation to get working. WebSockets on the other hand, require full-duplex connections and new Web Socket servers to handle the protocol. In addition, Server-Sent Events have a variety of features that WebSockets lack by design such as automatic reconnection, event IDs, and the ability to send arbitrary events." -- [html5rocks](https://www.html5rocks.com/en/tutorials/eventsource/basics/)

Example
-------

```C++
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

	sessions.erase(
		  std::remove_if(sessions.begin(), sessions.end(),
                                [](const shared_ptr<Session> &a) {
                                  return a->is_closed();
                                }),
		  sessions.end());

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
```

Build
-----

> $ clang++ -o example example.cpp -l restbed

Execution
---------

> $ ./example

Client
------
```HTML
<!DOCTYPE HTML>
<html>
  <head>
    <script type="text/javascript">
      function add_event( data )
      {
         var li = document.createElement( "li" );
         li.appendChild( document.createTextNode( "> " + data ) );

         var ul = document.getElementById( "events" );
         ul.appendChild( li );
      }

	  if ( !!window.EventSource )
	  {
	     var source = new EventSource( "http://localhost:1984/stream" );

         source.addEventListener( "message", function( evt )
         {
         	add_event( evt.data );
         }, false );

		 source.addEventListener( "open", function( evt )
		 {
		    add_event( "EventSource open." );
		 }, false );

         source.addEventListener( 'error', function( evt )
         {
            if ( evt.readyState == EventSource.CLOSED )
            {
               add_event( "EventSource closed." );
            }
         }, false );
	  }
	  else
	  {
	    alert( "WebSockets NOT supported by your Browser!" );
	  }
    </script>
  </head>
  <body>
  	<h1>Incoming Events</h1>
  	<ul id="events">
  	</ul>
  </body>
</html>
```
