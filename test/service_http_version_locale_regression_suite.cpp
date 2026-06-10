/*
 * Copyright 2013-2026, Corvusoft Ltd, All Rights Reserved.
 *
 * Regression: the HTTP request-line version was parsed with std::stod wrapped
 * in a process-global setlocale( LC_NUMERIC, "C" ) override -- a data race on
 * the io_context worker pool. ServiceImpl::parse_http_version now uses
 * std::from_chars, which is locale-independent and touches no global state.
 *
 * Under a comma-decimal locale a locale-sensitive parser reads "1.1" as 1.0;
 * from_chars still yields 1.1. (If the locale below is unavailable the process
 * stays in "C" and the assertions still hold.)
 */

//System Includes
#include <clocale>

//Project Includes
#include <corvusoft/restbed/logger.hpp>
#include <corvusoft/restbed/request.hpp>
#include <corvusoft/restbed/detail/service_impl.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//Project Namespaces
using restbed::detail::ServiceImpl;

//External Namespaces

TEST_CASE( "parse_http_version is independent of the global locale", "[service]" )
{
    std::setlocale( LC_ALL, "de_DE.utf8" );

    REQUIRE( ServiceImpl::parse_http_version( "1.1" ) == 1.1 );
    REQUIRE( ServiceImpl::parse_http_version( "1.0" ) == 1.0 );
    REQUIRE( ServiceImpl::parse_http_version( "2.0" ) == 2.0 );

    std::setlocale( LC_ALL, "C" );
}

int main( int argc, char* argv[] )
{
    return Catch::Session().run( argc, argv );
}
