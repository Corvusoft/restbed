/*
 * Copyright (c) 2013, 2014 Corvusoft
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

TEST( Settings, default_constructor )
{
    const Settings settings;
    
    EXPECT_EQ( 80, settings.get_port( )  );
    EXPECT_EQ( "/", settings.get_root( ) );
}

TEST( Settings, copy_constructor )
{
    const string name = "Planet";
    const string value = "earth";
    
    Settings original;
    original.set_property( name, value );
    
    const Settings copy( original );
    
    EXPECT_EQ( value, copy.get_property( name ) );
}

TEST( Settings, default_destructor )
{
    ASSERT_NO_THROW(
    {
        Settings* settings = new Settings( );
        
        delete settings;
    } );
}

TEST( Settings, port_accessor )
{
    Settings settings;
    settings.set_port( 8989 );
    
    EXPECT_EQ( 8989, settings.get_port( ) );
}

TEST( Settings, root_accessor )
{
    const string value = "The Quest For Life";
    
    Settings settings;
    settings.set_root( value );
    
    EXPECT_EQ( value, settings.get_root( ) );
}

TEST( Settings, maximum_connections_accessor )
{
    const int value = 88;
    
    Settings settings;
    settings.set_maximum_connections( value );
    
    EXPECT_EQ( value, settings.get_maximum_connections( ) );
}

TEST( Settings, property_accessor )
{
    const string name = "MIR";
    const string value = "1986";
    
    Settings settings;
    settings.set_property( name, value );
    
    EXPECT_EQ( value, settings.get_property( name ) );
}

TEST( Settings, case_insensitive_property_accessor )
{
    const string name = "MIR";
    const string value = "1986";
    
    Settings settings;
    settings.set_property( name, value );
    
    EXPECT_EQ( value, settings.get_property( "mir" ) );
}

TEST( Settings, previously_defined_property_accessor )
{
    Settings settings;
    settings.set_property( "Local Star Name", "Mars" );
    settings.set_property( "Local Star Name", "Sun" );
    
    EXPECT_EQ( "Sun", settings.get_property( "Local Star Name" ) );
}

TEST( Settings, default_defined_property_accessor )
{
    const string value = "black hole";
    
    Settings settings;
    settings.set_property( "root", value );
    
    EXPECT_EQ( value, settings.get_root( ) );
}

TEST( Settings, undefined_property_accessor )
{
    const Settings settings;
    
    EXPECT_EQ( "", settings.get_property( "Alpha Centauri" ) );
}

TEST( Settings, properties_accessor )
{
    Settings settings;
    settings.set_property( "Voyager 1", "124 AU" );
    settings.set_property( "Voyager 2", "101 AU" );
    
    map< string, string > expectation =
    {
        { "ROOT", "/" },
        { "MODE", "8" },
        { "PORT", "80" },
        { "MAXIMUM CONNECTIONS", "1024" },
        { "VOYAGER 1", "124 AU" },
        { "VOYAGER 2", "101 AU" }
    };
    
    EXPECT_EQ( expectation, settings.get_properties( ) );
}

TEST( Settings, default_properties_accessor )
{
    const Settings settings;
    
    map< string, string > expectation =
    {
        { "ROOT", "/" },
        { "MODE", "8" },
        { "PORT", "80" },
        { "MAXIMUM CONNECTIONS", "1024" }
    };
    
    EXPECT_EQ( expectation, settings.get_properties( ) );
}

TEST( Settings, assignment_operator )
{
    Settings rhs;
    rhs.set_property( "species", "30+ Million on Earth" );
    
    const Settings lhs = rhs;
    
    const auto& rhs_properties = rhs.get_properties( );
    const auto& lhs_properties = lhs.get_properties( );
    
    EXPECT_TRUE( lhs_properties == rhs_properties );
}

TEST( Settings, less_than_operator )
{
    Settings rhs;
    rhs.set_property( "Dr", "Richard Terrile" );
    
    const Settings lhs;
    
    EXPECT_TRUE( lhs < rhs );
}

TEST( Settings, greater_than_operator )
{
    const Settings rhs;
    
    Settings lhs;
    lhs.set_property( "Mars", "Water ways" );
    
    EXPECT_TRUE( lhs > rhs );
}

TEST( Settings, equality_operator )
{
    const Settings lhs;
    
    const Settings rhs;
    
    EXPECT_TRUE( lhs == rhs );
}

TEST( Settings, negated_equality_operator )
{
    const Settings lhs;
    
    Settings rhs;
    rhs.set_property( "Mars travel time?", "~6 Months" );
    
    EXPECT_TRUE( lhs != rhs );
}
