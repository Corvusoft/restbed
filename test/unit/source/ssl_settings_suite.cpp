/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <string>

//Project Includes
#include <corvusoft/restbed/ssl_settings>

//External Includes
#include <catch.hpp>
#include <framework>

//System Namespaces
using std::string;

//Project Namespaces
using restbed::SSLSettings;

//External Namespaces
using framework::Uri;

TEST_CASE( "validate default instance values", "[ssl-settings]" )
{
    const SSLSettings settings;

    REQUIRE( settings.get_port( ) == 443 );
    REQUIRE( settings.has_enabled_sslv2( ) );
    REQUIRE( settings.has_enabled_sslv3( ) );
    REQUIRE( settings.has_enabled_tlsv1( ) );
    REQUIRE( settings.has_enabled_tlsv11( ) );
    REQUIRE( settings.has_enabled_tlsv12( ) );
    REQUIRE( settings.has_enabled_compression( ) );
    REQUIRE( settings.has_enabled_default_workarounds( ) );
    REQUIRE( settings.has_enabled_single_diffie_hellman_use( ) );
    REQUIRE( settings.get_certificate( ).empty( ) );
    REQUIRE( settings.get_private_key( ).empty( ) );
    REQUIRE( settings.get_private_rsa_key( ).empty( ) );
    REQUIRE( settings.get_certificate_chain( ).empty( ) );
    REQUIRE( settings.get_temporary_diffie_hellman( ).empty( ) );
    REQUIRE( settings.get_certificate_authority_pool( ).empty( ) );
}

TEST_CASE( "confirm default destructor throws no exceptions", "[ssl-settings]" )
{
    auto settings = new SSLSettings;

    REQUIRE_NOTHROW( delete settings );
}

TEST_CASE( "validate setters modify default values", "[settings]" )
{
    SSLSettings settings;
    settings.set_port( 8080 );
    settings.set_sslv2_enabled( false );
    settings.set_sslv3_enabled( false );
    settings.set_tlsv1_enabled( false );
    settings.set_tlsv11_enabled( false );
    settings.set_tlsv12_enabled( false );
    settings.set_compression_enabled( false );
    settings.set_default_workarounds_enabled( false );
    settings.set_single_diffie_hellman_use_enabled( false );
    settings.set_certificate( Uri( "file:///tmp/server.crt" ) );
    settings.set_private_key( Uri( "file:///tmp/server.key" ) );
    settings.set_private_rsa_key( Uri( "file:///tmp/rsa.key" ) );
    settings.set_certificate_chain( Uri( "file:///tmp/chain.crt" ) );
    settings.set_certificate_authority_pool( Uri( "file:///tmp" ) );
    settings.set_temporary_diffie_hellman( Uri( "file:///tmp/dh512.pem" ) );

    REQUIRE( settings.get_port( ) == 8080 );
    REQUIRE( not settings.has_enabled_sslv2( ) );
    REQUIRE( not settings.has_enabled_sslv3( ) );
    REQUIRE( not settings.has_enabled_tlsv1( ) );
    REQUIRE( not settings.has_enabled_tlsv11( ) );
    REQUIRE( not settings.has_enabled_tlsv12( ) );
    REQUIRE( not settings.has_enabled_compression( ) );
    REQUIRE( not settings.has_enabled_default_workarounds( ) );
    REQUIRE( not settings.has_enabled_single_diffie_hellman_use( ) );
    REQUIRE( settings.get_certificate( ) == "/tmp/server.crt" );
    REQUIRE( settings.get_private_key( ) == "/tmp/server.key" );
    REQUIRE( settings.get_private_rsa_key( ) == "/tmp/rsa.key" );
    REQUIRE( settings.get_certificate_chain( ) == "/tmp/chain.crt" );
    REQUIRE( settings.get_temporary_diffie_hellman( ) == "/tmp/dh512.pem" );
    REQUIRE( settings.get_certificate_authority_pool( ) == "/tmp" );
}
