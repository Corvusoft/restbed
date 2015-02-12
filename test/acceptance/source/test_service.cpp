/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include <restbed>
#include "test_logger.h"
#include "test_service.h"

//External Includes

//System Namespaces
using std::shared_ptr;

//Project Namespaces
using restbed::Service;
using restbed::Resource;
using restbed::Settings;

//External Namespaces

TestService::TestService( const Settings& settings ) : Service( settings ),
    m_resource( ),
    m_logger( new TestLogger )
{
    set_logger( m_logger );
}

TestService::~TestService( void )
{
    return;
}

void TestService::suppress_resource( void )
{
    suppress( m_resource );
}

void TestService::publish_resource( Resource& resource )
{
    m_resource = resource;
    
    publish( resource );
}

const char* TestService::get_log_entry( void ) const
{
    return m_logger->get_log_entry( );
}
