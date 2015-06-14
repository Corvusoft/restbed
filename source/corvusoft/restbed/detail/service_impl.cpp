/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <regex>
#include <cstdio>
#include <utility>
#include <stdexcept>
#include <functional>

//Project Includes
#include "corvusoft/restbed/logger.h"
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/session.h"
#include "corvusoft/restbed/resource.h"
#include "corvusoft/restbed/settings.h"
#include "corvusoft/restbed/status_code.h"
#include "corvusoft/restbed/session_manager.h"
#include "corvusoft/restbed/detail/request_impl.h"
#include "corvusoft/restbed/detail/service_impl.h"
#include "corvusoft/restbed/detail/session_impl.h"
#include "corvusoft/restbed/detail/resource_impl.h"
#include "corvusoft/restbed/detail/session_manager_impl.h"

//External Includes
#include <corvusoft/framework/string>

//System Namespaces
using std::set;
using std::pair;
using std::bind;
using std::regex;
using std::string;
using std::smatch;
using std::find_if;
using std::function;
using std::to_string;
using std::exception;
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;
using std::invalid_argument;
using std::placeholders::_1;

//Project Namespaces

//External Namespaces
using asio::ip::tcp;
using asio::io_service;
using asio::error_code;
using asio::socket_base;
using asio::system_error;
using framework::String;

namespace restbed
{
    namespace detail
    {
        ServiceImpl::ServiceImpl( void ) : m_is_running( false ),
            m_logger( nullptr ),
            m_supported_methods( ),
            m_settings( nullptr ),
            m_io_service( nullptr ),
            m_session_manager( nullptr ),
            m_acceptor( nullptr ),
            m_resource_paths( ),
            m_resource_routes( ),
            m_not_found_handler( nullptr ),
            m_method_not_allowed_handler( nullptr ),
            m_method_not_implemented_handler( nullptr ),
            m_failed_filter_validation_handler( nullptr ),
            m_error_handler( nullptr ),
            m_authentication_handler( nullptr )
        {
            return;
        }
        
        ServiceImpl::~ServiceImpl( void )
        {
            try
            {
                stop( );
            }
            catch ( ... )
            {
                log( Logger::Level::WARNING, "Service failed graceful teardown." );
            }
        }
        
        void ServiceImpl::stop( void )
        {
            m_is_running = false;

            if ( m_io_service not_eq nullptr )
            {
                m_io_service->stop( );
            }

            if ( m_session_manager not_eq nullptr )
            {
                m_session_manager->stop( );
            }

            if ( m_logger not_eq nullptr )
            {
                m_logger->stop( );
            }
        }

        void ServiceImpl::start( const shared_ptr< const Settings >& settings )
        {
            m_settings = settings;

            if ( m_session_manager == nullptr )
            {
                m_session_manager = make_shared< SessionManagerImpl >( );
            }

            m_session_manager->start( settings );

            if ( m_logger not_eq nullptr )
            {
                m_logger->start( settings );
            }

            m_io_service = make_shared< io_service >( );

            m_acceptor = make_shared< tcp::acceptor >( *m_io_service, tcp::endpoint( tcp::v6( ), settings->get_port( ) ) );
            m_acceptor->set_option( socket_base::reuse_address( true ) );
            m_acceptor->listen( settings->get_connection_limit( ) );
            
            listen( );

            auto endpoint = m_acceptor->local_endpoint( );
            auto address = endpoint.address( );
            auto location = address.is_v4( ) ? address.to_string( ) : "[" + address.to_string( ) + "]:";
            location += ::to_string( endpoint.port( ) );
            log( Logger::Level::INFO, String::format( "Service accepting connections at '%s'.",  location.data( ) ) );

            for ( const auto& route : m_resource_paths )
            {
                auto path = String::format( "/%s/%s", settings->get_root( ).data( ), route.second.data( ) );
                path = String::replace( "//", "/", path );

                log( Logger::Level::INFO, String::format( "Resource published on route '%s'.", path.data( ) ) );
            }

            m_is_running = true;
            m_io_service->run( );

            log( Logger::Level::INFO, String::format( "Service halted at '%s'.", location.data( ) ) );
        }

        void ServiceImpl::restart( const shared_ptr< const Settings >& settings )
        {
            try
            {
                stop( );
            }
            catch ( ... )
            {
                log( Logger::Level::WARNING, "Service failed graceful teardown." );
            }

            start( settings );
        }
        
