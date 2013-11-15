/*
 * Copyright (c) 2013 Corvusoft
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes
#include <string>
#include <vector>

//Project Includes

//External Includes
#include <gtest/gtest.h>
#include <restbed/string>

//System Namespaces
using std::string;
using std::vector;

//Project Namespaces

//External Namespaces
using restbed::String;

TEST( String, trim_empty_string )
{
    const string text = String::empty;
    
    const string result = String::trim( text );
    
    ASSERT_TRUE( result == String::empty );
}

TEST( String, trim_leading_whitespace )
{
    const string text = "    Third rock from the sun.";
    
    const string result = String::trim( text );
    
    ASSERT_TRUE( result == "Third rock from the sun." );
}

TEST( String, trim_lagging_whitespace )
{
    const string text = "Recognize that the very molecules that make up your body, the atoms that construct the molecules, are traceable to the crucibles that were once the centers of high mass stars that exploded their chemically rich guts into the galaxy, enriching pristine gas clouds with the chemistry of life.     ";
    
    const string result = String::trim( text );
    
    ASSERT_TRUE( result == "Recognize that the very molecules that make up your body, the atoms that construct the molecules, are traceable to the crucibles that were once the centers of high mass stars that exploded their chemically rich guts into the galaxy, enriching pristine gas clouds with the chemistry of life." );
}

TEST( String, trim_leading_lagging_whitespace )
{
    const string text = "  Stars are beautiful, but they must not take an active part in anything, they must just look on forever. It is a punishment put on them for something they did so long ago that no star now knows what it was.    ";
    
    const string result = String::trim( text );
    
    ASSERT_TRUE( result == "Stars are beautiful, but they must not take an active part in anything, they must just look on forever. It is a punishment put on them for something they did so long ago that no star now knows what it was." );
}

TEST( String, trim_with_no_whitespace_in_string )
{
    const string text = "its-all-made-of-stars";
    
    const string result = String::trim( text );
    
    ASSERT_TRUE( result == text );
}

TEST( String, to_lower_empty_string )
{
    const string text = String::empty;
    
    const string result = String::to_lower( text );
    
    ASSERT_TRUE( result == text );
}

TEST( String, to_lower_lowercase_string )
{
    const string text = "cassiopeia";
    
    const string result = String::to_lower( text );
    
    ASSERT_TRUE( result == "cassiopeia" );
}

TEST( String, to_lower_uppercase_string )
{
    const string text = "CEPHEUS";
    
    const string result = String::to_lower( text );
    
    ASSERT_TRUE( result == "cepheus" );
}

TEST( String, to_lower_mixedcase_string )
{
    const string text = "Draco, the Dragon";
    
    const string result = String::to_lower( text );
    
    ASSERT_TRUE( result == "draco, the dragon" );
}

TEST( String, to_upper_empty_string )
{
    const string text = String::empty;
    
    const string result = String::to_upper( text );
    
    ASSERT_TRUE( result == text );
}

TEST( String, to_upper_lowercase_string )
{
    const string text = "cassiopeia";
    
    const string result = String::to_upper( text );
    
    ASSERT_TRUE( result == "CASSIOPEIA" );
}

TEST( String, to_upper_uppercase_string )
{
    const string text = "CEPHEUS";
    
    const string result = String::to_upper( text );
    
    ASSERT_TRUE( result == "CEPHEUS" );
}

TEST( String, to_upper_mixedcase_string )
{
    const string text = "Draco, the Dragon";
    
    const string result = String::to_upper( text );
    
    ASSERT_TRUE( result == "DRACO, THE DRAGON" );
}

TEST( String, split )
{
    const string text = "Saturn has 47 moons.";
    
    const auto& result = String::split( text, ' ' );
    
    vector< string > expectation = {
        "Saturn",
        "has",
        "47",
        "moons."
    };
    
    ASSERT_TRUE( result == expectation );
}

TEST( String, split_with_no_text )
{
    const string text = String::empty;
    
    const auto& result = String::split( text, ' ' );
    
    ASSERT_TRUE( result == vector< string >( ) );
}

TEST( String, split_with_no_delimiter )
{
    const string text = "Pluto is now classified as a dwarf planet.";

    const auto& result = String::split( text, 0 );
    
    ASSERT_TRUE( result == vector< string >( ) );
}

TEST( String, split_with_no_text_and_delimiter )
{
    const string text = String::empty;
    
    const auto& result = String::split( text, 0 );
    
    ASSERT_TRUE( result == vector< string >( ) );
}

TEST( String, split_with_no_matching_delimiter )
{
    const string text = "Neptune's moon, Triton, is slowly getting closer to Neptune. Eventually, it will get so close that it may get torn apart by Neptune's gravity and possibly form rings more spectacular than Saturn's.";
    
    const auto& result = String::split( text, 'X' );
    
    ASSERT_TRUE( result == vector< string >( ) );
}
