/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <functional>

//Project Includes
#include "corvusoft/restbed/rule.hpp"
#include "corvusoft/restbed/logger.hpp"
#include "corvusoft/restbed/service.hpp"
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/resource.hpp"
#include "corvusoft/restbed/settings.hpp"
#include "corvusoft/restbed/ssl_settings.hpp"
#include "corvusoft/restbed/session_manager.hpp"
#include "corvusoft/restbed/detail/service_impl.hpp"
#include "corvusoft/restbed/detail/resource_impl.hpp"

//External Includes
#include <asio.hpp>
#ifdef BUILD_SSL
    #include <asio/ssl.hpp>
#endif

//System Namespaces
using std::map;
using std::bind;
using std::string;
using std::vector;
using std::function;
using std::exception;
using std::to_string;
using std::shared_ptr;
using std::make_shared;
using std::stable_sort;
using std::runtime_error;
using std::invalid_argument;

//Project Namespaces
using restbed::detail::ServiceImpl;

//External Namespaces
using asio::io_service;

namespace restbed
{
    Service::Service( void ) : m_pimpl( new ServiceImpl )
    {
        return;
    }
    
    Service::~Service( void )
    {
        try
        {
            stop( );
        }
        catch ( ... )
        {
            m_pimpl->log( Logger::Level::WARNING, "Service failed graceful teardown." );
        }

        delete m_pimpl;
    }
    
    void Service::stop( void )
    {
        m_pimpl->is_running = false;
        
        if ( m_pimpl->io_service not_eq nullptr )
        {
            m_pimpl->io_service->stop( );
        }
        
        if ( m_pimpl->session_manager not_eq nullptr )
        {
            m_pimpl->session_manager->stop( );
        }

        m_pimpl->log( Logger::Level::INFO, String::format( "Service halted." ) );

        if ( m_pimpl->logger not_eq nullptr )
        {
            m_pimpl->logger->stop( );
        }
    }

    void Service::start( const shared_ptr< const Settings >& settings )
    {
        m_pimpl->settings = settings;

        if ( m_pimpl->settings == nullptr )
        {
            m_pimpl->settings = make_shared< Settings >( );
#ifdef BUILD_SSL
            m_pimpl->ssl_settings = m_pimpl->settings->get_ssl_settings( );
#endif
        }

        if ( m_pimpl->session_manager == nullptr )
        {
            m_pimpl->session_manager = make_shared< SessionManager >( );
        }
        
        m_pimpl->session_manager->start( m_pimpl->settings );
        
        if ( m_pimpl->logger not_eq nullptr )
        {
            m_pimpl->logger->start( m_pimpl->settings );
        }

        stable_sort( m_pimpl->rules.begin( ), m_pimpl->rules.end( ), [ ]( const shared_ptr< const Rule >& lhs, const shared_ptr< const Rule >& rhs )
        {
            return lhs->get_priority( ) < rhs->get_priority( );
        } );

        m_pimpl->io_service = make_shared< io_service >( );

        m_pimpl->http_start( );
#ifdef BUILD_SSL
        m_pimpl->https_start( );
#endif
        for ( const auto& route : m_pimpl->resource_paths )
        {
            auto path = String::format( "/%s/%s", m_pimpl->settings->get_root( ).data( ), route.second.data( ) );
            path = String::replace( "//", "/", path );
            
            m_pimpl->log( Logger::Level::INFO, String::format( "Resource published on route '%s'.", path.data( ) ) );
        }
        
        if ( m_pimpl->ready_handler not_eq nullptr )
        {
            m_pimpl->io_service->post( m_pimpl->ready_handler );
        }

        m_pimpl->is_running = true;
        m_pimpl->io_service->run( );
    }

    void Service::restart( const shared_ptr< const Settings >& settings )
    {
        try
        {
            stop( );
        }
        catch ( ... )
        {
            m_pimpl->log( Logger::Level::WARNING, "Service failed graceful teardown." );
        }
        
        start( settings );
    }

    void Service::add_rule( const shared_ptr< Rule >& rule )
    {
        if ( m_pimpl->is_running )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }

        m_pimpl->rules.push_back( rule );
    }

    void Service::add_rule( const shared_ptr< Rule >& rule, const int priority )
    {
        if ( m_pimpl->is_running )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }

        rule->set_priority( priority );
        m_pimpl->rules.push_back( rule );
    }

    void Service::publish( const shared_ptr< const Resource >& resource )
    {
        if ( m_pimpl->is_running )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        if ( resource == nullptr )
        {
            return;
        }
        
        auto paths = resource->m_pimpl->paths;
        
        if ( not m_pimpl->has_unique_paths( paths ) )
        {
            throw invalid_argument( "Resource would pollute namespace. Please ensure all published resources have unique paths." );
        }
        
        for ( auto& path : paths )
        {
            const string sanitised_path = m_pimpl->sanitise_path( path );
            
            m_pimpl->resource_paths[ sanitised_path ] = path;
            m_pimpl->resource_routes[ sanitised_path ] = resource;
        }
        
        const auto& methods = resource->m_pimpl->methods;
        m_pimpl->supported_methods.insert( methods.begin( ), methods.end( ) );
    }
    
    void Service::suppress( const shared_ptr< const Resource >& resource )
    {
        if ( m_pimpl->is_running )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        if ( resource == nullptr )
        {
            return;
        }
        
        for ( const auto& path : resource->m_pimpl->paths )
        {
            if ( m_pimpl->resource_routes.erase( path ) )
            {
                m_pimpl->log( Logger::Level::INFO, String::format( "Suppressed resource route '%s'.", path.data( ) ) );
            }
            else
            {
                m_pimpl->log( Logger::Level::WARNING, String::format( "Failed to suppress resource route '%s'; Not Found!", path.data( ) ) );
            }
        }
    }
    
    void Service::set_logger( const shared_ptr< Logger >& value )
    {
        if ( m_pimpl->is_running )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        m_pimpl->logger = value;
    }

    void Service::set_ready_handler( const function< void ( Service& ) >& value )
    {
        if ( m_pimpl->is_running )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }

        m_pimpl->ready_handler = bind( value, std::ref( *this ) );
    }
    
    void Service::set_not_found_handler( const function< void ( const shared_ptr< Session >& ) >& value )
    {
        if ( m_pimpl->is_running )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        m_pimpl->not_found_handler = value;
    }
    
    void Service::set_method_not_allowed_handler( const function< void ( const shared_ptr< Session >& ) >& value )
    {
        if ( m_pimpl->is_running )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        m_pimpl->method_not_allowed_handler = value;
    }
    
    void Service::set_method_not_implemented_handler( const function< void ( const shared_ptr< Session >& ) >& value )
    {
        if ( m_pimpl->is_running )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        m_pimpl->method_not_implemented_handler = value;
    }
    
    void Service::set_failed_filter_validation_handler( const function< void ( const shared_ptr< Session >& ) >& value )
    {
        if ( m_pimpl->is_running )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        m_pimpl->failed_filter_validation_handler = value;
    }
    
    void Service::set_error_handler( function< void ( const int, const exception&, const shared_ptr< Session >& ) > value )
    {
        if ( m_pimpl->is_running )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        m_pimpl->error_handler = value;
    }
    
    void Service::set_authentication_handler( const function< void ( const shared_ptr< Session >&, const function< void ( const shared_ptr< Session >& ) >& ) >& value )
    {
        if ( m_pimpl->is_running )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        m_pimpl->authentication_handler = value;
    }
}