        void ServiceImpl::publish( const shared_ptr< const Resource >& resource )
        {
            if ( m_is_running )
            {
                throw runtime_error( "Runtime modifications of the service are prohibited." );
            }

            if ( resource == nullptr )
            {
                return;
            }

            auto paths = resource->m_pimpl->get_paths( );

            if ( not has_unique_paths( paths ) )
            {
                throw invalid_argument( "Resource would pollute namespace. Please ensure all published resources have unique paths." );
            }

            for ( auto& path : paths )
            {
                const string sanitised_path = sanitise_path( path );

                m_resource_paths[ sanitised_path ] = path;
                m_resource_routes[ sanitised_path ] = resource;
            }

            const auto& methods = resource->m_pimpl->get_methods( );
            m_supported_methods.insert( methods.begin( ), methods.end( ) );
        }
        
        void ServiceImpl::suppress( const shared_ptr< const Resource >& resource )
        {
            if ( m_is_running )
            {
                throw runtime_error( "Runtime modifications of the service are prohibited." );
            }

            if ( resource == nullptr )
            {
                return;
            }

            for ( const auto& path : resource->m_pimpl->get_paths( ) )
            {
                if ( m_resource_routes.erase( path ) )
                {
                    log( Logger::Level::INFO, String::format( "Suppressed resource route '%s'.", path.data( ) ) );
                }
                else
                {
                    log( Logger::Level::WARNING, String::format( "Failed to suppress resource route '%s'; Not Found!", path.data( ) ) );
                }
            }
        }

        void ServiceImpl::set_logger(  const shared_ptr< Logger >& value )
        {
            if ( m_is_running )
            {
                throw runtime_error( "Runtime modifications of the service are prohibited." );
            }

            m_logger = value;
        }

        void ServiceImpl::set_not_found_handler( const function< void ( const shared_ptr< Session >& ) >& value )
        {
            if ( m_is_running )
            {
                throw runtime_error( "Runtime modifications of the service are prohibited." );
            }

            m_not_found_handler = value;
        }

        void ServiceImpl::set_method_not_allowed_handler( const function< void ( const shared_ptr< Session >& ) >& value )
        {
            if ( m_is_running )
            {
                throw runtime_error( "Runtime modifications of the service are prohibited." );
            }

            m_method_not_allowed_handler = value;
        }

        void ServiceImpl::set_method_not_implemented_handler( const function< void ( const shared_ptr< Session >& ) >& value )
        {
            if ( m_is_running )
            {
                throw runtime_error( "Runtime modifications of the service are prohibited." );
            }

            m_method_not_implemented_handler = value;
        }

        void ServiceImpl::set_failed_filter_validation_handler( const function< void ( const shared_ptr< Session >& ) >& value )
        {
            if ( m_is_running )
            {
                throw runtime_error( "Runtime modifications of the service are prohibited." );
            }

            m_failed_filter_validation_handler = value;
        }

        void ServiceImpl::set_error_handler( const function< void ( const int, const exception&, const shared_ptr< Session >& ) >& value )
        {
            if ( m_is_running )
            {
                throw runtime_error( "Runtime modifications of the service are prohibited." );
            }

            m_error_handler = value;
        }

        void ServiceImpl::set_authentication_handler( const function< void ( const shared_ptr< Session >&, const function< void ( const shared_ptr< Session >& ) >& ) >& value )
        {
            if ( m_is_running )
            {
                throw runtime_error( "Runtime modifications of the service are prohibited." );
            }

            m_authentication_handler = value;
        }
        
        void ServiceImpl::listen( void ) const
        {
            auto socket = make_shared< tcp::socket >( m_acceptor->get_io_service( ) );
            
            m_acceptor->async_accept( *socket, bind( &ServiceImpl::create_session, this, socket, _1 ) );
        }

        string ServiceImpl::sanitise_path( const string& path ) const
        {
            if ( path == "/" )
            {
                return path;
            }

            smatch matches;
            string sanitised_path = String::empty;
            static const regex pattern( "^\\{[a-zA-Z0-9]+: ?(.*)\\}$" );

            for ( auto folder : String::split( path, '/' ) )
            {
                if ( folder.front( ) == '{' and folder.back( ) == '}' )
                {
                    if ( not regex_match( folder, matches, pattern ) or matches.size( ) not_eq 2 )
                    {
                        throw runtime_error( String::format( "Resource path parameter declaration is malformed '%s'.", folder.data( ) ) );
                    }

                    sanitised_path += '/' + matches[ 1 ].str( );
                }
                else
                {
                    sanitised_path += '/' + folder;
                }
            }

            if ( path.back( ) == '/' )
            {
                sanitised_path += '/';
            }

            return sanitised_path;
        }

