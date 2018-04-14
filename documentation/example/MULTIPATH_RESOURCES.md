Overview
--------

"The concept of a web resource is primitive in the web architecture, and is used in the definition of its fundamental elements. The term was first introduced to refer to targets of uniform resource locators (URLs), but its definition has been further extended to include the referent of any uniform resource identifier (RFC 3986), or internationalized resource identifier (RFC 3987). In the Semantic Web, abstract resources and their semantic properties are described using the family of languages based on Resource Description Framework (RDF)." -- [Wikipedia](https://en.wikipedia.org/wiki/Web_resource)

Example
-------

```C++
#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session > session )
{
    session->close( OK, "Hello, World!", { { "Content-Length", "13" } } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_paths( { "/messages", "/queues/{id: [0-9]*}/messages" } );
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
> $ curl -w'\n' -v 'http://localhost:1984/messages'
>
> $ curl -w'\n' -v 'http://localhost:1984/queues/12/messages'
