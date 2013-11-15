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

//External Includes
#include <gtest/gtest.h>
#include <restbed/settings>

//System Namespaces
using std::map;
using std::string;

//Project Namespaces

//External Namespaces
using restbed::Settings;

TEST( Settings, default_constructor )
{
    const Settings settings;
    
    SUCCEED();
}

TEST( Settings, copy_constructor )
{
    Settings original;
    original.set_property( "Planet", "earth" );

    const Settings copy( original );
    
    ASSERT_TRUE( copy.get_property( "Planet" ) == "earth" );
}

TEST( Settings, default_destructor )
{
    ASSERT_NO_THROW( {
        Settings* settings = new Settings( );
        
        delete settings;
    });
}

TEST( Settings, set_port )
{
	Settings settings;
	settings.set_port( 8989 );

	ASSERT_TRUE( settings.get_port( ) == 8989 );
}

TEST( Settings, set_root )
{
	const string value = "The Quest For Life";

	Settings settings;
	settings.set_root( value );

	ASSERT_TRUE( settings.get_root( ) == value );
}

TEST( Settings, set_upper_case_property_name )
{
	Settings settings;
	settings.set_property( "MIR", "1986" );

	ASSERT_TRUE( settings.get_property( "mir" ) == "1986" );
}

TEST( Settings, set_lower_case_property_name )
{
	Settings settings;
	settings.set_property( "solar", "eclipse" );

	ASSERT_TRUE( settings.get_property( "SOLAR" ) == "eclipse" );
}

TEST( Settings, set_mixed_case_property_name )
{
	const string value = "Makemake is the third closest dwarf planet to the Sun and is the only one of the outer four dwarf planet to not have any moons.";
	
	Settings settings;
	settings.set_property( "MakeMake",  value );

	ASSERT_TRUE( settings.get_property( "maKemAke" ) == value );
}

TEST( Settings, set_defined_property )
{
	Settings settings;
	settings.set_property( "Local Star Name", "Mars" );
	settings.set_property( "Local Star Name", "Sun" );

	ASSERT_TRUE( settings.get_property( "Local Star Name" ) == "Sun" );
}

TEST( Settings, set_default_property )
{
	const string value = "black hole";

	Settings settings;
	settings.set_property( "root", value );

	ASSERT_TRUE( settings.get_root( ) == value );
}

TEST( Settings, get_defined_port )
{
	uint16_t port = 1984;

	Settings settings;
	settings.set_port( port );

	ASSERT_TRUE( settings.get_port( ) == port );
}

TEST( Settings, get_default_port )
{
	const Settings settings;

	ASSERT_TRUE( settings.get_port( ) == 80 );
}

TEST( Settings, get_defined_root )
{
	const string root = "/star/stuff";

	Settings settings;
	settings.set_root( root );

	ASSERT_TRUE( settings.get_root( ) == root );
}

TEST( Settings, get_default_root )
{
	const Settings settings;

	ASSERT_TRUE( settings.get_root( ) == "/" );
}

TEST( Settings, get_defined_property )
{
	const string value = "4.243 light years";

	Settings settings;
	settings.set_property( "Proxima Centauri", value );

	ASSERT_TRUE( settings.get_property( "Proxima Centauri" ) == value );
}

TEST( Settings, get_undefined_property )
{
	const Settings settings;

	ASSERT_TRUE( settings.get_property( "Alpha Centauri") == "" );
}

TEST( Settings, get_defined_properties )
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

TEST( Settings, get_default_properties )
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
