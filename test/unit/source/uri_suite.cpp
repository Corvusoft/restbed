/*
 * Site: restbed.corvusoft.co.uk
 * Author: Ben Crowhurst
 *
 * Copyright (c) 2013 Restbed Core Development Team and Community Contributors
 *
 * This file is part of Restbed.
 *
 * Restbed is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Restbed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with Restbed.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes
#include <string>
#include <stdexcept>

//Project Includes

//External Includes
#include <restbed/uri>
#include <gtest/gtest.h>

//System Namespaces
using std::string;
using std::invalid_argument;

//Project Namespaces

//External Namespaces
using restbed::Uri;

TEST( Uri, default_constructor )
{
    string value = "http://code.google.com/p/application-on";
    
    const Uri uri( value );
    
    EXPECT_STREQ( value.data( ), uri.to_string( ).data( ) );
    
    EXPECT_TRUE( 39u == uri.to_string( ).length( ) );
}

TEST( Uri, copy_constructor )
{
    string value = "ftp://code.google.com/p/application-on";
    
    const Uri original( value );
    
    const Uri uri( original );
    
    EXPECT_TRUE( uri == original );
    
    EXPECT_STREQ( uri.to_string( ).data( ), original.to_string( ).data( ) );
}

TEST( Uri, empty_constructor )
{
    EXPECT_THROW( Uri( "" ), invalid_argument );
}

TEST( Uri, default_destructor )
{
    ASSERT_NO_THROW({
        Uri* uri = new Uri( "http://www.google.co.uk" );
        
        delete uri;
    });
}

TEST( Uri, to_string )
{
    string value = "http://code.google.com/p/application-on";
    
    const Uri uri( value );
    
    EXPECT_STREQ( value.data( ), uri.to_string( ).data( ) );
}

TEST( Uri, to_native_path )
{
    string value = "/User/ben/Development/application-on/resource/en_GB.UTF-8";
    
    const Uri uri( "file://" + value );
    
    EXPECT_STREQ( value.data( ), uri.to_native_path( ).data( ) );
}

TEST( Uri, parse )
{
    string value = "file:///tmp/tmp_20482932.txt";
    
    const Uri uri = Uri::parse( value );
    
    EXPECT_STREQ( value.data( ), uri.to_string( ).data( ) );
}

TEST( Uri, decode )
{
    string encoded = "file:///tmp/a%2Eb/tmp_20482932.txt";
    
    const string decoded = Uri::decode( encoded );
    
    EXPECT_STREQ( decoded.data( ), "file:///tmp/a.b/tmp_20482932.txt" );
}

TEST( Uri, encode )
{
    string decoded = "file:///tmp/tmp_20482932.txt";
    
    const string encoded = Uri::encode( decoded );
    
    EXPECT_STREQ( encoded.data( ), "file%3A%2F%2F%2Ftmp%2Ftmp_20482932.txt" );
}

TEST( Uri, get_port )
{
    string value = "http://code.google.com:8981/p/application-on/";
    
    const Uri uri( value );
    
    EXPECT_TRUE( uri.get_port( ) == 8981 );
}

TEST( Uri, get_path )
{
    string value = "http://code.google.com:8981/p/application-on/";
    
    const Uri uri( value );
    
    EXPECT_STREQ( uri.get_path( ).data( ), "/p/application-on/" );
}

TEST( Uri, get_query )
{
    string value = "http://code.google.com/p/application-on/source/detail?r=73aa44eefc85407545b11ff30abbcd980030aab1";
    
    const Uri uri( value );
    
    EXPECT_STREQ( uri.get_query( ).data( ), "r=73aa44eefc85407545b11ff30abbcd980030aab1" );
}

TEST( Uri, get_scheme )
{
    string value = "http://code.google.com/p/application-on/source/detail?r=73aa44eefc85407545b11ff30abbcd980030aab1";
    
    const Uri uri( value );
    
    EXPECT_STREQ( uri.get_scheme( ).data( ), "http" );
}

TEST( Uri, get_fragment )
{
    string value = "http://code.google.com/p/application-on/source/browse/source/appon/type/logger.h?spec=svn73aa44eefc85407545b11ff30abbcd980030aab1&r=73aa44eefc85407545b11ff30abbcd980030aab1#85";
    
    const Uri uri( value );
    
    EXPECT_STREQ( uri.get_fragment( ).data( ), "85" );
}

TEST( Uri, get_username )
{
    string value = "https://crowhurst.ben@code.google.com/p/application-on";
    
    const Uri uri( value );
    
    EXPECT_STREQ( uri.get_username( ).data( ), "crowhurst.ben" );
}

TEST( Uri, get_password )
{
    string value = "https://crowhurst.ben:ASDFFDSA1234@code.google.com/p/application-on";
    
    const Uri uri( value );
    
    EXPECT_STREQ( uri.get_password( ).data( ), "ASDFFDSA1234" );
}

TEST( Uri, get_authority )
{
    string value = "https://crowhurst.ben:ASDFFDSA1234@code.google.com/p/application-on";
    
    const Uri uri( value );
    
    EXPECT_STREQ( uri.get_authority( ).data( ), "code.google.com" );
}
