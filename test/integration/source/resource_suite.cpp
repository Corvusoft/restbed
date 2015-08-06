/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <string>
#include <memory>
#include <stdexcept>

//Project Includes
#include <corvusoft/restbed/session.hpp>
#include <corvusoft/restbed/resource.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::shared_ptr;
using std::invalid_argument;

//Project Namespaces
using restbed::Session;
using restbed::Resource;

//External Namespaces

TEST_CASE( "validate invalid (empty) method argument", "[resource]" )
{
    Resource resource;
    const std::function< void ( const std::shared_ptr< Session >& ) > callback;
    
    REQUIRE_THROWS_AS( resource.set_method_handler( "", callback ), invalid_argument );
}
