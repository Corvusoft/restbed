/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <string>

//Project Includes
#include "request_fixture.h"
#include <corvusoft/restbed/method>
#include <corvusoft/restbed/request>
#include <corvusoft/restbed/status_code>

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::string;

//Project Namespaces
using restbed::Method;
using restbed::Request;
using restbed::StatusCode;

//External Namespaces

TEST( Request, constructor )
{
    RequestFixture request;
    
    EXPECT_EQ( Method( "GET" ), request.get_method( ) );
}

TEST( Request, copy_constructor )
{
    RequestFixture original;
    original.set_method( "POST" );
    
    RequestFixture copy( original );
    
    EXPECT_EQ( Method( "POST" ), copy.get_method( ) );
}

TEST( Request, modify_method )
{
    RequestFixture request;
    request.set_method( "POST" );
    
    EXPECT_EQ( Method( "POST" ), request.get_method( ) );
}

TEST( Request, modify_version )
{
    RequestFixture request;
    
    try
    {
        request.set_version( 2.0 );
    }
    catch ( StatusCode::Value code )
    {
        EXPECT_EQ( code, StatusCode::HTTP_VERSION_NOT_SUPPORTED );
    }
}

TEST( Request, assignment_operator )
{
    RequestFixture original;
    original.set_method( "POST" );
    
    RequestFixture copy = original;
    
    EXPECT_EQ( Method( "POST" ), copy.get_method( ) );
}
