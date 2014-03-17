/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes

//Project Includes
#include <restbed>
#include "basic_auth_service.h"

//External Includes

//System Namespaces

//Project Namespaces
using restbed::Request;
using restbed::Response;
using restbed::Settings;

//External Namespaces

BasicAuthService::BasicAuthService( const Settings& settings ) : TestService( settings )
{
    //n/a
}

BasicAuthService::~BasicAuthService( void )
{
    //n/a
}

void BasicAuthService::authentication_handler( const Request& request, /*out*/ Response& response )
{
    auto authorisation = request.get_header( "Authorization" );
    
    if ( authorisation == "Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==" )
    {
        response.set_status_code( 200 );
    }
    else
    {
        response.set_status_code( 401 );
        response.set_header( "WWW-Authenticate", "Basic realm=\"Restbed\"" );
    }
}
