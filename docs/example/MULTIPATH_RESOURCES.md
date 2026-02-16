Overview
--------

A web resource is anything that can be identified and accessed on the web. Originally, the term referred to the target of a URL.

Its definition now includes anything identified by a Uniform Resource Identifier (URI) or Internationalised Resource Identifier (IRI).

In the Semantic Web, abstract resources and their properties are described using RDF (Resource Description Framework), which allows machines to understand and process the meaning of resources.

In short, a web resource can be a webpage, a file, a service, or even an abstract concept, as long as it can be identified on the web.

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

> $ clang++ -std=c++20 -o example example.cpp -l restbed

Execution
---------

> $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
> $ ./example
>
> $ curl -w'\n' -v 'http://localhost:1984/messages'
>
> $ curl -w'\n' -v 'http://localhost:1984/queues/12/messages'
