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

TEST( Service, default_destructor )
{
    const Settings settings;
    
    ASSERT_NO_THROW(
    {
        Service* service = new Service( settings );
        
        delete service;
    } );
}

TEST( Service, less_than_operator )
{
    Settings settings;
    settings.set_port( 9 );
    
    const Service lhs( settings );
    
    settings.set_port( 11 );
    const Service rhs( settings );
    
    EXPECT_TRUE( lhs < rhs );
}

TEST( Service, greater_than_operator )
{
    Settings settings;
    settings.set_port( 88 );
    
    const Service lhs( settings );
    
    settings.set_port( 1 );
    const Service rhs( settings );
    
    EXPECT_TRUE( lhs > rhs );
}

TEST( Service, equality_operator )
{
    Settings settings;
    settings.set_port( 88 );
    
    const Service lhs( settings );
    
    const Service rhs( settings );
    
    EXPECT_TRUE( lhs == rhs );
}

TEST( Service, negated_equality_operator )
{
    Settings settings;
    settings.set_port( 8999 );
    
    const Service lhs( settings );
    
    settings.set_port( 12 );
    const Service rhs( settings );
    
    EXPECT_TRUE( lhs != rhs );
}

TEST( Service, assignment_operator )
{
    Settings settings;
    settings.set_port( 8732 );
    
    const Service lhs( settings );
    
    const Service rhs = lhs;
    
    EXPECT_TRUE( lhs == rhs );
}
