/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restbed/request>
#include <corvusoft/restbed/detail/request_impl.h>

//External Includes
#include <gtest/gtest.h>
#include <corvusoft/framework/bytes>

//System Namespaces
using std::map;
using std::string;

//Project Namespaces
using restbed::Request;
using restbed::detail::RequestImpl;
using framework::Bytes;

//External Namespaces

TEST( Request, constructor )
{
    Bytes body;
    double version = 1.1;
    string path = "/";
    string origin = "";
    map< string, string > headers;
    map< string, string > query_parameters;
    map< string, string > path_parameters;
    
    Request request;
    
    EXPECT_EQ( body, request.get_body( ) );
    EXPECT_EQ( version, request.get_version( ) );
    EXPECT_EQ( path, request.get_path( ) );
    EXPECT_EQ( origin, request.get_origin( ) );
    EXPECT_EQ( headers, request.get_headers( ) );
    EXPECT_EQ( path_parameters, request.get_path_parameters( ) );
    EXPECT_EQ( query_parameters, request.get_query_parameters( ) );
}

TEST( Request, copy_constructor )
{
    Bytes body = { 'b', 'o', 'd', 'y' };
    double version = 1.0;
    string path = "/events";
    string origin = "localhost";
    map< string, string > headers = { { "api", "1.0v" } };
    map< string, string > query_parameters = { { "q", "cats" } };
    map< string, string > path_parameters = { { "name", "value" } };
    
    RequestImpl original;
    original.set_body( body );
    original.set_version( version );
    original.set_path( path );
    original.set_origin( origin );
    original.set_headers( headers );
    original.set_path_parameters( path_parameters );
    original.set_query_parameters( query_parameters );
    
    Request copy( original );
    
    EXPECT_EQ( body, copy.get_body( ) );
    EXPECT_EQ( version, copy.get_version( ) );
    EXPECT_EQ( path, copy.get_path( ) );
    EXPECT_EQ( origin, copy.get_origin( ) );
    EXPECT_EQ( headers, copy.get_headers( ) );
    EXPECT_EQ( path_parameters, copy.get_path_parameters( ) );
    EXPECT_EQ( query_parameters, copy.get_query_parameters( ) );
}

TEST( Request, default_destructor )
{
    ASSERT_NO_THROW(
    {
        Request* request = new Request( );
        
        delete request;
    } );
}

TEST( Request, to_bytes )
{
    Bytes body = { 'b', 'o', 'd', 'y' };
    double version = 1.0;
    string path = "/events";
    string origin = "localhost";
    map< string, string > headers = { { "api", "1.0v" } };
    map< string, string > query_parameters = { { "q", "cats" } };
    map< string, string > path_parameters = { { "name", "value" } };
    
    RequestImpl request;
    request.set_body( body );
    request.set_version( version );
    request.set_path( path );
    request.set_origin( origin );
    request.set_headers( headers );
    request.set_path_parameters( path_parameters );
    request.set_query_parameters( query_parameters );
    
    string bytes = "GET /events?q=cats HTTP/1.0\r\napi: 1.0v\r\n\r\nbody";
    
    EXPECT_EQ( Bytes( bytes.begin( ), bytes.end( ) ), request.to_bytes( ) );
}

TEST( Request, has_header )
{
    RequestImpl request;
    
    EXPECT_EQ( false, request.has_header( "Server" ) );
    
    map< string, string > headers = { { "Server", "restbed" } };
    request.set_headers( headers );
    
    EXPECT_EQ( true, request.has_header( "Server" ) );
}

TEST( Request, has_path_parameter )
{
    RequestImpl request;
    
    EXPECT_EQ( false, request.has_path_parameter( "login" ) );
    
    map< string, string > parameters = { { "login", "benc" } };
    request.set_path_parameters( parameters );
    
    EXPECT_EQ( true, request.has_path_parameter( "login" ) );
}

TEST( Request, has_query_parameter )
{
    RequestImpl request;
    
    EXPECT_EQ( false, request.has_query_parameter( "event" ) );
    
    map< string, string > parameters = { { "event", "cpu-overload" } };
    request.set_query_parameters( parameters );
    
    EXPECT_EQ( true, request.has_query_parameter( "event" ) );
}

TEST( Request, modify_body )
{
    Bytes body = { 'b', 'o', 'd', 'y' };
    
    RequestImpl request;
    request.set_body( body );
    
    EXPECT_EQ( body, request.get_body( ) );
}

TEST( Request, modify_version )
{
    RequestImpl request;
    request.set_version( 1.0 );
    
    EXPECT_EQ( 1.0, request.get_version( ) );
}

