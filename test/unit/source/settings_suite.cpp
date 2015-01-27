/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restbed/settings>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::map;
using std::string;

//Project Namespaces
using restbed::Settings;

//External Namespaces

SCENARIO( "constructor", "[settings]" )
{
    GIVEN( "i want to instantiate default settings" )
    {
        Settings settings;

        WHEN( "i construct the object" )
        {
            THEN( "i should see default properties" )
            {
                REQUIRE( settings.get_port( ) == 80 );
                REQUIRE( settings.get_root( ) == "/" );
                REQUIRE( settings.get_maximum_connections( ) == 1024 );
            }
        }
    }
}

SCENARIO( "copy constructor", "[settings]" )
{
    GIVEN( "i want to copy existing settings" )
    {
        Settings settings;
        settings.set_port( 33 );
        settings.set_root( "/events" );
        settings.set_maximum_connections( 30 );
        settings.set_property( "name", "value" );

        WHEN( "i instantiate the object with the copy-constructor" )
        {
            Settings copy( settings );

            THEN( "i should see the same properties" )
            {
                REQUIRE( settings.get_port( ) == 33 );
                REQUIRE( settings.get_root( ) == "/events" );
                REQUIRE( settings.get_maximum_connections( ) == 30 );
                REQUIRE( settings.get_property( "name" ) == "value" );
            }
        }
    }
}

SCENARIO( "destructor", "[settings]" )
{
    GIVEN( "i instantiate a new object" )
    {
        Settings* settings = new Settings( );

        WHEN( "i deallocate the object" )
        {
            THEN( "i should not see any exceptions" )
            {
                REQUIRE_NOTHROW( delete settings );
            }
        }
    }
}

SCENARIO( "assignment-operator", "[settings]" )
{
    GIVEN( "i want to copy existing settings" )
    {
        Settings settings;
        settings.set_port( 33 );
        settings.set_root( "/events" );
        settings.set_maximum_connections( 23 );
        settings.set_property( "name", "value" );

        WHEN( "i instantiate the object with the assignment-operator" )
        {
            Settings copy = settings;

            THEN( "i should see the same properties" )
            {
                REQUIRE( settings.get_port( ) == 33 );
                REQUIRE( settings.get_root( ) == "/events" );
                REQUIRE( settings.get_maximum_connections( ) == 23 );
                REQUIRE( settings.get_property( "name" ) == "value" );
            }
        }
    }
}

SCENARIO( "overwrite properties", "[settings]" )
{
    GIVEN( "i want to overwrite all properties" )
    {
        map< string, string > values =
        {
            { "ROOT", "/" },
            { "MODE", "8" },
            { "PORT", "80" },
            { "MAXIMUM CONNECTIONS", "1024" },
            { "VOYAGER 1", "124 AU" },
            { "VOYAGER 2", "101 AU" }
        };

        Settings settings;
        settings.set_properties( values );

        WHEN( "i instantiate the object with the assignment-operator" )
        {
            Settings copy = settings;

            THEN( "i should see the same properties" )
            {
                REQUIRE( settings.get_properties( ) == values );
            }
        }
    }
}

SCENARIO( "property case sensitivity", "[response]" )
{
    GIVEN( "i want to read settings property 'port'" )
    {
        Settings settings;
        settings.set_port( 343 );

        WHEN( "i invoke get_property with 'PoRt'" )
        {
            THEN( "i should see '343'" )
            {
                REQUIRE( settings.get_property( "PoRt" ) == "343" );
            }
        }
    }
}

SCENARIO( "read non-existent property", "[response]" )
{
    GIVEN( "i want to read settings property 'asfadf'" )
    {
        Settings settings;

        WHEN( "i invoke get_property with 'asfadf'" )
        {
            THEN( "i should see ''" )
            {
                REQUIRE( settings.get_property( "asfadf" ) == "" );
            }
        }
    }
}
