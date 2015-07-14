/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 *
 * bug tracker issue #15
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

TEST_CASE( "trim with only single whitespace character", "[string]" )
{
    REQUIRE( String::trim( " " ) == "" );
}

TEST_CASE( "trim with only multiple whitespace characters", "[string]" )
{
    REQUIRE( String::trim( "    " ) == "" );
}
