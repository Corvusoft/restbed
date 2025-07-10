Overview
--------

"The whole of the Internet is built on conventions. We call them RFCs. While nobody will come and arrest you if you violate an RFC, you do run the risk that your service will not interoperate with the rest of the world." -- [StackExchange](https://softwareengineering.stackexchange.com/questions/218080/should-i-make-up-my-own-http-status-codes-a-la-twitter-420-enhance-your-calm)

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
    session->close( 418 );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    settings->set_status_message( 418, "I'm a teapot" );
    
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
> $ curl -w'\n' -v -X GET 'http://localhost:1984/resource'
