/*
 * Copyright (c) 2013 Corvusoft
 */

/*
 * See issue tracker bug #2 for details.
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes
#include <memory>
#include <functional>

//Project Includes
#include <restbed>
#include "helpers/http.h"
#include "fixtures/service_fixture.h"

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::bind;
using std::shared_ptr;
using std::placeholders::_1;

//Project Namespaces
using namespace restbed;

//External Namespaces

TEST_F( ServiceFixture, mismatched_resource_path_of_equal_path_segments )
{
	auto response = Http::get( "http://localhost:1984/tests" );
	
	EXPECT_EQ( "404", response[ "Status Code" ] );
}

TEST_F( ServiceFixture, mismatched_resource_path_of_unequal_path_segments )
{
	auto response = Http::get( "http://localhost:1984/event/test" );
	
	EXPECT_EQ( "404", response[ "Status Code" ] );
}

TEST_F( ServiceFixture, matched_resource_path )
{
	auto response = Http::get( "http://localhost:1984/test" );
	
	EXPECT_EQ( "200", response[ "Status Code" ] );
}
