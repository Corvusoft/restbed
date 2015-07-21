/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <regex>
#include <cstdio>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <functional>

//Project Includes
#include "corvusoft/restbed/rule.hpp"
#include "corvusoft/restbed/logger.hpp"
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/resource.hpp"
#include "corvusoft/restbed/settings.hpp"
#include "corvusoft/restbed/status_code.hpp"
#include "corvusoft/restbed/ssl_settings.hpp"
#include "corvusoft/restbed/session_manager.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"
#include "corvusoft/restbed/detail/request_impl.hpp"
#include "corvusoft/restbed/detail/service_impl.hpp"
#include "corvusoft/restbed/detail/session_impl.hpp"
#include "corvusoft/restbed/detail/resource_impl.hpp"
#include "corvusoft/restbed/detail/rule_engine_impl.hpp"
#include "corvusoft/restbed/detail/session_manager_impl.hpp"

//External Includes

//System Namespaces
using std::set;
using std::pair;
using std::bind;
using std::regex;
using std::string;
using std::smatch;
using std::vector;
using std::find_if;
using std::function;
using std::to_string;
using std::exception;
using std::shared_ptr;
using std::make_shared;
using std::stable_sort;
using std::runtime_error;
using std::invalid_argument;
using std::placeholders::_1;
using std::regex_constants::icase;

//Project Namespaces

//External Namespaces
using asio::ip::tcp;
using asio::io_service;
using asio::error_code;
using asio::socket_base;
using asio::system_error;

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
            m_rules( ),
#ifdef BUILD_SSL
            m_ssl_settings( nullptr ),
            m_ssl_context( nullptr ),
            m_ssl_acceptor( nullptr ),
