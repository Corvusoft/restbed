#include <string>
#include <cstring>
#include <cstdlib>
#include <security/pam_appl.h>

using namespace std;

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
