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
using std::multimap;

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
    string protocol = "HTTP";
    multimap< string, string > headers;
    map< string, string > path_parameters;
    multimap< string, string > query_parameters;
    
    Request request;
    
    EXPECT_EQ( body, request.get_body( ) );
    EXPECT_EQ( version, request.get_version( ) );
    EXPECT_EQ( path, request.get_path( ) );
    EXPECT_EQ( origin, request.get_origin( ) );
    EXPECT_EQ( headers, request.get_headers( ) );
    EXPECT_EQ( protocol, request.get_protocol( ) );
    EXPECT_EQ( path_parameters, request.get_path_parameters( ) );
    EXPECT_EQ( query_parameters, request.get_query_parameters( ) );
}

TEST( Request, copy_constructor )
{
    Bytes body = { 'b', 'o', 'd', 'y' };
    double version = 1.0;
    string path = "/events";
    string origin = "localhost";
    string protocol = "HTTPS";
    multimap< string, string > headers = { { "api", "1.0v" } };
    map< string, string > path_parameters = { { "name", "value" } };
    multimap< string, string > query_parameters = { { "q", "cats" } };
    
    RequestImpl original;
    original.set_body( body );
    original.set_version( version );
    original.set_path( path );
    original.set_origin( origin );
    original.set_headers( headers );
    original.set_protocol( protocol );
    original.set_path_parameters( path_parameters );
    original.set_query_parameters( query_parameters );
    
    Request copy( original );
    
    EXPECT_EQ( body, copy.get_body( ) );
    EXPECT_EQ( version, copy.get_version( ) );
    EXPECT_EQ( path, copy.get_path( ) );
    EXPECT_EQ( origin, copy.get_origin( ) );
    EXPECT_EQ( headers, copy.get_headers( ) );
    EXPECT_EQ( protocol, copy.get_protocol( ) );
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
    string protocol = "HTTPS";
    string origin = "localhost";
    multimap< string, string > headers = { { "api", "1.0v" } };
    map< string, string > path_parameters = { { "name", "value" } };
    multimap< string, string > query_parameters = { { "q", "cats" } };
    
    RequestImpl request;
    request.set_body( body );
    request.set_version( version );
    request.set_path( path );
    request.set_origin( origin );
    request.set_headers( headers );
    request.set_protocol( protocol );
    request.set_path_parameters( path_parameters );
    request.set_query_parameters( query_parameters );
    
    string bytes = "GET /events?q=cats HTTPS/1.0\r\napi: 1.0v\r\n\r\nbody";
    
    EXPECT_EQ( Bytes( bytes.begin( ), bytes.end( ) ), request.to_bytes( ) );
}

