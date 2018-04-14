Overview
--------

"The HTTP client functionality is DEPRECATED and will be removed from future releases.  See [Restless](https://github.com/Corvusoft/restless) for an alternative implementation."

Example
-------

```C++
#include <memory>
#include <future>
#include <cstdio>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void print( const shared_ptr< Response >& response )
{
    fprintf( stderr, "*** Response ***\n" );
    fprintf( stderr, "Status Code:    %i\n", response->get_status_code( ) );
    fprintf( stderr, "Status Message: %s\n", response->get_status_message( ).data( ) );
    fprintf( stderr, "HTTP Version:   %.1f\n", response->get_version( ) );
    fprintf( stderr, "HTTP Protocol:  %s\n", response->get_protocol( ).data( ) );

    for ( const auto header : response->get_headers( ) )
    {
        fprintf( stderr, "Header '%s' > '%s'\n", header.first.data( ), header.second.data( ) );
    }

    auto length = response->get_header( "Content-Length", 0 );

    Http::fetch( length, response );

    fprintf( stderr, "Body:           %.*s...\n\n", 25, response->get_body( ).data( ) );
}

int main( const int, const char** )
{
    auto request = make_shared< Request >( Uri( "http://www.corvusoft.co.uk:80/?query=search%20term" ) );
    request->set_header( "Accept", "*/*" );
    request->set_header( "Host", "www.corvusoft.co.uk" );

    auto response = Http::sync( request );
    print( response );

    auto future = Http::async( request, [ ]( const shared_ptr< Request >, const shared_ptr< Response > response )
    {
        fprintf( stderr, "Printing async response\n" );
        print( response );
    } );

    future.wait( );

    return EXIT_SUCCESS;
}
```

Build
-----

> $ clang++ -o example example.cpp -l restbed

Execution
---------

> $ ./example
