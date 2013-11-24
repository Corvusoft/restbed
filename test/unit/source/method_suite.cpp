/*
 * Copyright (c) 2013 Corvusoft
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

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

    const Method method( name );
    
    EXPECT_TRUE( method.to_string( ) == "GET" );
}

TEST( Method, lowercase_char_constructor )
{
    const char* name = "put";
    
    const Method method( name );
    
    EXPECT_TRUE( method.to_string( ) == "PUT" );
}

TEST( Method, invalid_char_constructor )
{
    const char* name = "Nova Delphini";
    
    EXPECT_ANY_THROW( Method method( name ) );
}

TEST( Method, string_constructor )
{
    const string name = "POST";
    
    const Method method( name );
    
    EXPECT_TRUE( method.to_string( ) == "POST" );
}

TEST( Method, lowercase_string_constructor )
{
    const char* name = "get";
    
    const Method method( name );
    
    EXPECT_TRUE( method.to_string( ) == "GET" );
}

TEST( Method, invalid_string_constructor )
{
    const string name = "Magellanic cloud";
    
    EXPECT_ANY_THROW( Method method( name ) );
}

TEST( Method, copy_constructor )
{
    const Method original( "DELETE" );
    
    const Method copy( original );
    
    EXPECT_TRUE( copy.to_string( ) == "DELETE" );
}

TEST( Method, lowercase_copy_constructor )
{
    const Method original( "delete" );
    
    const Method copy( original );
    
    EXPECT_TRUE( copy.to_string( ) == "DELETE" );
}

TEST( Method, default_destructor )
{
    ASSERT_NO_THROW({
        Method* method = new Method( "CONNECT" );
        
        delete method;
    });
}

TEST( Method, to_string )
{
    const Method method( "TRACE" );

    EXPECT_TRUE( method.to_string( ) == "TRACE" );
}

TEST( Method, parse )
{
    const Method method = Method::parse( "PUT" );
    
    EXPECT_TRUE( method.to_string( ) == "PUT" );
}

TEST( Method, invalid_parse )
{
    EXPECT_ANY_THROW( Method::parse( "Lagoon Nebula" ) );
}

TEST( Method, assignment_operator )
{
    const Method rhs( "OPTIONS" );
    
    const Method lhs = rhs;
    
    EXPECT_TRUE( lhs.to_string( ) == "OPTIONS" );
}

TEST( Method, less_than_operator )
{
    const Method lhs( "GET" );
    
    const Method rhs( "POST" );
    
    EXPECT_TRUE( lhs < rhs );
}

TEST( Method, greater_than_operator )
{
    const Method lhs( "POST" );
    
    const Method rhs( "GET" );
    
    EXPECT_TRUE( lhs > rhs );
}

TEST( Method, equality_operator )
{
    const Method lhs( "HEAD" );
    
    const Method rhs( "HEAD" );
    
    EXPECT_TRUE( lhs == rhs );
}

TEST( Method, negated_equality_operator )
{
    const Method lhs( "HEAD" );
    
    const Method rhs( "CONNECT" );
    
    EXPECT_TRUE( lhs != rhs );
}