#endif
            m_acceptor( nullptr ),
            m_resource_paths( ),
            m_resource_routes( ),
            m_ready_handler( nullptr ),
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

            log( Logger::Level::INFO, String::format( "Service halted." ) );
        }

        void ServiceImpl::start( const shared_ptr< const Settings >& settings )
        {
            m_settings = settings;

            if ( m_settings == nullptr )
            {
                m_settings = make_shared< Settings >( );
            }

            if ( m_session_manager == nullptr )
            {
                m_session_manager = make_shared< SessionManagerImpl >( );
            }
            
            m_session_manager->start( m_settings );
            
            if ( m_logger not_eq nullptr )
            {
                m_logger->start( m_settings );
            }

            stable_sort( m_rules.begin( ), m_rules.end( ), [ ]( const shared_ptr< const Rule >& lhs, const shared_ptr< const Rule >& rhs )
            {
                return lhs->get_priority( ) < rhs->get_priority( );
            } );

            m_io_service = make_shared< io_service >( );

            http_start( );

#ifdef BUILD_SSL
            m_ssl_settings = m_settings->get_ssl_settings( );
            https_start( );
#endif
            for ( const auto& route : m_resource_paths )
            {
                auto path = String::format( "/%s/%s", m_settings->get_root( ).data( ), route.second.data( ) );
                path = String::replace( "//", "/", path );
                
                log( Logger::Level::INFO, String::format( "Resource published on route '%s'.", path.data( ) ) );
            }
            
            if ( m_ready_handler not_eq nullptr )
            {
                m_io_service->post( m_ready_handler );
            }

            m_is_running = true;
            m_io_service->run( );
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

        void ServiceImpl::add_rule( const shared_ptr< Rule >& rule )
        {
            if ( m_is_running )
            {
                throw runtime_error( "Runtime modifications of the service are prohibited." );
            }

            m_rules.push_back( rule );
        }

        void ServiceImpl::add_rule( const shared_ptr< Rule >& rule, const int priority )
        {
            if ( m_is_running )
            {
                throw runtime_error( "Runtime modifications of the service are prohibited." );
            }

            rule->set_priority( priority );
            m_rules.push_back( rule );
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
        
        void ServiceImpl::set_ready_handler( const function< void ( void ) >& value )
        {
            m_ready_handler = value;
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

        void ServiceImpl::http_start( void )
        {
#ifdef BUILD_SSL
            if ( m_ssl_settings == nullptr or m_ssl_settings->has_disabled_http( ) == false )
            {
#endif
                m_acceptor = make_shared< tcp::acceptor >( *m_io_service, tcp::endpoint( tcp::v6( ), m_settings->get_port( ) ) );
                m_acceptor->set_option( socket_base::reuse_address( true ) );
                m_acceptor->listen( m_settings->get_connection_limit( ) );
            
                http_listen( );

                auto endpoint = m_acceptor->local_endpoint( );
                auto address = endpoint.address( );
                auto location = address.is_v4( ) ? address.to_string( ) : "[" + address.to_string( ) + "]:";
                location += ::to_string( endpoint.port( ) );
                log( Logger::Level::INFO, String::format( "Service accepting HTTP connections at '%s'.",  location.data( ) ) );
#ifdef BUILD_SSL
            }
#endif
        }

        void ServiceImpl::http_listen( void ) const
        {
            auto socket = make_shared< tcp::socket >( m_acceptor->get_io_service( ) );
            m_acceptor->async_accept( *socket, bind( &ServiceImpl::create_session, this, socket, _1 ) );
        }

#ifdef BUILD_SSL
        void ServiceImpl::https_start( void )
        {
            if ( m_ssl_settings not_eq nullptr )
            {
                m_ssl_context = make_shared< asio::ssl::context >( asio::ssl::context::sslv23 );
                m_ssl_context->set_default_verify_paths( );

                auto passphrase = m_ssl_settings->get_passphrase( );
                m_ssl_context->set_password_callback( [ passphrase ]( size_t, asio::ssl::context::password_purpose )
                {
                    return passphrase;
                } );

                auto filename = m_ssl_settings->get_temporary_diffie_hellman( );
                if ( not filename.empty( ) )
                {
                    m_ssl_context->use_tmp_dh_file( filename );
                }

                filename = m_ssl_settings->get_certificate_authority_pool( );
                if ( not filename.empty( ) )
                {
                    m_ssl_context->add_verify_path( filename );
                }

                filename = m_ssl_settings->get_certificate_chain( );
                if ( not filename.empty( ) )
                {
                    m_ssl_context->use_certificate_chain_file( filename );
                }

                filename = m_ssl_settings->get_certificate( );
                if ( not filename.empty( ) )
                {
                    m_ssl_context->use_certificate_file( filename, asio::ssl::context::pem );
                }

                filename = m_ssl_settings->get_private_key( );
                if ( not filename.empty( ) )
                {
                    m_ssl_context->use_private_key_file( filename, asio::ssl::context::pem );
                }

                filename = m_ssl_settings->get_private_rsa_key( );
                if ( not filename.empty( ) )
                {
                    m_ssl_context->use_rsa_private_key_file( filename, asio::ssl::context::pem );
                }

                asio::ssl::context::options options = 0;
                options = ( m_ssl_settings->has_enabled_tlsv1( ) ) ? options : options | asio::ssl::context::no_tlsv1;
                options = ( m_ssl_settings->has_enabled_sslv2( ) ) ? options : options | asio::ssl::context::no_sslv2;
                options = ( m_ssl_settings->has_enabled_sslv3( ) ) ? options : options | asio::ssl::context::no_sslv3;
                options = ( m_ssl_settings->has_enabled_tlsv11( ) ) ? options : options | asio::ssl::context::no_tlsv1_1;
                options = ( m_ssl_settings->has_enabled_tlsv12( ) ) ? options : options | asio::ssl::context::no_tlsv1_2;
                options = ( m_ssl_settings->has_enabled_compression( ) ) ? options : options | asio::ssl::context::no_compression;
                options = ( m_ssl_settings->has_enabled_default_workarounds( ) ) ? options | asio::ssl::context::default_workarounds : options;
                options = ( m_ssl_settings->has_enabled_single_diffie_hellman_use( ) ) ? options | asio::ssl::context::single_dh_use : options;
                m_ssl_context->set_options( options );

                m_ssl_acceptor = make_shared< tcp::acceptor >( *m_io_service, tcp::endpoint( tcp::v6( ), m_ssl_settings->get_port( ) ) );
                m_ssl_acceptor->set_option( socket_base::reuse_address( true ) );
                m_ssl_acceptor->listen( m_settings->get_connection_limit( ) ); 

                https_listen( );

                auto endpoint = m_ssl_acceptor->local_endpoint( );
                auto address = endpoint.address( );
                auto location = address.is_v4( ) ? address.to_string( ) : "[" + address.to_string( ) + "]:";
                location += ::to_string( endpoint.port( ) );
                log( Logger::Level::INFO, String::format( "Service accepting HTTPS connections at '%s'.",  location.data( ) ) );
            }
        }

        void ServiceImpl::https_listen( void ) const
        {
            auto socket = make_shared< asio::ssl::stream< tcp::socket > >( m_ssl_acceptor->get_io_service( ), *m_ssl_context );
            m_ssl_acceptor->async_accept( socket->lowest_layer( ), bind( &ServiceImpl::create_ssl_session, this, socket, _1 ) );
        }

        void ServiceImpl::create_ssl_session( const shared_ptr< asio::ssl::stream< tcp::socket > >& socket, const error_code& error ) const
        {
            if ( not error )
            {
                socket->async_handshake( asio::ssl::stream_base::server, [ this, socket ]( const asio::error_code& error )
                {
                    if ( error )
                    {
                        log( Logger::Level::ERROR, String::format( "Failed SSL handshake, '%s'.", error.message( ).data( ) ) );
                        return;
                    }

                    auto connection = make_shared< SocketImpl >( socket, m_logger );
                    connection->set_timeout( m_settings->get_connection_timeout( ) );
                    
                    m_session_manager->create( [ this, connection ]( const shared_ptr< Session >& session )
                    {
                        session->m_pimpl->set_logger( m_logger );
                        session->m_pimpl->set_socket( connection );
                        session->m_pimpl->set_settings( m_settings );
                        session->m_pimpl->set_error_handler( m_error_handler );
                        session->m_pimpl->set_session_manager( m_session_manager );
                        session->m_pimpl->fetch( session, bind( &ServiceImpl::authenticate, this, _1 ) );
                    } );
                } );
            }
            else
            {
                if ( socket not_eq nullptr and socket->lowest_layer( ).is_open( ) )
                {
                    socket->lowest_layer( ).close( );
                }
                
                log( Logger::Level::WARNING, String::format( "Failed to create session, '%s'.", error.message( ).data( ) ) );
            }
            
            https_listen( );
        }
#endif

        string ServiceImpl::sanitise_path( const string& path ) const
        {
            if ( path == "/" )
            {
                return path;
            }
            
            smatch matches;
            string sanitised_path = "";
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
        
        void ServiceImpl::not_found( const shared_ptr< Session >& session ) const
        {
            log( Logger::Level::INFO, String::format( "'%s' resource route not found '%s'.",
                    session->get_origin( ).data( ),
                    session->get_request( )->get_path( ).data( ) ) );
                    
            if ( m_not_found_handler not_eq nullptr )
            {
                m_not_found_handler( session );
            }
            else
            {
                session->close( NOT_FOUND );
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
                session->close( METHOD_NOT_ALLOWED );
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
                session->close( NOT_IMPLEMENTED );
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
                session->close( BAD_REQUEST, { { "Connection", "close" } } );
            }
        }
        
        void ServiceImpl::router( const shared_ptr< Session >& session ) const
        {
            if ( session->is_closed( ) )
            {
                return;
            }
            
            const auto resource_route = find_if( m_resource_routes.begin( ), m_resource_routes.end( ), bind( &ServiceImpl::resource_router, this, session, _1 ) );
            
            if ( resource_route == m_resource_routes.end( ) )
            {
                return not_found( session );
            }

            const auto path = resource_route->first;
            const auto resource = resource_route->second;
            session->m_pimpl->set_resource( resource );

            resource->m_pimpl->authenticate( session, [ this, path, resource ]( const shared_ptr< Session >& session )
            {    
                rule_engine( session, resource->m_pimpl->get_rules( ), [ this, path, resource ]( const shared_ptr< Session >& session )
                {
                    if ( session->is_closed( ) )
                    {
                        return;
                    }

                    const auto request = session->get_request( );
                    auto method_handler = find_method_handler( session );
                    
                    extract_path_parameters( path, request );
                    
                    if ( method_handler == nullptr )
                    {
                        if ( m_supported_methods.count( request->get_method( ) ) == 0 )
                        {
                            method_handler = bind( &ServiceImpl::method_not_implemented, this, _1 );
                        }
                        else
                        {
                            method_handler = bind( &ServiceImpl::method_not_allowed, this, _1 );
                        }
                    }

                    method_handler( session );
                } );
            } );
        }
        
        void ServiceImpl::create_session( const shared_ptr< tcp::socket >& socket, const error_code& error ) const
        {
            if ( not error )
            {
                auto connection = make_shared< SocketImpl >( socket, m_logger );
                connection->set_timeout( m_settings->get_connection_timeout( ) );
                
                m_session_manager->create( [ this, connection ]( const shared_ptr< Session >& session )
                {
                    session->m_pimpl->set_logger( m_logger );
                    session->m_pimpl->set_socket( connection );
                    session->m_pimpl->set_settings( m_settings );
                    session->m_pimpl->set_error_handler( m_error_handler );
                    session->m_pimpl->set_session_manager( m_session_manager );
                    session->m_pimpl->fetch( session, bind( &ServiceImpl::authenticate, this, _1 ) );
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
            
            http_listen( );
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
        
        void ServiceImpl::authenticate( const shared_ptr< Session >& session ) const
        {
            if ( m_authentication_handler not_eq nullptr )
            {
                m_authentication_handler( session, [ this ]( const shared_ptr< Session >& session )
                {
                    m_session_manager->load( session, [ this ]( const shared_ptr< Session >& session )
                    {
                        rule_engine( session, m_rules, bind( &ServiceImpl::router, this, _1 ) );
                    } );
                } );
            }
            else
            {
                m_session_manager->load( session, [ this ]( const shared_ptr< Session >& session )
                {
                    rule_engine( session, m_rules, bind( &ServiceImpl::router, this, _1 ) );
                } );
            }
        }
        
        bool ServiceImpl::resource_router( const shared_ptr< Session >& session, const pair< string, shared_ptr< const Resource > >& route ) const
        {
            log( Logger::Level::INFO, String::format( "Incoming '%s' request from '%s' for route '%s'.",
                    session->get_request( )->get_method( ).data( ),
                    session->get_origin( ).data( ),
                    session->get_request( )->get_path( ).data( ) ) );
            
            const auto request = session->get_request( );
            const auto path_folders = String::split( request->get_path( ), '/' );
            const auto route_folders = String::split( m_settings->get_root( ) + "/" + route.first, '/' );
            
            if ( path_folders.empty( ) and route_folders.empty( ) )
            {
                return true;
            }
            
            bool match = false;

            if ( path_folders.size( ) == route_folders.size( ) )
            {
                for ( size_t index = 0; index < path_folders.size( ); index++ )
                {
                    if ( m_settings->get_case_insensitive_uris( ) )
                    {
                        match = regex_match( path_folders[ index ], regex( route_folders[ index ], icase ) );
                    }
                    else
                    {
                        match = regex_match( path_folders[ index ], regex( route_folders[ index ] ) );
                    }
                    
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
