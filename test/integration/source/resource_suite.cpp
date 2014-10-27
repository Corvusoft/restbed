/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <map>
#include <string>
#include <stdexcept>
#include <functional>

//Project Includes
#include <corvusoft/restbed/method>
#include <corvusoft/restbed/request>
#include <corvusoft/restbed/response>
#include <corvusoft/restbed/resource>

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::map;
using std::string;
using std::function;
using std::invalid_argument;

//Project Namespaces

//External Namespaces
using restbed::Method;
using restbed::Request;
using restbed::Response;
using restbed::Resource;

const static int method_handler_accessor_expectation = 3349;

Response test_method_handler( const Request& )
{
    Response response;
    response.set_status_code( method_handler_accessor_expectation );
    
    return response;
}

TEST( Resource, method_handler_accessor )
{
    string method = "GET";
    
    Resource resource;
    resource.set_method_handler( method, &test_method_handler );
    
    auto handler = resource.get_method_handler( method );
    
    Request request;
    Response response = handler( request );
    
    EXPECT_EQ( method_handler_accessor_expectation, response.get_status_code( ) );
}

TEST( Resource, method_handlers_accessor )
{
    map< Method, function< Response ( const Request& ) > > expectation;
    expectation[ "GET" ] = &test_method_handler;
    expectation[ "PUT" ] = &test_method_handler;
    expectation[ "DELETE" ] = &test_method_handler;
    
    Resource resource;
    resource.set_method_handlers( expectation );
    
    auto actual = resource.get_method_handlers( );
    
    EXPECT_TRUE( actual.count( "GET" ) );
    EXPECT_TRUE( actual.count( "PUT" ) );
    EXPECT_TRUE( actual.count( "DELETE" ) );
}
