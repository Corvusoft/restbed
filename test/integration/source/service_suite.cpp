/*
 * Site: restbed.corvusoft.co.uk
 * Author: Ben Crowhurst
 *
 * Copyright (c) 2013 Restbed Core Development Team and Community Contributors
 *
 * This file is part of Restbed.
 *
 * Restbed is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Restbed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with Restbed.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes

//Project Includes

//External Includes
#include <gtest/gtest.h>
#include <restbed/service>
#include <restbed/settings>

//System Namespaces

//Project Namespaces

//External Namespaces
using restbed::Service;
using restbed::Settings;

TEST( Service, default_destructor )
{
    const Settings settings;

    ASSERT_NO_THROW({
        Service* service = new Service( settings );
        
        delete service;
    });
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
