/*
 * Copyright (c) 2013 Corvusoft
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

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

	ASSERT_TRUE( settings.get_port( ) == 80 );
	ASSERT_TRUE( settings.get_root( ) == "/" );
}

TEST( Settings, copy_constructor )
{
	const string name = "Planet";
	const string value = "earth";

    Settings original;
    original.set_property( name, value );

    const Settings copy( original );
    
    ASSERT_TRUE( copy.get_property( name ) == value );
}

TEST( Settings, default_destructor )
{
    ASSERT_NO_THROW( {
        Settings* settings = new Settings( );
        
        delete settings;
    });
}

TEST( Settings, port_accessor )
{
	Settings settings;
	settings.set_port( 8989 );

	ASSERT_TRUE( settings.get_port( ) == 8989 );
}

TEST( Settings, root_accessor )
{
	const string value = "The Quest For Life";

	Settings settings;
	settings.set_root( value );

	ASSERT_TRUE( settings.get_root( ) == value );
}

TEST( Settings, property_accessor )
{
	const string name = "MIR";
	const string value = "1986";

	Settings settings;
	settings.set_property( name, value );

	ASSERT_TRUE( settings.get_property( name ) == value );
}

TEST( Settings, case_insensitive_property_accessor )
{
	const string name = "MIR";
	const string value = "1986";

	Settings settings;
	settings.set_property( name, value );

	ASSERT_TRUE( settings.get_property( "mir" ) == value );
}

TEST( Settings, previously_defined_property_accessor )
{
	Settings settings;
	settings.set_property( "Local Star Name", "Mars" );
	settings.set_property( "Local Star Name", "Sun" );

	ASSERT_TRUE( settings.get_property( "Local Star Name" ) == "Sun" );
}

TEST( Settings, default_defined_property_accessor )
{
	const string value = "black hole";

	Settings settings;
	settings.set_property( "root", value );

	ASSERT_TRUE( settings.get_root( ) == value );
}

TEST( Settings, undefined_property_accessor )
{
	const Settings settings;

	ASSERT_TRUE( settings.get_property( "Alpha Centauri") == "" );
}

TEST( Settings, properties_accessor )
{
	Settings settings;
	settings.set_property( "Voyager 1", "124 AU" );
	settings.set_property( "Voyager 2", "101 AU" );

	map< string, string > expectation = {
		{ "ROOT", "/" },
		{ "PORT", "80" },
		{ "VOYAGER 1", "124 AU" },
		{ "VOYAGER 2", "101 AU" }
	};

	ASSERT_TRUE( settings.get_properties( ) == expectation );
}

TEST( Settings, default_properties_accessor )
{
	const Settings settings;

	map< string, string > expectation = {
		{ "ROOT", "/" },
		{ "PORT", "80" },
	};

	ASSERT_TRUE( settings.get_properties( ) == expectation );
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