        void ServiceImpl::router( const shared_ptr< Session >& session ) const
        {
            if ( session->is_closed( ) )
            {
                return;
            }

            const auto root = m_settings->get_root( );

            const auto resource_route = find_if( m_resource_routes.begin( ), m_resource_routes.end( ), bind( &ServiceImpl::resource_router, this, session, _1 ) );

            if ( resource_route == m_resource_routes.end( ) )
            {
                return not_found( session );
            }

            const auto path = resource_route->first;
            const auto resource = resource_route->second;
            session->m_pimpl->set_resource( resource );

            resource->m_pimpl->authenticate( session, bind( &ServiceImpl::route, this, _1, path ) );
        }

        void ServiceImpl::not_found( const shared_ptr< Session >& session ) const
        {
            log( Logger::Level::INFO, String::format( "'%s' resource not found '%s'.",
                                                      session->get_origin( ).data( ),
                                                      session->get_request( )->get_path( ).data( ) ) );
            if ( m_not_found_handler not_eq nullptr )
            {
                m_not_found_handler( session );
            }
            else
            {
                if ( session->is_open( ) )
                {
                    session->close( NOT_FOUND );
                }
            }
        }

        bool ServiceImpl::has_unique_paths( const set< string >& paths ) const
        {
            if ( paths.empty( ) )
            {
                return false;
            }

            for ( const auto& path : paths )
            {
                if ( m_resource_routes.count( path ) )
                {
                    return false;
                }
            }

            return true;
        }

        void ServiceImpl::log( const Logger::Level level, const string& message ) const
        {
             if ( m_logger not_eq nullptr )
             {
                 m_logger->log( level, "%s", message.data( ) );
             }
        }

        void ServiceImpl::method_not_allowed( const shared_ptr< Session >& session ) const
        {
            log( Logger::Level::INFO, String::format( "'%s' '%s' method not allowed '%s'.",
                                                      session->get_origin( ).data( ),
                                                      session->get_request( )->get_method( ).data( ),
                                                      session->get_request( )->get_path( ).data( ) ) );

            if ( m_method_not_allowed_handler not_eq nullptr )
            {
                m_method_not_allowed_handler( session );
            }
            else
            {
                if ( session->is_open( ) )
                {
                    session->close( METHOD_NOT_ALLOWED );
                }
            }
        }

        void ServiceImpl::method_not_implemented( const shared_ptr< Session >& session ) const
        {
            log( Logger::Level::INFO, String::format( "'%s' '%s' method not implemented '%s'.",
                                                      session->get_origin( ).data( ),
                                                      session->get_request( )->get_method( ).data( ),
                                                      session->get_request( )->get_path( ).data( ) ) );

            if ( m_method_not_implemented_handler not_eq nullptr )
            {
                m_method_not_implemented_handler( session );
            }
            else
            {
                if ( session->is_open( ) )
                {
                    session->close( NOT_IMPLEMENTED );
                }
            }
        }

        void ServiceImpl::failed_filter_validation( const shared_ptr< Session >& session ) const
        {
            log( Logger::Level::INFO, String::format( "'%s' failed filter validation '%s'.",
                                                      session->get_origin( ).data( ),
                                                      session->get_request( )->get_path( ).data( ) ) );

            if ( m_failed_filter_validation_handler not_eq nullptr )
            {
                m_failed_filter_validation_handler( session );
            }
            else
            {
                if ( session->is_open( ) )
                {
                    session->close( BAD_REQUEST, { { "Connection", "close" } } );
                }
            }
        }

        void ServiceImpl::route( const shared_ptr< Session >& session, const string sanitised_path ) const
        {
            if ( session->is_closed( ) )
            {
                return;
            }

            const auto request = session->get_request( );
            const auto method_handler = find_method_handler( session );

            extract_path_parameters( sanitised_path, request );

            if ( method_handler == nullptr )
            {
                if ( m_supported_methods.count( request->get_method( ) ) == 0 )
                {
                    return method_not_implemented( session );
                }
                else
                {
                    return method_not_allowed( session );
                }
            }

            method_handler( session );
        }

