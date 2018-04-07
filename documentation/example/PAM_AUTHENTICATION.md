Overview
--------

"A pluggable authentication module (PAM) is a mechanism to integrate multiple low-level authentication schemes into a high-level application programming interface (API). It allows programs that rely on authentication to be written independently of the underlying authentication scheme. PAM was first proposed by Sun Microsystems in an Open Software Foundation Request for Comments (RFC) 86.0 dated October 1995. It was adopted as the authentication framework of the Common Desktop Environment. As a stand-alone open-source infrastructure, PAM first appeared in Red Hat Linux 3.0.4 in August 1996 in the Linux PAM project. PAM is currently supported in the AIX operating system, DragonFly BSD,[1] FreeBSD, HP-UX, Linux, Mac OS X, NetBSD and Solaris." -- [Wikipedia](https://en.wikipedia.org/wiki/Pluggable_authentication_module)

Example
-------

```C++
#include <memory>
#include <string>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <restbed>
#include <security/pam_appl.h>

#include "base64.h"

using namespace std;
using namespace restbed;

#ifdef __linux__
    #define SERVICE "system-auth"
#else
    #define SERVICE "chkpasswd"
#endif

struct pam_response *response;

int null_conv( int, const struct pam_message**, struct pam_response** reply, void* )
{
    *reply = response;
    return PAM_SUCCESS;
}

bool pam_authorisation( const string& username, const string& password )
{
    pam_handle_t* handle = nullptr;
    struct pam_conv conversation = { null_conv, nullptr };

    int status = pam_start( SERVICE, username.data( ), &conversation, &handle );

    if ( status == PAM_SUCCESS )
    {
        response = new pam_response;
        response[ 0 ].resp_retcode = 0;

        char* pass = new char[ password.length( ) ];
        response[ 0 ].resp = strncpy( pass, password.data( ), password.length( ) );

        status = pam_authenticate( handle, 0 );

        pam_end( handle, PAM_SUCCESS );
    }

    if ( status not_eq PAM_SUCCESS )
    {
        fprintf( stderr, "PAM Error: status=%i, message=%s\n", status, pam_strerror( handle, status ) );
        fprintf( stderr, "Credentials: username='%s', password='%s'\n\n", username.data( ), password.data( ) );
        return false;
    }

    return true;
}

pair< string, string > decode_header( const string& value )
{
    auto data = base64_decode( value.substr( 6 ) );
    auto delimiter = data.find_first_of( ':' );
    auto username = data.substr( 0, delimiter );
    auto password = data.substr( delimiter + 1 );
    
    return make_pair( username, password );
}

void authentication_handler( const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback )
{
    const auto request = session->get_request( );
    const auto credentials = decode_header( request->get_header( "Authorization" ) );
    
    bool authorised = pam_authorisation( credentials.first, credentials.second );
    
    if ( not authorised )
    {
        session->close( UNAUTHORIZED, { { "WWW-Authenticate", "Basic realm=\"Restbed\"" } } );
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

Execution
---------

> $ ./distribution/example/pam_authentication
>
> $ curl -w'\n' -v -XGET 'http://<USERNAME>:<PASSWORD>@localhost:1984/resource'

Build
-----

> $ clang++ -o example example.cpp -l restbed -l pam
