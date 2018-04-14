Overview
--------

"
The inside and front of a Dell PowerEdge web server, a computer designed for rack mounting
Web server refers to server software, or hardware dedicated to running said software, that can serve contents to the World Wide Web. A web server processes incoming network requests over the HTTP protocol (and several other related protocols)." -- [Wikipedia](https://en.wikipedia.org/wiki/Web_server)

Example
-------

```C++
#include <string>
#include <memory>
#include <cstdlib>
#include <fstream>
#include <restbed>
#include <streambuf>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    const string filename = request->get_path_parameter( "filename" );
    
    ifstream stream( "./" + filename, ifstream::in );
    
    if ( stream.is_open( ) )
    {
        const string body = string( istreambuf_iterator< char >( stream ), istreambuf_iterator< char >( ) );
        
        const multimap< string, string > headers
        {
            { "Content-Type", "text/html" },
            { "Content-Length", ::to_string( body.length( ) ) }
        };
        
        session->close( OK, body, headers );
    }
    else
    {
        session->close( NOT_FOUND );
    }
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/static/{filename: [a-z]*\\.html}" );
    resource->set_method_handler( "GET", get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    Service service;
    service.publish( resource );
    service.start( settings );
    
    return EXIT_SUCCESS;
}
```

Build
-----

> $ clang++ -o example example.cpp -l restbed

Execution
---------

> $ touch index.html
>
> $ ./example
>
> $ curl -w'\n' -v -X GET 'http://localhost:1984/static/index.html'