TEST( Request, has_header )
{
    RequestImpl request;
    
    EXPECT_EQ( false, request.has_header( "Server" ) );
    
    multimap< string, string > headers = { { "Server", "restbed" } };
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
    
    multimap< string, string > parameters = { { "event", "cpu-overload" } };
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

TEST( Request, modify_protocol )
{
    RequestImpl request;
    request.set_protocol( "HTTPS" );
    
    EXPECT_EQ( "HTTPS", request.get_protocol( ) );
}


TEST( Request, modify_header )
{
    multimap< string, string > headers = { { "name", "value" } };
    
    RequestImpl request_impl;
    request_impl.set_headers( headers );
    
    Request request( request_impl );
    
    EXPECT_EQ( "value", request.get_header( "name" ) );
}

TEST( Request, modify_header_default_value )
{
    Request request;
    
    EXPECT_EQ( "corvusoft", request.get_header( "name", "corvusoft" ) );
}

TEST( Request, modify_headers )
{
    multimap< string, string > headers = { { "name", "value" } };
    
    RequestImpl request;
    request.set_headers( headers );
    
    EXPECT_EQ( headers, request.get_headers( ) );
}

TEST( Request, modify_headers_subset_values )
{
    multimap< string, string > headers = { { "name", "value1" }, { "NAME", "value2" }, { "name", "value3" }, { "Age", "30yo" } };
    
    RequestImpl request;
    request.set_headers( headers );
    
    multimap< string, string > expectation = { { "name", "value1" }, { "NAME", "value2" }, { "name", "value3" } };
    
    EXPECT_EQ( expectation, request.get_headers( "name" ) );
}

TEST( Request, modify_query_parameter )
{
    multimap< string, string > parameters = { { "name", "value" } };
    
    RequestImpl request_impl;
    request_impl.set_query_parameters( parameters );
    
    Request request( request_impl );
    
    EXPECT_EQ( "value", request.get_query_parameter( "name" ) );
}

TEST( Request, modify_query_parameter_default_value )
{
    Request request;
    
    EXPECT_EQ( "corvusoft", request.get_query_parameter( "name", "corvusoft" ) );
}

TEST( Request, modify_query_parameters )
{
    multimap< string, string > parameters = { { "name", "value" } };
    
    RequestImpl request;
    request.set_query_parameters( parameters );
    
    EXPECT_EQ( parameters, request.get_query_parameters( ) );
}

TEST( Request, modify_query_subset_parameters )
{
    multimap< string, string > parameters = { { "name", "value1" }, { "name", "value2" }, { "age", "30yo" } };
    
    RequestImpl request;
    request.set_query_parameters( parameters );
    
    multimap< string, string > expectation = { { "name", "value1" }, { "name", "value2" } };
    
    EXPECT_EQ( expectation, request.get_query_parameters( "name" ) );
}

TEST( Request, modify_path_parameter )
{
    map< string, string > parameters = { { "name", "value" } };
    
    RequestImpl request_impl;
    request_impl.set_path_parameters( parameters );
    
    Request request( request_impl );
    
    EXPECT_EQ( "value", request.get_path_parameter( "name" ) );
}

TEST( Request, modify_path_parameter_default_value )
{
    Request request;
    
    EXPECT_EQ( "corvusoft", request.get_path_parameter( "name", "corvusoft" ) );
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
    string protocol = "HTTPS";
    string origin = "localhost";
    multimap< string, string > headers = { { "api", "1.0v" } };
    map< string, string > path_parameters = { { "name", "value" } };
    multimap< string, string > query_parameters = { { "q", "cats" } };
    
    RequestImpl original;
    original.set_body( body );
    original.set_version( version );
    original.set_path( path );
    original.set_origin( origin );
    original.set_headers( headers );
    original.set_protocol( protocol );
    original.set_path_parameters( path_parameters );
    original.set_query_parameters( query_parameters );
    
    RequestImpl copy = original;
    
    EXPECT_EQ( body, copy.get_body( ) );
    EXPECT_EQ( version, copy.get_version( ) );
    EXPECT_EQ( path, copy.get_path( ) );
    EXPECT_EQ( origin, copy.get_origin( ) );
    EXPECT_EQ( headers, copy.get_headers( ) );
    EXPECT_EQ( protocol, copy.get_protocol( ) );
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
    string protocol = "HTTPS";
    string origin = "localhost";
    multimap< string, string > headers = { { "api", "1.0v" } };
    map< string, string > path_parameters = { { "name", "value" } };
    multimap< string, string > query_parameters = { { "q", "cats" } };
    
    RequestImpl lhs;
    lhs.set_body( body );
    lhs.set_version( version );
    lhs.set_path( path );
    lhs.set_origin( origin );
    lhs.set_headers( headers );
    lhs.set_protocol( protocol );
    lhs.set_path_parameters( path_parameters );
    lhs.set_query_parameters( query_parameters );
    
    RequestImpl rhs;
    rhs.set_body( body );
    rhs.set_version( version );
    rhs.set_path( path );
    rhs.set_origin( origin );
    rhs.set_headers( headers );
    rhs.set_protocol( protocol );
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
