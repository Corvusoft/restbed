/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <thread>
#include <vector>
#include <utility>
#include <cstdint>
#include <ciso646>
#include <stdexcept>
#include <algorithm>
#include <functional>

//Project Includes
#include "corvusoft/restbed/uri.hpp"
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
#include "corvusoft/restbed/detail/web_socket_manager_impl.hpp"

//External Includes
#include <asio/io_service.hpp>
#include <asio/steady_timer.hpp>

#ifdef BUILD_SSL
    #include <asio/ssl.hpp>
#endif

//System Namespaces
using std::map;
using std::bind;
using std::thread;
using std::string;
using std::vector;
using std::function;
using std::exception;
using std::to_string;
using std::unique_ptr;
using std::shared_ptr;
using std::error_code;
using std::make_shared;
using std::stable_sort;
using std::runtime_error;
using std::chrono::seconds;
using std::invalid_argument;
using std::chrono::milliseconds;
using std::chrono::steady_clock;
using std::chrono::duration_cast;

//Project Namespaces
using restbed::detail::ServiceImpl;
using restbed::detail::WebSocketManagerImpl;

//External Namespaces
using asio::io_service;
using asio::steady_timer;

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
            m_pimpl->log( Logger::WARNING, "Service failed graceful wind down." );
        }
    }
    
    bool Service::is_up( void ) const
    {
        return m_pimpl->m_uptime not_eq steady_clock::time_point::min( );
    }
    
    bool Service::is_down( void ) const
    {
        return not is_up( );
    }
    
    void Service::stop( void )
    {
        m_pimpl->m_uptime = steady_clock::time_point::min( );
        
        if ( m_pimpl->m_io_service not_eq nullptr )
        {
            m_pimpl->m_io_service->stop( );
        }
        
        if ( m_pimpl->m_session_manager not_eq nullptr )
        {
            m_pimpl->m_session_manager->stop( );
        }
        
        for ( auto& worker : m_pimpl->m_workers )
        {
            worker->join( );
        }
        
        m_pimpl->m_workers.clear( );
        
        if ( m_pimpl->m_logger not_eq nullptr )
        {
            m_pimpl->log( Logger::INFO, "Service halted." );
            m_pimpl->m_logger->stop( );
        }
    }
    
    void Service::start( const shared_ptr< const Settings >& settings )
    {
        m_pimpl->setup_signal_handler( );
        
        m_pimpl->m_settings = settings;
        
        if ( m_pimpl->m_settings == nullptr )
        {
            m_pimpl->m_settings = make_shared< Settings >( );
        }
        
#ifdef BUILD_SSL
        m_pimpl->m_ssl_settings = m_pimpl->m_settings->get_ssl_settings( );
#else
        
        if ( m_pimpl->m_settings->get_ssl_settings( ) not_eq nullptr )
        {
            throw runtime_error( "Not Implemented! Rebuild Restbed with SSL funcationality enabled." );
        }
        
#endif
        
        if ( m_pimpl->m_logger not_eq nullptr )
        {
            m_pimpl->m_logger->start( m_pimpl->m_settings );
        }
        
        if ( m_pimpl->m_session_manager == nullptr )
        {
            m_pimpl->m_session_manager = make_shared< SessionManager >( );
        }
        
        m_pimpl->m_session_manager->start( m_pimpl->m_settings );
        
        m_pimpl->m_web_socket_manager = make_shared< WebSocketManagerImpl >( );
        
        stable_sort( m_pimpl->m_rules.begin( ), m_pimpl->m_rules.end( ), [ ]( const shared_ptr< const Rule >& lhs, const shared_ptr< const Rule >& rhs )
        {
            return lhs->get_priority( ) < rhs->get_priority( );
        } );
        
        m_pimpl->http_start( );
#ifdef BUILD_SSL
        m_pimpl->https_start( );
#endif
        
        for ( const auto& route : m_pimpl->m_resource_paths )
        {
            auto path = String::format( "/%s/%s", m_pimpl->m_settings->get_root( ).data( ), route.second.data( ) );
            path = String::replace( "//", "/", path );
            
            m_pimpl->log( Logger::INFO, String::format( "Resource published on route '%s'.", path.data( ) ) );
        }
        
        if ( m_pimpl->m_ready_handler not_eq nullptr )
        {
            m_pimpl->m_io_service->post( m_pimpl->m_ready_handler );
        }
        
        m_pimpl->m_uptime = steady_clock::now( );
        unsigned int limit = m_pimpl->m_settings->get_worker_limit( );
        
        if ( limit > 0 )
        {
            const auto this_thread = 1;
            limit = limit - this_thread;
            
            for ( unsigned int count = 0;  count < limit; count++ )
            {
                auto worker = make_shared< thread >( [ this ]( )
                {
                    m_pimpl->m_io_service->run( );
                } );
                
                m_pimpl->m_workers.push_back( worker );
            }
        }
        
        m_pimpl->m_io_service->run( );
    }
    
    void Service::restart( const shared_ptr< const Settings >& settings )
    {
        try
        {
            stop( );
        }
        catch ( ... )
        {
            m_pimpl->log( Logger::WARNING, "Service failed graceful reboot." );
        }
        
        start( settings );
    }
    
    void Service::add_rule( const shared_ptr< Rule >& rule )
    {
        if ( is_up( ) )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        if ( rule not_eq nullptr )
        {
            m_pimpl->m_rules.push_back( rule );
        }
    }
    
    void Service::add_rule( const shared_ptr< Rule >& rule, const int priority )
    {
        if ( is_up( ) )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        if ( rule not_eq nullptr )
        {
            rule->set_priority( priority );
            m_pimpl->m_rules.push_back( rule );
        }
    }
    
    void Service::publish( const shared_ptr< const Resource >& resource )
    {
        if ( is_up( ) )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        if ( resource == nullptr )
        {
            return;
        }
        
        auto paths = resource->m_pimpl->m_paths;
        
        if ( not m_pimpl->has_unique_paths( paths ) )
        {
            throw invalid_argument( "Resource would pollute namespace. Please ensure all published resources have unique paths." );
        }
        
        for ( auto& path : paths )
        {
            const string sanitised_path = m_pimpl->sanitise_path( path );
            
            m_pimpl->m_resource_paths[ sanitised_path ] = path;
            m_pimpl->m_resource_routes[ sanitised_path ] = resource;
        }
        
        const auto& methods = resource->m_pimpl->m_methods;
        m_pimpl->m_supported_methods.insert( methods.begin( ), methods.end( ) );
    }
    
    void Service::suppress( const shared_ptr< const Resource >& resource )
    {
        if ( is_up( ) )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        if ( resource == nullptr )
        {
            return;
        }
        
        for ( const auto& path : resource->m_pimpl->m_paths )
        {
            if ( m_pimpl->m_resource_routes.erase( path ) )
            {
                m_pimpl->log( Logger::INFO, String::format( "Suppressed resource route '%s'.", path.data( ) ) );
            }
            else
            {
                m_pimpl->log( Logger::WARNING, String::format( "Failed to suppress resource route '%s'; Not Found!", path.data( ) ) );
            }
        }
    }
    
    void Service::schedule( const function< void ( void ) >& task, const milliseconds& interval )
    {
        if ( task == nullptr )
        {
            return;
        }
        
        if ( interval == milliseconds::zero( ) )
        {
            m_pimpl->m_io_service->post( task );
            return;
        }
        
        auto timer = make_shared< steady_timer >( *m_pimpl->m_io_service );
        timer->expires_from_now( interval );
        timer->async_wait( [ this, task, interval, timer ]( const error_code& )
        {
            task( );
            schedule( task, interval );
        } );
    }
    
    const seconds Service::get_uptime( void ) const
    {
        if ( is_down( ) )
        {
            return seconds( 0 );
        }
        
        return duration_cast< seconds >( steady_clock::now( ) - m_pimpl->m_uptime );
    }
    
    const shared_ptr< const Uri > Service::get_http_uri( void ) const
    {
        return m_pimpl->get_http_uri( );
    }
    
    const shared_ptr< const Uri > Service::get_https_uri( void ) const
    {
        return m_pimpl->get_https_uri( );
    }
    
    void Service::set_logger( const shared_ptr< Logger >& value )
    {
        if ( is_up( ) )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        m_pimpl->m_logger = value;
    }
    
    void Service::set_session_manager( const shared_ptr< SessionManager >& value )
    {
        if ( is_up( ) )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        m_pimpl->m_session_manager = value;
    }
    
    void Service::set_ready_handler( const function< void ( Service& ) >& value )
    {
        if ( is_up( ) )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        if ( value not_eq nullptr )
        {
            m_pimpl->m_ready_handler = bind( value, std::ref( *this ) );
        }
    }
    
    void Service::set_signal_handler( const int signal, const function< void ( const int ) >& value )
    {
        if ( is_up( ) )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        if ( value not_eq nullptr )
        {
            m_pimpl->m_signal_handlers[ signal ] = value;
        }
    }
    
    void Service::set_not_found_handler( const function< void ( const shared_ptr< Session > ) >& value )
    {
        if ( is_up( ) )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        m_pimpl->m_not_found_handler = value;
    }
    
    void Service::set_method_not_allowed_handler( const function< void ( const shared_ptr< Session > ) >& value )
    {
        if ( is_up( ) )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        m_pimpl->m_method_not_allowed_handler = value;
    }
    
    void Service::set_method_not_implemented_handler( const function< void ( const shared_ptr< Session > ) >& value )
    {
        if ( is_up( ) )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        m_pimpl->m_method_not_implemented_handler = value;
    }
    
    void Service::set_failed_filter_validation_handler( const function< void ( const shared_ptr< Session > ) >& value )
    {
        if ( is_up( ) )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        m_pimpl->m_failed_filter_validation_handler = value;
    }
    
    void Service::set_error_handler( const function< void ( const int, const exception&, const shared_ptr< Session > ) >& value )
    {
        if ( is_up( ) )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        if ( value == nullptr )
        {
            m_pimpl->m_error_handler = ServiceImpl::default_error_handler;
        }
        
        m_pimpl->m_error_handler = value;
    }
    
    void Service::set_authentication_handler( const function< void ( const shared_ptr< Session >, const function< void ( const shared_ptr< Session > ) >& ) >& value )
    {
        if ( is_up( ) )
        {
            throw runtime_error( "Runtime modifications of the service are prohibited." );
        }
        
        m_pimpl->m_authentication_handler = value;
    }
}
