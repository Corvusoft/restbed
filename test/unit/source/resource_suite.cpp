/*
 * Copyright (c) 2013 Corvusoft
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes
#include <map>
#include <string>
#include <stdexcept>

//Project Includes
#include <corvusoft/restbed/resource>

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::map;
using std::string;
using std::invalid_argument;

//Project Namespaces
using restbed::Resource;

//External Namespaces

TEST( Resource, constructor )
{
    const Resource resource;
    
    map< string, string > expections;

    EXPECT_TRUE( resource.get_path( ) == "" );
    EXPECT_TRUE( resource.get_header_filters( ) == expections );
}

TEST( Resource, default_destructor )
{
    ASSERT_NO_THROW({
        Resource* resource = new Resource( );
        
        delete resource;
    });
}

TEST( Resource, path_accessor )
{
    const string path = "Super important test data.";

    Resource resource;
    resource.set_path( path );

    EXPECT_TRUE( resource.get_path( ) == path );
}

TEST( Resource, header_filter_accessor )
{
    const string type = "application/json";

    Resource resource;
    resource.set_header_filter( "Content-Type", type );

    EXPECT_TRUE( resource.get_header_filter( "Content-Type" ) == type );
}

TEST( Resource, case_insensitive_header_filter_accessor )
{
    const string type = "application/json";

    Resource resource;
    resource.set_header_filter( "Content-Type", type );

    EXPECT_TRUE( resource.get_header_filter( "content-type" ) == type );
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

TEST( Resource, negated_equality_operator )
{
    Resource lhs;
    lhs.set_path( "/api" );
    
    Resource rhs;
    rhs.set_path( "/resources" );
    
    EXPECT_TRUE( lhs != rhs );
}

TEST( Resource, assignment_operator )
{
    Resource original;
    original.set_path( "/api/login" );
    original.set_header_filter( "Content-Type", "text/data" );

    Resource copy = original;

    EXPECT_TRUE( original == copy );
}
