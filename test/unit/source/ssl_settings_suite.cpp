/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <string>
#include <ciso646>

//Project Includes
#include <corvusoft/restbed/ssl_settings.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;

//Project Namespaces
using restbed::SSLSettings;

//External Namespaces

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
    REQUIRE( settings.get_bind_address( ).empty( ) );
    REQUIRE( settings.get_passphrase( ).empty( ) );
    REQUIRE( settings.get_certificate( ).empty( ) );
    REQUIRE( settings.get_private_key( ).empty( ) );
    REQUIRE( settings.get_private_rsa_key( ).empty( ) );
    REQUIRE( settings.get_certificate_chain( ).empty( ) );
    REQUIRE( settings.get_temporary_diffie_hellman( ).empty( ) );
    REQUIRE( settings.get_certificate_authority_pool( ).empty( ) );
    REQUIRE( settings.has_disabled_http( ) == false );
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
    settings.set_http_disabled( true );
    settings.set_compression_enabled( false );
    settings.set_default_workarounds_enabled( false );
    settings.set_single_diffie_hellman_use_enabled( false );
    settings.set_bind_address( "127.0.0.1" );
    settings.set_passphrase( "my-passphrase" );
    
    REQUIRE( settings.get_port( ) == 8080 );
    REQUIRE( not settings.has_enabled_sslv2( ) );
    REQUIRE( not settings.has_enabled_sslv3( ) );
    REQUIRE( not settings.has_enabled_tlsv1( ) );
    REQUIRE( not settings.has_enabled_tlsv11( ) );
    REQUIRE( not settings.has_enabled_tlsv12( ) );
    REQUIRE( not settings.has_enabled_compression( ) );
    REQUIRE( not settings.has_enabled_default_workarounds( ) );
    REQUIRE( not settings.has_enabled_single_diffie_hellman_use( ) );
    REQUIRE( settings.get_bind_address( ) == "127.0.0.1" );
    REQUIRE( settings.get_passphrase( ) == "my-passphrase" );
    REQUIRE( settings.has_disabled_http( ) == true );
}
