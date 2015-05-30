/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include <corvusoft/restbed/service>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using restbed::Service;

//External Namespaces

TEST_CASE( "confirm default constructor throws no exceptions", "[service]" )
{
    REQUIRE_NOTHROW( new Service );
}

TEST_CASE( "confirm default destructor throws no exceptions", "[service]" )
{
    auto service = new Service;

    REQUIRE_NOTHROW( delete service );
}

TEST_CASE( "confirm calling stop before start throws no exceptions", "[service]" )
{
    Service service;

    REQUIRE_NOTHROW( service.stop( ) );
}
