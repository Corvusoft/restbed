/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/logger.hpp"
#include "corvusoft/restbed/service.hpp"
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/resource.hpp"
#include "corvusoft/restbed/settings.hpp"
#include "corvusoft/restbed/ssl_settings.hpp"
#include "corvusoft/restbed/detail/service_impl.hpp"

//External Includes

//System Namespaces
using std::map;
using std::string;
using std::function;
using std::exception;
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
    
    void Service::start( const shared_ptr< const Settings >& settings )
    {
        m_pimpl->start( settings, nullptr );
    }

    void Service::start( const shared_ptr< const SSLSettings >& settings )
    {
        m_pimpl->start( nullptr, settings );
    }
    
    void Service::start( const shared_ptr< const Settings >& settings, const shared_ptr< const SSLSettings >& ssl_settings )
    {
        m_pimpl->start( settings, ssl_settings );
    }

    void Service::restart( const shared_ptr< const Settings >& settings )
    {
        m_pimpl->restart( settings, nullptr );
    }

    void Service::restart( const shared_ptr< const SSLSettings >& settings )
    {
        m_pimpl->restart( nullptr, settings );
    }

    void Service::restart( const shared_ptr< const Settings >& settings, const shared_ptr< const SSLSettings >& ssl_settings )
    {
        m_pimpl->restart( settings, ssl_settings );
    }
    
    void Service::publish( const shared_ptr< const Resource >& resource )
    {
        m_pimpl->publish( resource );
    }
    
    void Service::suppress( const shared_ptr< const Resource >& resource )
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
    
    void Service::set_error_handler( function< void ( const int, const exception&, const shared_ptr< Session >& ) > value )
    {
        m_pimpl->set_error_handler( value );
    }
    
    void Service::set_authentication_handler( const function< void ( const shared_ptr< Session >&, const function< void ( const shared_ptr< Session >& ) >& ) >& value )
    {
        m_pimpl->set_authentication_handler( value );
    }
}
