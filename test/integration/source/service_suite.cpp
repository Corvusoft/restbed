/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include <corvusoft/restbed/service>
#include <corvusoft/restbed/settings>

//External Includes
#include <gtest/gtest.h>

//System Namespaces

//Project Namespaces
using restbed::Service;
using restbed::Settings;

//External Namespaces

TEST( Service, constructor )
{
    Settings settings;
    
    Service service( settings );
    
    EXPECT_TRUE( true );
}

TEST( Service, destructor )
{
    Settings settings;
    
    ASSERT_NO_THROW(
    {
        Service* service = new Service( settings );
        
        delete service;
    } );
}
