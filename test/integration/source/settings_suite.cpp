/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <string>

//Project Includes
#include <corvusoft/restbed/mode>
#include <corvusoft/restbed/settings>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;

//Project Namespaces
using restbed::Mode;
using restbed::Settings;

//External Namespaces

SCENARIO( "constructor", "[settings]" )
{
    GIVEN( "i want to instantiate a default settings instance" )
    {
        Settings settings;
        settings.set_mode( Mode::ASYNCHRONOUS );

        WHEN( "i construct the object" )
        {
            THEN( "i should see the default mode of 'asynchronous'" )
            {
                REQUIRE( settings.get_mode( ) == Mode::ASYNCHRONOUS );
            }
        }
    }
}
