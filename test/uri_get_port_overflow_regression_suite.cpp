/*
 * Copyright 2013-2026, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <cstdint>

//Project Includes
#include <corvusoft/restbed/uri.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::uint16_t;

//Project Namespaces
using restbed::Uri;

//External Namespaces

TEST_CASE( "uri get_port throws on out-of-range port", "[uri]" )
{
    // A port that does not fit in the numeric range stoi accepts causes get_port
    // to throw std::out_of_range. A malformed/hostile URI must not be able to
    // throw out of this accessor; an unparseable port should report 0 (the same
    // sentinel already used when no port is present).
    const Uri uri( "http://www.corvusoft.co.uk:99999999999/resource" );

    uint16_t port = 1;
    REQUIRE_NOTHROW( port = uri.get_port( ) );
    REQUIRE( port == 0 );
}

TEST_CASE( "uri get_port does not silently truncate above 65535", "[uri]" )
{
    // 65537 silently truncates to 1 via the uint16_t cast -- a hostile URI can
    // masquerade as a valid low port. An out-of-range port must report the 0
    // sentinel instead.
    const Uri uri( "http://www.corvusoft.co.uk:65537/resource" );

    uint16_t port = 1;
    REQUIRE_NOTHROW( port = uri.get_port( ) );
    REQUIRE( port == 0 );
}

int main( int argc, char* argv[] )
{
    return Catch::Session().run( argc, argv );
}
