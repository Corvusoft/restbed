/*
 * Copyright (c) 2013, 2014 Corvusoft
 *
 * bug tracker issue #24
 */

//System Includes
#include <regex>

//Project Includes

//External Includes
#include <gtest/gtest.h>

//System Namespaces

//Project Namespaces
using std::regex;

//External Namespaces

TEST( Service, missing_regex_support )
{
    ASSERT_NO_THROW( regex( "(abc[1234])" ) );
}
