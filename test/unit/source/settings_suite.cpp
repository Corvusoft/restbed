/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restbed/settings>

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::map;
using std::string;

//Project Namespaces
using restbed::Settings;

//External Namespaces

TEST( Settings, constructor )
{
    Settings settings;
    
    EXPECT_EQ( 80, settings.get_port( ) );
    EXPECT_EQ( "/", settings.get_root( ) );
    EXPECT_EQ( 1024, settings.get_maximum_connections( ) );
}

TEST( Settings, copy_constructor )
{
    Settings original;
    original.set_port( 33 );
    original.set_root( "/events" );
    original.set_maximum_connections( 23 );
    original.set_property( "name", "value" );
    
    Settings copy( original );
    EXPECT_EQ( 33, copy.get_port( ) );
    EXPECT_EQ( "/events", copy.get_root( ) );
    EXPECT_EQ( 23, copy.get_maximum_connections( ) );
    EXPECT_EQ( "value", copy.get_property( "name" ) );
}

TEST( Settings, destructor )
{
    ASSERT_NO_THROW(
    {
        Settings* settings = new Settings( );
        
        delete settings;
    } );
}

TEST( Settings, assignment_operator )
{
    Settings original;
    original.set_port( 33 );
    original.set_root( "/events" );
    original.set_maximum_connections( 23 );
    original.set_property( "name", "value" );
    
    Settings copy = original;
    EXPECT_EQ( 33, copy.get_port( ) );
    EXPECT_EQ( "/events", copy.get_root( ) );
    EXPECT_EQ( 23, copy.get_maximum_connections( ) );
    EXPECT_EQ( "value", copy.get_property( "name" ) );
}

TEST( Settings, modify_port )
{
    Settings settings;
    settings.set_port( 8989 );
    
    EXPECT_EQ( 8989, settings.get_port( ) );
}

TEST( Settings, modify_root )
{
    Settings settings;
    settings.set_root( "/events" );
    
    EXPECT_EQ( "/events", settings.get_root( ) );
}

TEST( Settings, modify_maximum_connections )
{
    Settings settings;
    settings.set_maximum_connections( 120 );
    
    EXPECT_EQ( 120, settings.get_maximum_connections( ) );
}

TEST( Settings, modify_property )
{
    Settings settings;
    settings.set_property( "Local Star", "Sun" );
    
    EXPECT_EQ( "Sun", settings.get_property( "Local Star" ) );
}

TEST( Settings, modify_properties )
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
    
    EXPECT_EQ( values, settings.get_properties( ) );
}

TEST( Settings, ignore_property_case )
{
    Settings settings;
    settings.set_property( "MIR", "1986" );
    
    EXPECT_EQ( "1986", settings.get_property( "mir" ) );
}

TEST( Settings, overwrite_property )
{
    Settings settings;
    settings.set_property( "Fourth Planet", "Sun" );
    settings.set_property( "Fourth Planet", "Mars" );
    
    EXPECT_EQ( "Mars", settings.get_property( "Fourth Planet" ) );
}

TEST( Settings, non_existent_property )
{
    const Settings settings;
    
    EXPECT_NO_THROW( settings.get_property( "Alpha Centauri" ) );
    EXPECT_EQ( "", settings.get_property( "Alpha Centauri" ) );
}
