/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes
#include <string>
#include <stdexcept>

//Project Includes
#include <corvusoft/restbed/method>
#include <corvusoft/restbed/request>
#include <corvusoft/restbed/response>
#include <corvusoft/restbed/resource>

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::string;
using std::invalid_argument;

//Project Namespaces

//External Namespaces
using restbed::Method;
using restbed::Request;
using restbed::Response;
using restbed::Resource;

const static int method_handler_accessor_expection = 3349;

Response test_method_handler( const Request& )
{
    Response response;
    response.set_status_code( method_handler_accessor_expection );
    
    return response;
}

TEST( Resource, copy_constructor )
{
    string method = "POST";
    
    Resource original;
    original.set_path( "/event/.*" );
    original.set_header_filter( "Content-Type", "text/data" );
    original.set_method_handler( method, &test_method_handler );
    
    const Resource copy( original );
    
    EXPECT_EQ( original, copy );
}

TEST( Resource, method_handler_accessor )
{
    string method = "GET";
    
    Resource resource;
    resource.set_method_handler( method, &test_method_handler );
    
    auto handler = resource.get_method_handler( method );
    
    Request request;
    Response response = handler( request );
    
    EXPECT_EQ( method_handler_accessor_expection, response.get_status_code( ) );
}
