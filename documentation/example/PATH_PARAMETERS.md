Overview
--------

"A URI path parameter is part of a path segment that occurs after its name. Path parameters offer a unique opportunity to control the representations of resources. Since they can't be manipulated by standard Web forms, they have to be constructed out of band. Since they're part of the path, they're sequential, unlike query strings." -- [Dorian Taylor](https://doriantaylor.com/policy/http-url-path-parameter-syntax)

Example
-------

```C++
#include <string>
#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session > session )
{
    const auto& request = session->get_request( );
    
    const string body = "Hello, " + request->get_path_parameter( "name" );
    session->close( OK, body, { { "Content-Length", ::to_string( body.size( ) ) } } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource/{name: .*}" );
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

> $ ./example
>
> $ curl -w'\n' -v -XGET 'http://localhost:1984/resource/<YOUR NAME HERE>'
