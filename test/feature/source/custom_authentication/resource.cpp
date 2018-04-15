//System Includes
#include <map>
#include <thread>
#include <string>
#include <memory>
#include <ciso646>
#include <utility>
#include <stdexcept>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::string;
using std::function;
using std::multimap;
using std::make_pair;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

void resource_handler( const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback )
{
    auto authorisation = session->get_request( )->get_header( "Authorization" );
    
    if ( authorisation not_eq "Basic Q29ydnVzb2Z0OkdsYXNnb3c=" )
    {
        session->close( FORBIDDEN, { { "WWW-Authenticate", "Basic realm=\"restbed\"" } } );
    }
    else
    {
        callback( session );
    }
}

void service_handler( const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback )
{
    auto authorisation = session->get_request( )->get_header( "Authorization" );
    
    if ( authorisation.empty( ) )
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

SCENARIO( "custom resource authentication", "[resource]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resources/1" );
    resource->set_method_handler( "GET", get_method_handler );
    resource->set_authentication_handler( resource_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_authentication_handler( service_handler );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I publish a secure resource at '/resources/1' with a HTTP 'GET' method handler" )
            {
                WHEN( "I perform an authorised HTTP 'GET' request to '/resources/1' with header 'Authorization: Basic Q29ydnVzb2Z0OkdsYXNnb3c='" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resources/1" );
                    
                    multimap< string, string > headers;
                    headers.insert( make_pair( "Authorization", "Basic Q29ydnVzb2Z0OkdsYXNnb3c=" ) );
                    request->set_headers( headers );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '200' (OK) status code" )
                    {
                        REQUIRE( 200 == response->get_status_code( ) );
                        REQUIRE( "OK" == response->get_status_message( ) );
                    }
                    
                    AND_THEN( "I should see a response body of 'Password Protected Hello, World!'" )
                    {
                        auto actual = Http::fetch( 32, response );
                        Bytes expectation { 'P', 'a', 's', 's', 'w', 'o', 'r', 'd', ' ', 'P', 'r', 'o', 't', 'e', 'c', 't', 'e', 'd', ' ', 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
                        REQUIRE( actual == expectation );
                    }
                    
                    headers = response->get_headers( );
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = headers.find( "Connection" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "close" == headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should see a 'Content-Length' header value of '32'" )
                    {
                        auto header = headers.find( "Content-Length" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "32" == headers.find( "Content-Length" )->second );
                    }
                }
                
                WHEN( "I perform an unauthorised HTTP 'GET' request to '/resources/1' with header 'Authorization: Basic Q29y28fsoOkdsYXNnb3c'" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resources/1" );
                    
                    multimap< string, string > headers;
                    headers.insert( make_pair( "Authorization", "Basic Q29y28fsoOkdsYXNnb3c" ) );
                    request->set_headers( headers );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '403' (Forbidden) status code" )
                    {
                        REQUIRE( 403 == response->get_status_code( ) );
                        REQUIRE( "Forbidden" == response->get_status_message( ) );
                    }
                    
                    AND_THEN( "I should see an empty response body" )
                    {
                        REQUIRE( response->get_body( ).empty( ) );
                    }
                    
                    headers = response->get_headers( );
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = headers.find( "Connection" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "close" == headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should not see a 'Content-Length' header" )
                    {
                        REQUIRE( headers.find( "Content-Length" ) == headers.end( ) );
                    }
                    
                    AND_THEN( "I should see a 'WWW-Authenticate' header value of 'Basic realm=\"restbed\"'" )
                    {
                        auto header = headers.find( "WWW-Authenticate" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "Basic realm=\"restbed\"" == headers.find( "WWW-Authenticate" )->second );
                    }
                }
                
                WHEN( "I perform an unauthorised HTTP 'GET' request to '/resources/1' without an 'Authorization' header" )
                {
                    auto request = make_shared< Request >( );
                    request->set_port( 1984 );
                    request->set_host( "localhost" );
                    request->set_path( "/resources/1" );
                    
                    auto response = Http::sync( request );
                    
                    THEN( "I should see a '401' (Unauthorized) status code" )
                    {
                        REQUIRE( 401 == response->get_status_code( ) );
                        REQUIRE( "Unauthorized" == response->get_status_message( ) );
                    }
                    
                    AND_THEN( "I should see an empty response body" )
                    {
                        REQUIRE( response->get_body( ).empty( ) );
                    }
                    
                    multimap< string, string > headers = response->get_headers( );
                    
                    AND_THEN( "I should see a 'Connection' header value of 'close'" )
                    {
                        auto header = headers.find( "Connection" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "close" == headers.find( "Connection" )->second );
                    }
                    
                    AND_THEN( "I should not see a 'Content-Length' header" )
                    {
                        REQUIRE( headers.find( "Content-Length" ) == headers.end( ) );
                    }
                    
                    AND_THEN( "I should see a 'WWW-Authenticate' header value of 'Basic realm=\"restbed\"'" )
                    {
                        auto header = headers.find( "WWW-Authenticate" );
                        REQUIRE( header not_eq headers.end( ) );
                        REQUIRE( "Basic realm=\"restbed\"" == headers.find( "WWW-Authenticate" )->second );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
