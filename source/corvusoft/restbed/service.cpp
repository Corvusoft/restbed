/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <functional>

//Project Includes
#include "corvusoft/restbed/mode.h"
#include "corvusoft/restbed/logger.h"
#include "corvusoft/restbed/service.h"
#include "corvusoft/restbed/response.h"
#include "corvusoft/restbed/settings.h"
#include "corvusoft/restbed/log_level.h"
#include "corvusoft/restbed/detail/service_impl.h"

//External Includes

//System Namespaces
using std::string;
using std::function;
using std::shared_ptr;

//Project Namespaces
using restbed::detail::ServiceImpl;

//External Namespaces

namespace restbed
{
    Service::Service( const Settings& settings ) : m_pimpl( new ServiceImpl( settings ) )
    {
        //n/a
    }
    
    Service::Service( const Service& original ) : m_pimpl( new ServiceImpl( *original.m_pimpl ) )
    {
        //n/a
    }
    
    Service::Service( const ServiceImpl& implementation ) : m_pimpl( new ServiceImpl( implementation ) )
    {
        //n/a
    }
    
    Service::~Service( void )
    {
        //n/a
    }
    
    void Service::start( void )
    {
        m_pimpl->start( );
    }
    
    void Service::start( const Mode& value )
    {
        m_pimpl->start( value );
    }
    
    void Service::stop( void )
    {
        m_pimpl->stop( );
    }
    
    void Service::publish( const Resource& value )
    {
        m_pimpl->publish( value );
    }
    
    void Service::suppress( const Resource& value )
    {
        m_pimpl->suppress( value );
    }
    
    void Service::set_logger( const shared_ptr< Logger >& value )
    {
        m_pimpl->set_log_handler( value );
    }
    
    void Service::set_authentication_handler( function< void ( const Request&, Response& ) > value )
    {
        m_pimpl->set_authentication_handler( value );
    }
    
    void Service::set_error_handler( function< void ( const int, const Request&, Response& ) > value )
    {
        m_pimpl->set_error_handler( value );
    }
    
    Service& Service::operator =( const Service& value )
    {
        *m_pimpl = *value.m_pimpl;
        
        return *this;
    }
}
