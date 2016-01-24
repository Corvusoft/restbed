/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <memory>
#include <stdexcept>

//Project Includes
#include <corvusoft/restbed/http.hpp>
#include <corvusoft/restbed/request.hpp>
#include <corvusoft/restbed/response.hpp>
#include <corvusoft/restbed/settings.hpp>
#include <corvusoft/restbed/ssl_settings.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;

//Project Namespaces
using restbed::Http;
using restbed::Request;
using restbed::Response;
using restbed::Settings;
using restbed::SSLSettings;

//External Namespaces

#ifdef BUILD_SSL
TEST_CASE( "validate runtime_error is not thrown when SSLSettings passed into sync", "[client]" )
{
    const auto settings = make_shared< SSLSettings >( );
    
    auto request = make_shared< Request >( );
    
    REQUIRE_NOTHROW( Http::sync( request, settings ) );
}
#else
TEST_CASE( "validate runtime_error is thrown when SSLSettings passed into sync", "[client]" )
{
    const auto settings = make_shared< SSLSettings >( );
    
    auto request = make_shared< Request >( );
    
    REQUIRE_THROWS_AS( Http::sync( request, settings ), runtime_error );
}
#endif
