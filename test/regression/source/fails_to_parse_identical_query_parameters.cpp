/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 *
 * bug tracker issue #60
 */

//System Includes
#include <map>
#include <string>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>
#include <corvusoft/framework/http>

//System Namespaces
using std::string;
using std::multimap;
using std::make_pair;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces
using namespace framework;

Response get_handler( const Request& request )
{
    Response response;
    response.set_status_code( 200 );
    
    multimap< string, string > expectation;
    expectation.insert( make_pair( "echo", "false" ) );
    expectation.insert( make_pair( "echo", "true" ) );

    const auto actual = request.get_query_parameters( "echo" );
    
    if ( actual not_eq expectation )
    {
        response.set_status_code( 500 );
    }

    return response;
}

TEST_CASE( "fails to parse identical query parameters", "[service]" )
{
    Resource resource;
    resource.set_path( "test" );
    resource.set_method_handler( "GET", &get_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    settings.set_mode( ASYNCHRONOUS );
    
    auto service = make_shared< Service >( settings );
    service->publish( resource );
    
    service->start( );

    Http::Request request;
    request.method = "GET";
    request.port = 1984;
    request.host = "localhost";
    request.path = "/test?echo=false&echo=true";

    auto response = Http::get( request );
    
    REQUIRE( 200 == response.status_code );
    
    service->stop( );
}
