/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <string>

//Project Includes
#include <corvusoft/restbed/method>
#include <corvusoft/restbed/request>
#include <corvusoft/restbed/status_code>
#include <corvusoft/restbed/detail/request_impl.h>

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::string;

//Project Namespaces
using restbed::Method;
using restbed::Request;
using restbed::StatusCode;
using restbed::detail::RequestImpl;

//External Namespaces

TEST( Request, constructor )
{
    Request request;
    
    EXPECT_EQ( Method( "GET" ), request.get_method( ) );
}

TEST( Request, copy_constructor )
{
    RequestImpl original;
    original.set_method( "POST" );
    
    Request copy( original );
    
    EXPECT_EQ( Method( "POST" ), copy.get_method( ) );
}

TEST( Request, modify_method )
{
    RequestImpl request;
    request.set_method( "POST" );
    
    EXPECT_EQ( Method( "POST" ), request.get_method( ) );
}

TEST( Request, modify_version )
{
    RequestImpl request;
    
    try
    {
        request.set_version( 2.0 );
    }
    catch ( StatusCode::Value code )
    {
        EXPECT_EQ( code, StatusCode::HTTP_VERSION_NOT_SUPPORTED );
    }
}

TEST( Request, modify_protocol )
{
    RequestImpl request;
    
    try
    {
        request.set_protocol( "SPDY" );
    }
    catch ( StatusCode::Value code )
    {
        EXPECT_EQ( code, StatusCode::BAD_REQUEST );
    }
}

TEST( Request, assignment_operator )
{
    RequestImpl original;
    original.set_method( "POST" );
    
    RequestImpl copy = original;
    
    EXPECT_EQ( Method( "POST" ), copy.get_method( ) );
}