TEST( Request, modify_path )
{
    RequestImpl request;
    request.set_path( "/events" );
    
    EXPECT_EQ( "/events", request.get_path( ) );
}

TEST( Request, modify_origin )
{
    RequestImpl request;
    request.set_origin( "localhost" );
    
    EXPECT_EQ( "localhost", request.get_origin( ) );
}

TEST( Request, modify_header )
{
    map< string, string > headers = { { "name", "value" } };
    
    RequestImpl request;
    request.set_headers( headers );
    
    EXPECT_EQ( "value", request.get_header( "name" ) );
}

TEST( Request, modify_headers )
{
    map< string, string > headers = { { "name", "value" } };
    
    RequestImpl request;
    request.set_headers( headers );
    
    EXPECT_EQ( headers, request.get_headers( ) );
}

TEST( Request, modify_query_parameter )
{
    map< string, string > parameters = { { "name", "value" } };
    
    RequestImpl request;
    request.set_query_parameters( parameters );
    
    EXPECT_EQ( "value", request.get_query_parameter( "name" ) );
}

TEST( Request, modify_query_parameters )
{
    map< string, string > parameters = { { "name", "value" } };
    
    RequestImpl request;
    request.set_query_parameters( parameters );
    
    EXPECT_EQ( parameters, request.get_query_parameters( ) );
}

TEST( Request, modify_path_parameter )
{
    map< string, string > parameters = { { "name", "value" } };
    
    RequestImpl request;
    request.set_path_parameters( parameters );
    
    EXPECT_EQ( "value", request.get_path_parameter( "name" ) );
}

TEST( Request, modify_path_parameters )
{
    map< string, string > parameters = { { "name", "value" } };
    
    RequestImpl request;
    request.set_path_parameters( parameters );
    
    EXPECT_EQ( parameters, request.get_path_parameters( ) );
}

TEST( Request, assignment_operator )
{
    Bytes body = { 'b', 'o', 'd', 'y' };
    double version = 1.0;
    string path = "/events";
    string origin = "localhost";
    map< string, string > headers = { { "api", "1.0v" } };
    map< string, string > query_parameters = { { "q", "cats" } };
    map< string, string > path_parameters = { { "name", "value" } };
    
    RequestImpl original;
    original.set_body( body );
    original.set_version( version );
    original.set_path( path );
    original.set_origin( origin );
    original.set_headers( headers );
    original.set_path_parameters( path_parameters );
    original.set_query_parameters( query_parameters );
    
    RequestImpl copy = original;
    
    EXPECT_EQ( body, copy.get_body( ) );
    EXPECT_EQ( version, copy.get_version( ) );
    EXPECT_EQ( path, copy.get_path( ) );
    EXPECT_EQ( origin, copy.get_origin( ) );
    EXPECT_EQ( headers, copy.get_headers( ) );
    EXPECT_EQ( path_parameters, copy.get_path_parameters( ) );
    EXPECT_EQ( query_parameters, copy.get_query_parameters( ) );
}

TEST( Request, less_than_operator )
{
    RequestImpl lhs;
    lhs.set_path( "1" );
    
    RequestImpl rhs;
    rhs.set_path( "2" );
    
    EXPECT_TRUE( lhs < rhs );
}

TEST( Request, greater_than_operator )
{
    RequestImpl lhs;
    lhs.set_path( "2" );
    
    RequestImpl rhs;
    rhs.set_path( "1" );
    
    EXPECT_TRUE( lhs > rhs );
}

TEST( Request, equality_operator )
{
    Bytes body = { 'b', 'o', 'd', 'y' };
    double version = 1.0;
    string path = "/events";
    string origin = "localhost";
    map< string, string > headers = { { "api", "1.0v" } };
    map< string, string > query_parameters = { { "q", "cats" } };
    map< string, string > path_parameters = { { "name", "value" } };
    
    RequestImpl lhs;
    lhs.set_body( body );
    lhs.set_version( version );
    lhs.set_path( path );
    lhs.set_origin( origin );
    lhs.set_headers( headers );
    lhs.set_path_parameters( path_parameters );
    lhs.set_query_parameters( query_parameters );
    
    RequestImpl rhs;
    rhs.set_body( body );
    rhs.set_version( version );
    rhs.set_path( path );
    rhs.set_origin( origin );
    rhs.set_headers( headers );
    rhs.set_path_parameters( path_parameters );
    rhs.set_query_parameters( query_parameters );
    
    EXPECT_TRUE( lhs == rhs );
}

TEST( Request, inequality_operator )
{
    RequestImpl lhs;
    lhs.set_version( 1.1 );
    
    RequestImpl rhs;
    rhs.set_version( 1.0 );
    
    EXPECT_TRUE( lhs not_eq rhs );
}
