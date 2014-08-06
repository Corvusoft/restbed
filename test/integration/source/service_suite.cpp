/*
 * Copyright (c) 2013, 2014 Corvusoft
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

TEST( Service, destructor )
{
    const Settings settings;
    
    ASSERT_NO_THROW(
    {
        Service* service = new Service( settings );
        
        delete service;
    } );
}

TEST( Service, assignment_operator )
{
    Settings settings;
    settings.set_port( 8732 );
    
    const Service lhs( settings );
    
    const Service rhs = lhs;
    
    EXPECT_TRUE( true );
}