        void ServiceImpl::create_session( const shared_ptr< tcp::socket >& socket, const error_code& error ) const
        {
            if ( not error )
            {
                const function< void ( const shared_ptr< Session >& ) > route = bind( &ServiceImpl::router, this, _1 );
                const function< void ( const shared_ptr< Session >& ) > load = bind( &SessionManager::load, m_session_manager, _1, route );
                const function< void ( const shared_ptr< Session >& ) > authenticate = bind( &ServiceImpl::authenticate, this, _1, load );
                const function< void ( const int, const exception&, const shared_ptr< Session >& ) > error_handler = m_error_handler;

                const auto settings = m_settings;

                m_session_manager->create( [ socket, authenticate, settings, error_handler ]( const shared_ptr< Session >& session )
                {
                    session->m_pimpl->set_socket( socket );
                    session->m_pimpl->fetch( session, authenticate );
                    session->m_pimpl->set_settings( settings );
                    session->m_pimpl->set_error_handler( error_handler );
                    //set socket timeout etc...
                } );
            }
            else
            {
                if ( socket not_eq nullptr and socket->is_open( ) )
                {
                    socket->close( );
                }

                log( Logger::Level::WARNING, String::format( "Failed to create session, '%s'.", error.message( ).data( ) ) );
            }

            listen( );
        }

        void ServiceImpl::extract_path_parameters( const string& sanitised_path, const shared_ptr< const Request >& request ) const
        {
            smatch matches;
            static const regex pattern( "^\\{([a-zA-Z0-9]+): ?.*\\}$" );

            const auto folders = String::split( request->get_path( ), '/' );
            const auto declarations = String::split( m_resource_paths.at( sanitised_path ), '/' );

            for ( size_t index = 0; index < folders.size( ) and index < declarations.size( ); index++ )
            {
                const auto declaration = declarations[ index ];

                if ( declaration.front( ) == '{' and declaration.back( ) == '}' )
                {
                    regex_match( declaration, matches, pattern );
                    request->m_pimpl->set_path_parameter( matches[ 1 ].str( ), folders[ index ] );
                }
            }
        }

        function< void ( const shared_ptr< Session >& ) > ServiceImpl::find_method_handler( const shared_ptr< Session >& session ) const
        {
            const auto request = session->get_request( );
            const auto resource = session->get_resource( );
            const auto method_handlers = resource->m_pimpl->get_method_handlers( request->get_method( ) );

            bool failed_filter_validation = false;
            function< void ( const shared_ptr< Session >& ) > method_handler = nullptr;

            for ( auto handler = method_handlers.begin( ); handler not_eq method_handlers.end( ) and method_handler == nullptr; handler++ )
            {
                method_handler = handler->second.second;

                for ( const auto& filter : handler->second.first )
                {
                    for ( const auto& header : request->get_headers( filter.first ) )
                    {
                         if ( not regex_match( header.second, regex( filter.second ) ) )
                         {
                            method_handler = nullptr;
                            failed_filter_validation = true;
                         }
                    }
                }
            }

            if ( failed_filter_validation and method_handler == nullptr )
            {
                const auto handler = resource->m_pimpl->get_failed_filter_validation_handler( );
                method_handler = ( handler == nullptr ) ? bind( &ServiceImpl::failed_filter_validation, this, _1 ) : handler;
            }

            return method_handler;
        }

        void ServiceImpl::authenticate( const shared_ptr< Session >& session, const function< void ( const shared_ptr< Session >& ) >& callback ) const
        {
            if ( m_authentication_handler not_eq nullptr )
            {
                m_authentication_handler( session, callback );
            }
            else
            {
                callback( session );
            }
        }

        bool ServiceImpl::resource_router( const shared_ptr< Session >& session, const pair< string, shared_ptr< const Resource > >& route ) const
        {
            log( Logger::Level::INFO, String::format( "Incoming '%s' request from '%s' for route '%s'.",
                                                      session->get_request( )->get_method( ).data( ),
                                                      session->get_origin( ).data( ),
                                                      session->get_request( )->get_path( ).data( ) ) );

            const auto root = m_settings->get_root( );
            auto route_folders = String::split( route.first, '/' );

            if ( not root.empty( ) and root not_eq "/" )
            {
                route_folders.insert( route_folders.begin( ), root );
            }

            const auto request = session->get_request( );
            const auto path_folders = String::split( request->get_path( ), '/' );

            if ( path_folders.empty( ) and route_folders.empty( ) )
            {
                return true;
            }

            bool match = false;

            if ( path_folders.size( ) == route_folders.size( ) )
            {
                for ( size_t index = 0; index < path_folders.size( ); index++ )
                {
                    match = regex_match( path_folders[ index ], regex( route_folders[ index ] ) );

                    if ( not match )
                    {
                        break;
                    }
                }
            }

            return match;
        }
    }
}
