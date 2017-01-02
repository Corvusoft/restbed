/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <string>

//Project Includes
#include <corvusoft/restbed/uri.hpp>
#include <corvusoft/restbed/ssl_settings.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;

//Project Namespaces
using restbed::Uri;
using restbed::SSLSettings;

//External Namespaces

TEST_CASE( "validate setters modify default values", "[settings]" )
{
    SSLSettings settings;
    settings.set_certificate( Uri( "file:///tmp/server.crt" ) );
    settings.set_private_key( Uri( "file:///tmp/server.key" ) );
    settings.set_private_rsa_key( Uri( "file:///tmp/rsa.key" ) );
    settings.set_certificate_chain( Uri( "file:///tmp/chain.crt" ) );
    settings.set_certificate_authority_pool( Uri( "file:///tmp" ) );
    settings.set_temporary_diffie_hellman( Uri( "file:///tmp/dh512.pem" ) );
    
    REQUIRE( settings.get_certificate( ) == "/tmp/server.crt" );
    REQUIRE( settings.get_private_key( ) == "/tmp/server.key" );
    REQUIRE( settings.get_private_rsa_key( ) == "/tmp/rsa.key" );
    REQUIRE( settings.get_certificate_chain( ) == "/tmp/chain.crt" );
    REQUIRE( settings.get_temporary_diffie_hellman( ) == "/tmp/dh512.pem" );
    REQUIRE( settings.get_certificate_authority_pool( ) == "/tmp" );
}
