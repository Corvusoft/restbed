/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/logger.h"
#include "corvusoft/restbed/service.h"
#include "corvusoft/restbed/session.h"
#include "corvusoft/restbed/resource.h"
#include "corvusoft/restbed/settings.h"
#include "corvusoft/restbed/detail/service_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::string;
using std::function;
using std::shared_ptr;

//Project Namespaces
using restbed::detail::ServiceImpl;

//External Namespaces

namespace restbed
{
    Service::Service( void ) : m_pimpl( new ServiceImpl )
    {
        return;
    }
    
    Service::~Service( void )
    {
        return;
    }
    
    void Service::stop( void )
    {
        m_pimpl->stop( );
    }
    
    void Service::start( const shared_ptr< Settings >& settings )
    {
        m_pimpl->start( settings );
    }
    
    void Service::publish( const shared_ptr< Resource >& resource )
    {
        m_pimpl->publish( resource );
    }
    
    void Service::suppress( const shared_ptr< Resource >& resource )
    {
        m_pimpl->suppress( resource );
    }

    void Service::set_logger( const shared_ptr< Logger >& value )
    {
        m_pimpl->set_logger( value );
    }

    void Service::set_not_found_handler( const function< void ( const shared_ptr< Session >& ) >& value )
    {
        m_pimpl->set_not_found_handler( value );
    }

    void Service::set_method_not_allowed_handler( const function< void ( const shared_ptr< Session >& ) >& value )
    {
        m_pimpl->set_method_not_allowed_handler( value );
    }

    void Service::set_method_not_implemented_handler( const function< void ( const shared_ptr< Session >& ) >& value )
    {
        m_pimpl->set_method_not_implemented_handler( value );
    }

    void Service::set_failed_filter_validation_handler( const function< void ( const shared_ptr< Session >& ) >& value )
    {
        m_pimpl->set_failed_filter_validation_handler( value );
    }

    void Service::set_authentication_handler( const function< void ( const shared_ptr< Session >&,
                                                                     const std::function< void ( const std::shared_ptr< Session >& ) >& ) >& value )
    {
        m_pimpl->set_authentication_handler( value );
    }
    
    void Service::set_error_handler( function< void ( const int, const shared_ptr< Session >& ) > value )
    {
        m_pimpl->set_error_handler( value );
    }
}
