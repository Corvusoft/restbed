/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <map>
#include <string>
#include <vector>
#include <stdexcept>

//Project Includes
#include <corvusoft/restbed/resource>

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::map;
using std::string;
using std::vector;
using std::invalid_argument;

//Project Namespaces
using restbed::Resource;

//External Namespaces

TEST( Resource, constructor )
{
    string path = "";
    vector< string > paths;
    map< string, string > filters;
    
    Resource resource;
    
    EXPECT_EQ( path, resource.get_path( ) );
    EXPECT_EQ( paths, resource.get_paths( ) );
    EXPECT_EQ( filters, resource.get_header_filters( ) );
}

TEST( Resource, copy_constructor )
{
    string path = "/events";
    map< string, string > filters = { { "Content-Language", "en_GB" } };
    
    Resource original;
    original.set_path( path );
    original.set_header_filters( filters );
    
    Resource copy( original );
    
    EXPECT_EQ( path, copy.get_path( ) );
    EXPECT_EQ( filters, copy.get_header_filters( ) );
}

TEST( Resource, destructor )
{
    ASSERT_NO_THROW(
    {
        Resource* resource = new Resource( );
        
        delete resource;
    } );
}

TEST( Resource, modify_path )
{
    string path = "Super important test data.";
    
    Resource resource;
    resource.set_path( path );
    
    EXPECT_EQ( path, resource.get_path( ) );
}

TEST( Resource, modify_paths )
{
    vector< string > paths;
    paths.push_back( "/one" );
    paths.push_back( "/two" );
    
    Resource resource;
    resource.set_paths( paths );
    
    EXPECT_EQ( paths, resource.get_paths( ) );
}

TEST( Resource, modify_header_filter )
{
    string type = "application/json";
    
    Resource resource;
    resource.set_header_filter( "Content-Type", type );
    
    EXPECT_EQ( type, resource.get_header_filter( "Content-Type" ) );
}

TEST( Resource, modify_case_insensitive_header_filter )
{
    string type = "application/json";
    
    Resource resource;
    resource.set_header_filter( "Content-Type", type );
    
    EXPECT_EQ( type, resource.get_header_filter( "content-type" ) );
}

TEST( Resource, modify_header_filters )
{
    map< string, string > filters = { { "Content-Language", "en_GB" } };
    
    Resource resource;
    resource.set_header_filters( filters );
    
    EXPECT_EQ( filters, resource.get_header_filters( ) );
}

TEST( Resource, assignment_operator )
{
    string path = "/events";
    map< string, string > filters = { { "Content-Language", "en_GB" } };
    
    Resource original;
    original.set_path( path );
    original.set_header_filters( filters );
    
    Resource copy = original;
    
    EXPECT_EQ( path, copy.get_path( ) );
    EXPECT_EQ( filters, copy.get_header_filters( ) );
}

TEST( Resource, less_than_operator )
{
    Resource lhs;
    lhs.set_path( "a" );
    
    Resource rhs;
    rhs.set_path( "abc" );
    
    EXPECT_TRUE( lhs < rhs );
}

TEST( Resource, greater_than_operator )
{
    Resource lhs;
    lhs.set_path( "123456" );
    
    Resource rhs;
    rhs.set_path( "123" );
    
    EXPECT_TRUE( lhs > rhs );
}

TEST( Resource, equality_operator )
{
    Resource lhs;
    lhs.set_path( "/api" );
    
    Resource rhs;
    rhs.set_path( "/api" );
    
    EXPECT_TRUE( lhs == rhs );
}

TEST( Resource, inequality_operator )
{
    Resource lhs;
    lhs.set_path( "/api" );
    
    Resource rhs;
    rhs.set_path( "/resources" );
    
    EXPECT_TRUE( lhs != rhs );
}
