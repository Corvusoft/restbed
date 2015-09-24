/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <string>

//Project Includes
#include "corvusoft/restbed/string.hpp"

//External Includes
#pragma warning( push )
#pragma warning( disable:4702 )
#include <catch.hpp>
#pragma warning( pop )

//System Namespaces
using std::string;

//Project Namespaces
using restbed::String;

//External Namespaces

TEST_CASE( "deduplicate string value", "[string]" )
{
    const string value = "//path/to////resources/";
    
    REQUIRE( String::replace( "//", "/", value ) == "/path/to/resources/" );
}

TEST_CASE( "deduplicate string value with missing target", "[string]" )
{
    const string value = "/path/to/resources";
    
    REQUIRE( String::replace( "//", "/", value ) == "/path/to/resources" );
}
