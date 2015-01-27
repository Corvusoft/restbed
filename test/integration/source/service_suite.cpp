/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include <corvusoft/restbed/service>
#include <corvusoft/restbed/settings>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using restbed::Service;
using restbed::Settings;

//External Namespaces

SCENARIO( "constructor", "[service]" )
{
    GIVEN( "i wish to allocate a new service" )
    {
        WHEN( "i allocate the object" )
        {
            THEN( "i should not see any exceptions" )
            {
                Settings settings;
                REQUIRE_NOTHROW( Service service( settings ) );
            }
        }
    }
}

SCENARIO( "destructor", "[service]" )
{
    GIVEN( "i instantiate a new object" )
    {
        Settings settings;
        Service* service = new Service( settings );

        WHEN( "i deallocate the object" )
        {
            THEN( "i should not see any exceptions" )
            {
                REQUIRE_NOTHROW( delete service );
            }
        }
    }
}
