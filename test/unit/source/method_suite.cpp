/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <string>
#include <stdexcept>

//Project Includes
#include <corvusoft/restbed/method>

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::string;

//Project Namespaces
using restbed::Method;

//External Namespaces

TEST( Method, char_constructor )
{
    const char* name = "GET";
    
    Method method( name );
    
    EXPECT_EQ( "GET", method.to_string( ) );
}

TEST( Method, lowercase_char_constructor )
{
    const char* name = "put";
    
    Method method( name );
    
    EXPECT_EQ( "PUT", method.to_string( ) );
}

TEST( Method, invalid_char_constructor )
{
    const char* name = "Nova Delphini";
    
    EXPECT_ANY_THROW( Method method( name ) );
}

TEST( Method, string_constructor )
{
    string name = "POST";
    
    Method method( name );
    
    EXPECT_EQ( "POST", method.to_string( ) );
}

TEST( Method, lowercase_string_constructor )
{
    const char* name = "get";
    
    Method method( name );
    
    EXPECT_EQ( "GET", method.to_string( ) );
}

TEST( Method, invalid_string_constructor )
{
    string name = "Magellanic cloud";
    
    EXPECT_ANY_THROW( Method method( name ) );
}

TEST( Method, copy_constructor )
{
    Method original( "DELETE" );
    
    Method copy( original );
    
    EXPECT_EQ( "DELETE", copy.to_string( ) );
}

TEST( Method, lowercase_copy_constructor )
{
    Method original( "delete" );
    
    Method copy( original );
    
    EXPECT_EQ( "DELETE", copy.to_string( ) );
}

TEST( Method, destructor )
{
    ASSERT_NO_THROW(
    {
        Method* method = new Method( "CONNECT" );
        
        delete method;
    } );
}

TEST( Method, to_string )
{
    Method method( "TRACE" );
    
    EXPECT_EQ( "TRACE", method.to_string( ) );
}

TEST( Method, parse )
{
    Method method = Method::parse( "PUT" );
    
    EXPECT_EQ( "PUT", method.to_string( ) );
}

TEST( Method, invalid_parse )
{
    EXPECT_ANY_THROW( Method::parse( "Lagoon Nebula" ) );
}

TEST( Method, assignment_operator )
{
    Method rhs( "OPTIONS" );
    
    Method lhs = rhs;
    
    EXPECT_EQ( "OPTIONS", lhs.to_string( ) );
}

TEST( Method, less_than_operator )
{
    Method lhs( "GET" );
    
    Method rhs( "POST" );
    
    EXPECT_TRUE( lhs < rhs );
}

TEST( Method, greater_than_operator )
{
    Method lhs( "POST" );
    
    Method rhs( "GET" );
    
    EXPECT_TRUE( lhs > rhs );
}

TEST( Method, equality_operator )
{
    Method lhs( "HEAD" );
    
    Method rhs( "HEAD" );
    
    EXPECT_TRUE( lhs == rhs );
}

TEST( Method, inequality_operator )
{
    Method lhs( "HEAD" );
    
    Method rhs( "CONNECT" );
    
    EXPECT_TRUE( lhs != rhs );
}
