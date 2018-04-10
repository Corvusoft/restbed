Overview
--------

"Digest access authentication is one of the agreed-upon methods a web server can use to negotiate credentials, such as username or password, with a user's web browser. This can be used to confirm the identity of a user before sending sensitive information, such as online banking transaction history. It applies a hash function to the username and password before sending them over the network. In contrast, basic access authentication uses the easily reversible Base64 encoding instead of encryption, making it non-secure unless used in conjunction with TLS." -- [Wikipedia](https://en.wikipedia.org/wiki/Digest_access_authentication)

Example
-------

```C++
#include <regex>
#include <memory>
#include <string>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

string build_authenticate_header( void )
{
    string header = "Digest realm=\"Restbed\",";
    header += "algorithm=\"MD5\",";
    header += "stale=false,";
    header += "opaque=\"0000000000000000\",";
    header += "nonce=\"Ny8yLzIwMDIgMzoyNjoyNCBQTQ\"";
    
    return header;
}

void authentication_handler( const shared_ptr< Session > session,
                             const function< void ( const shared_ptr< Session > ) >& callback )
{
    const auto request = session->get_request( );
    
    auto authorisation = request->get_header( "Authorization" );
    
    bool authorised = regex_match( authorisation, regex( ".*response=\"02863beb15feb659dfe4703d610d1b73\".*" ) );
    
    if ( authorised )
    {
        callback( session );
    }
    else
    {
        session->close( UNAUTHORIZED, { { "WWW-Authenticate", build_authenticate_header( ) } } );
    }
}

void get_method_handler( const shared_ptr< Session > session )
{
    return session->close( OK, "Password Protected Hello, World!", { { "Content-Length", "32" } } );
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
> $ curl -w'\n' -v --digest -XGET 'http://Corvusoft:Glasgow@localhost:1984/resource'
