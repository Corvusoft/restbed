/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <string>
#include <ciso646>
#include <stdexcept>

//Project Includes
#include "corvusoft/restbed/uri.hpp"

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::invalid_argument;

//Project Namespaces
using restbed::Uri;

//External Namespaces

TEST_CASE( "default constructor", "[uri]" )
{
    Uri uri( "http://crowhurst.ben:ASDFFDSA1234@code.google.com:80/resources/index.html?q=bear&b=cubs#frag1" );
    REQUIRE( uri.get_port( ) == 80 );
    REQUIRE( uri.get_path( ) == "/resources/index.html" );
    REQUIRE( uri.get_query( ) == "q=bear&b=cubs" );
    REQUIRE( uri.get_scheme( ) == "http" );
    REQUIRE( uri.get_fragment( ) == "frag1" );
    REQUIRE( uri.get_username( ) == "crowhurst.ben" );
    REQUIRE( uri.get_password( ) == "ASDFFDSA1234" );
    REQUIRE( uri.get_authority( ) == "code.google.com" );
    
    const string value = uri.to_string( );
    REQUIRE( value == "http://crowhurst.ben:ASDFFDSA1234@code.google.com:80/resources/index.html?q=bear&b=cubs#frag1" );
}

TEST_CASE( "ipv4 constructor", "[uri]" )
{
    Uri uri( "http://username:password@127.1.1.1:80/resources/index.html?q=bear&b=cubs#frag1" );
    REQUIRE( uri.get_port( ) == 80 );
    REQUIRE( uri.get_path( ) == "/resources/index.html" );
    REQUIRE( uri.get_query( ) == "q=bear&b=cubs" );
    REQUIRE( uri.get_scheme( ) == "http" );
    REQUIRE( uri.get_fragment( ) == "frag1" );
    REQUIRE( uri.get_username( ) == "username" );
    REQUIRE( uri.get_password( ) == "password" );
    REQUIRE( uri.get_authority( ) == "127.1.1.1" );

    const string value = uri.to_string( );
    REQUIRE( value == "http://username:password@127.1.1.1:80/resources/index.html?q=bear&b=cubs#frag1" );
}

TEST_CASE( "ipv6 constructor", "[uri]" )
{
    Uri uri( "http://username:password@[2001:0db8:85a3:0000:0000:8a2e:0370:7334]:80/resources/index.html?q=bear&b=cubs#frag1" );
    REQUIRE( uri.get_port( ) == 80 );
    REQUIRE( uri.get_path( ) == "/resources/index.html" );
    REQUIRE( uri.get_query( ) == "q=bear&b=cubs" );
    REQUIRE( uri.get_scheme( ) == "http" );
    REQUIRE( uri.get_fragment( ) == "frag1" );
    REQUIRE( uri.get_username( ) == "username" );
    REQUIRE( uri.get_password( ) == "password" );
    REQUIRE( uri.get_authority( ) == "2001:0db8:85a3:0000:0000:8a2e:0370:7334" );

    const string value = uri.to_string( );
    REQUIRE( value == "http://username:password@[2001:0db8:85a3:0000:0000:8a2e:0370:7334]:80/resources/index.html?q=bear&b=cubs#frag1" );
}

TEST_CASE( "invalid constructor", "[uri]" )
{
    REQUIRE_THROWS_AS( Uri( "---_)(*&" ), invalid_argument );
}

TEST_CASE( "empty constructor", "[uri]" )
{
    REQUIRE_THROWS_AS( Uri( "" ), invalid_argument );
}

TEST_CASE( "copy constructor", "[uri]" )
{
    Uri uri( "ftp://code.google.com/p/application-on" );
    Uri copy( uri );
    
    REQUIRE( copy.to_string( ) == uri.to_string( ) );
}

TEST_CASE( "destructor", "[uri]" )
{
    Uri* uri = new Uri( "ftp://code.google.com/p/application-on" );
    
    REQUIRE_NOTHROW( delete uri );
}

TEST_CASE( "assignment-operator", "[uri]" )
{
    Uri uri( "http://code.google.com/p/application-on/source/detail?r=73aa44eefc85407545b11ff30abbcd980030aab1" );
    Uri copy = uri;
    
    REQUIRE( copy.to_string( ) == uri.to_string( ) );
}

TEST_CASE( "less-than-operator", "[uri]" )
{
    Uri lhs( "http://restbed.corvusoft.co.uk" );
    Uri rhs( "http://restule.corvusoft.co.uk/index.html" );
    
    REQUIRE( lhs < rhs );
}

TEST_CASE( "greater-than-operator", "[uri]" )
{
    Uri lhs( "http://restbed.corvusoft.co.uk/index.html" );
    Uri rhs( "http://restbed.corvusoft.co.uk" );
    
    REQUIRE( lhs > rhs );
}

TEST_CASE( "equality-operator", "[uri]" )
{
    Uri lhs( "http://restq.corvusoft.co.uk" );
    Uri rhs( "http://restq.corvusoft.co.uk" );
    
    REQUIRE( lhs == rhs );
}

TEST_CASE( "inequality-operator", "[uri]" )
{
    Uri lhs( "http://restbed.corvusoft.co.uk" );
    Uri rhs( "http://restule.corvusoft.co.uk" );
    
    REQUIRE( lhs not_eq rhs );
}

TEST_CASE( "to_string", "[uri]" )
{
    Uri uri( "https://source.corvusoft.co.uk" );
    
    REQUIRE( uri.to_string( ) == "https://source.corvusoft.co.uk" );
}

TEST_CASE( "valid is_valid", "[uri]" )
{
    REQUIRE( Uri::is_valid( "ws://restq.corvusoft.co.uk:443/queues" ) );
}

TEST_CASE( "invalid is_valid", "[uri]" )
{
    REQUIRE( Uri::is_valid( "---_)(*&" ) == false );
}

TEST_CASE( "parse", "[uri]" )
{
    Uri uri = Uri::parse( "http://shard.corvusoft.co.uk" );
    
    const string value = uri.to_string( );
    REQUIRE( value == "http://shard.corvusoft.co.uk" );
}

TEST_CASE( "invalid parse", "[uri]" )
{
    REQUIRE_THROWS_AS( Uri::parse( "---_)(*&" ), invalid_argument );
}

TEST_CASE( "empty parse", "[uri]" )
{
    REQUIRE_THROWS_AS( Uri::parse( "" ), invalid_argument );
}

TEST_CASE( "decode", "[uri]" )
{
    REQUIRE( Uri::decode( "file:///tmp/a%2Eb/tmp_20482932.txt" ) == "file:///tmp/a.b/tmp_20482932.txt" );
}

TEST_CASE( "decode_parameter", "[uri]" )
{
    REQUIRE( Uri::decode_parameter( "Corvusoft+Solutions" ) == "Corvusoft Solutions" );
}

TEST_CASE( "encode", "[uri]" )
{
    REQUIRE( Uri::encode( "a=b" ) == "a%3Db" );
}

TEST_CASE( "encode parameter", "[uri]" )
{
    REQUIRE( Uri::encode_parameter( "a=b" ) == "a%3Db" );
}
