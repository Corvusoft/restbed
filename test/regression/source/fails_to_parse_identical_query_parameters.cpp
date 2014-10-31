/*
 * Copyright (c) 2013, 2014 Corvusoft
 *
 * bug tracker issue #60
 */

//System Includes
#include <map>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

//Project Includes
#include <restbed>
#include "helpers/http.h"

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::multimap;
using std::make_pair;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using namespace restbed;

//External Namespaces

Response get_handler( const Request& request )
{
    Response response;
    response.set_status_code( StatusCode::OK );
    
    multimap< string, string > expectation;
    expectation.insert( make_pair( "echo", "false" ) );
    expectation.insert( make_pair( "echo", "true" ) );

    const auto actual = request.get_query_parameters( "echo" );
    
    if ( actual not_eq expectation )
    {
        response.set_status_code( StatusCode::INTERNAL_SERVER_ERROR );
    }

    return response;
}

TEST( Service, fails_to_parse_identical_query_parameters )
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
    
    auto response = Http::get( "http://localhost:1984/test?echo=false&echo=true" );
    
    EXPECT_EQ( "200", response[ "Status Code" ] );
    
    service->stop( );
}
