/*
 * Site: restbed.corvusoft.co.uk
 * Author: Ben Crowhurst
 *
 * Copyright (c) 2013 Restbed Core Development Team and Community Contributors
 *
 * This file is part of Restbed.
 *
 * Restbed is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Restbed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with Restbed.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes
#include <string>
#include <stdexcept>

//Project Includes

//External Includes
#include <gtest/gtest.h>
#include <restbed/method>

//System Namespaces
using std::string;
using std::invalid_argument;

//Project Namespaces

//External Namespaces
using restbed::Method;

TEST( Method, char_constructor )
{
    const char* name = "GET";

    const Method method( name );
    
    EXPECT_TRUE( method.to_string( ) == "GET" );
}

TEST( Method, invalid_char_constructor )
{
    const char* name = "Nova Delphini";
    
    EXPECT_THROW( Method method( name ), invalid_argument );
}

TEST( Method, lowercase_char_constructor )
{
    const char* name = "put";
    
    const Method method( name );
    
    EXPECT_TRUE( method.to_string( ) == "PUT" );
}

TEST( Method, string_constructor )
{
    const string name = "POST";
    
    const Method method( name );
    
    EXPECT_TRUE( method.to_string( ) == "POST" );
}

TEST( Method, invalid_string_constructor )
{
    const string name = "Magellanic cloud";
    
    EXPECT_THROW( Method method( name ), invalid_argument );
}

TEST( Method, lowercase_string_constructor )
{
    const char* name = "get";
    
    const Method method( name );
    
    EXPECT_TRUE( method.to_string( ) == "GET" );
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
    EXPECT_THROW( Method::parse( "Lagoon Nebula" ), invalid_argument );
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
