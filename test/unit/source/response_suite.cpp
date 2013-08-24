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
#include <map>
#include <string>
#include <stdexcept>

//Project Includes

//External Includes
#include <gtest/gtest.h>
#include <restbed/response>

//System Namespaces
using std::map;
using std::string;
using std::invalid_argument;

//Project Namespaces

//External Namespaces
using restbed::Response;

TEST( Response, constructor )
{
    const Response response;
    
    EXPECT_TRUE( response.get_data( ) == "" );

    auto expectation = map< string, string >( );

    EXPECT_TRUE( response.get_headers( ) == expectation );
}

TEST( Response, copy_constructor )
{
    const string data = "Test Data";

    Response original;
    original.set_data( data );

    const Response copy( original );
    
    EXPECT_TRUE( copy.get_data( ) == data );
}

TEST( Response, default_destructor )
{
    ASSERT_NO_THROW({
        Response* response = new Response( );
        
        delete response;
    });
}

TEST( Response, data_accessor )
{
    const string data = "Super important test data.";

    Response response;
    response.set_data( data );

    EXPECT_TRUE( response.get_data( ) == data );
}

TEST( Response, header_accessor )
{
    const string name = "Test Name.";
    const string value = "Test Value.";

    Response response;
    response.set_header( name, value );

    EXPECT_TRUE( response.get_header( name ) == value );
}

TEST( Response, headers_accessor )
{
    const map< string, string > headers = {
        {"1", "2"},
        {"3", "4"}
    };

    Response response;
    response.set_headers( headers );

    EXPECT_TRUE( response.get_headers( ) == headers );
}

TEST( Response, less_than_operator )
{
    Response lhs;
    lhs.set_data( "a" );

    Response rhs;
    rhs.set_data( "abc" );

    EXPECT_TRUE( lhs < rhs );
}

TEST( Response, greater_than_operator )
{
    Response lhs;
    lhs.set_data( "123456" );

    Response rhs;
    rhs.set_data( "123" );

    EXPECT_TRUE( lhs > rhs );
}

TEST( Response, equality_operator )
{
    Response lhs;
    lhs.set_header( "name", "value" );
    
    Response rhs;
    rhs.set_header( "name", "value" );
    
    EXPECT_TRUE( lhs == rhs );
}

TEST( Response, negated_equality_operator )
{
    Response lhs;
    lhs.set_data( "some data" );
    
    Response rhs;
    rhs.set_data( "data some" );
    
    EXPECT_TRUE( lhs != rhs );
}

TEST( Response, assignment_operator )
{
    const map< string, string > headers = {
        {"12", "25"},
        {"33", "44"}
    };

    Response original;
    original.set_headers( headers );

    Response copy = original;

    EXPECT_TRUE( original == copy );
}
