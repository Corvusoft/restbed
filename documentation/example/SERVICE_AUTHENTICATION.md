Overview
--------

"HTTP Basic authentication (BA) implementation is the simplest technique for enforcing access controls to web resources because it does not require cookies, session identifiers, or login pages; rather, HTTP Basic authentication uses standard fields in the HTTP header, removing the need for handshakes." -- [Wikipedia](https://en.wikipedia.org/wiki/Basic_access_authentication)

Example
-------

```C++
#include <memory>
#include <cstdlib>
#include <ciso646>
#include <functional>
#include <restbed>

using namespace std;
using namespace restbed;

void authentication_handler( const shared_ptr< Session > session,
                             const function< void ( const shared_ptr< Session > ) >& callback )
{
    auto authorisation = session->get_request( )->get_header( "Authorization" );
    
    if ( authorisation not_eq "Basic Q29ydnVzb2Z0OkdsYXNnb3c=" )
    {
        session->close( UNAUTHORIZED, { { "WWW-Authenticate", "Basic realm=\"restbed\"" } } );
    }
    else
    {
        callback( session );
    }
}

void get_method_handler( const shared_ptr< Session > session )
{
    session->close( OK, "Password Protected Hello, World!", { { "Content-Length", "32" } } );
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
    service.set_authentication_handler( authentication_handler );
    
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
> $ curl -w'\n' -v -XGET 'http://Corvusoft:Glasgow@localhost:1984/resource'
