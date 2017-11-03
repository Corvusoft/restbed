/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <memory>

//Project Includes
#include <corvusoft/restbed/resource.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using restbed::Resource;

//External Namespaces

TEST_CASE( "confirm default constructor throws no exceptions", "[resource]" )
{
    REQUIRE_NOTHROW( new Resource );
}

TEST_CASE( "confirm default destructor throws no exceptions", "[resource]" )
{
    auto resource = new Resource;
    
    REQUIRE_NOTHROW( delete resource );
}
