/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restbed/mode>
#include <corvusoft/restbed/settings>

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::map;
using std::string;

//Project Namespaces
using restbed::Mode;
using restbed::Settings;

//External Namespaces

TEST( Settings, port_accessor )
{
	Settings settings;
	settings.set_mode( Mode::ASYNCHRONOUS );

	EXPECT_EQ( Mode::ASYNCHRONOUS, settings.get_mode( ) );
}
