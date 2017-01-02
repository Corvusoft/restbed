/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <string>

//Project Includes
#include "corvusoft/restbed/string.hpp"

//External Includes
#include <catch.hpp>

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
