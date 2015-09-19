/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <regex>
#include <cstdio>
#include <utility>
#include <ciso646>
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

//External Includes

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
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;
using std::placeholders::_1;
using std::regex_constants::icase;

//Project Namespaces

//External Namespaces
using asio::ip::tcp;
using asio::io_service;
using asio::error_code;
using asio::ip::address;
using asio::socket_base;
using asio::system_error;

namespace restbed
{
    namespace detail
    {
        ServiceImpl::ServiceImpl( void ) : is_running( false ),
            logger( nullptr ),
            supported_methods( ),
            settings( nullptr ),
            io_service( new ::io_service ),
            session_manager( nullptr ),
            rules( ),
            workers( ),
#ifdef BUILD_SSL
            ssl_settings( nullptr ),
            ssl_context( nullptr ),
            ssl_acceptor( nullptr ),
#endif
            acceptor( nullptr ),
            resource_paths( ),
            resource_routes( ),
            ready_handler( nullptr ),
            not_found_handler( nullptr ),
            method_not_allowed_handler( nullptr ),
            method_not_implemented_handler( nullptr ),
            failed_filter_validation_handler( nullptr ),
            error_handler( nullptr ),
            authentication_handler( nullptr )
        {
            return;
        }
        
        ServiceImpl::~ServiceImpl( void )
        {
            return;
        }
        
        void ServiceImpl::http_start( void )
        {
#ifdef BUILD_SSL
        
            if ( ssl_settings == nullptr or ssl_settings->has_disabled_http( ) == false )
            {
#endif
            
                if ( not settings->get_bind_address( ).empty( ) )
                {
                    const auto address = address::from_string( settings->get_bind_address( ) );
                    acceptor = make_shared< tcp::acceptor >( *io_service, tcp::endpoint( address, settings->get_port( ) ) );
                }
                else
                {
                    acceptor = make_shared< tcp::acceptor >( *io_service, tcp::endpoint( tcp::v6( ), settings->get_port( ) ) );
                }
                
                acceptor->set_option( socket_base::reuse_address( true ) );
                acceptor->listen( settings->get_connection_limit( ) );
                
                http_listen( );
                
                auto endpoint = acceptor->local_endpoint( );
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
            auto socket = make_shared< tcp::socket >( acceptor->get_io_service( ) );
            acceptor->async_accept( *socket, bind( &ServiceImpl::create_session, this, socket, _1 ) );
        }
        
#ifdef BUILD_SSL
        void ServiceImpl::https_start( void )
        {
            if ( ssl_settings not_eq nullptr )
            {
                ssl_context = make_shared< asio::ssl::context >( asio::ssl::context::sslv23 );
                ssl_context->set_default_verify_paths( );
                
                auto passphrase = ssl_settings->get_passphrase( );
                ssl_context->set_password_callback( [ passphrase ]( size_t, asio::ssl::context::password_purpose )
                {
                    return passphrase;
                } );
                
                auto filename = ssl_settings->get_temporary_diffie_hellman( );
                
                if ( not filename.empty( ) )
                {
                    ssl_context->use_tmp_dh_file( filename );
                }
                
                filename = ssl_settings->get_certificate_authority_pool( );
                
                if ( not filename.empty( ) )
                {
                    ssl_context->add_verify_path( filename );
                }
                
                filename = ssl_settings->get_certificate_chain( );
                
                if ( not filename.empty( ) )
                {
                    ssl_context->use_certificate_chain_file( filename );
                }
                
                filename = ssl_settings->get_certificate( );
                
                if ( not filename.empty( ) )
                {
                    ssl_context->use_certificate_file( filename, asio::ssl::context::pem );
                }
                
                filename = ssl_settings->get_private_key( );
                
                if ( not filename.empty( ) )
                {
                    ssl_context->use_private_key_file( filename, asio::ssl::context::pem );
                }
                
                filename = ssl_settings->get_private_rsa_key( );
                
                if ( not filename.empty( ) )
                {
                    ssl_context->use_rsa_private_key_file( filename, asio::ssl::context::pem );
                }
                
                asio::ssl::context::options options = 0;
                options = ( ssl_settings->has_enabled_tlsv1( ) ) ? options : options | asio::ssl::context::no_tlsv1;
                options = ( ssl_settings->has_enabled_sslv2( ) ) ? options : options | asio::ssl::context::no_sslv2;
                options = ( ssl_settings->has_enabled_sslv3( ) ) ? options : options | asio::ssl::context::no_sslv3;
                options = ( ssl_settings->has_enabled_tlsv11( ) ) ? options : options | asio::ssl::context::no_tlsv1_1;
                options = ( ssl_settings->has_enabled_tlsv12( ) ) ? options : options | asio::ssl::context::no_tlsv1_2;
                options = ( ssl_settings->has_enabled_compression( ) ) ? options : options | asio::ssl::context::no_compression;
                options = ( ssl_settings->has_enabled_default_workarounds( ) ) ? options | asio::ssl::context::default_workarounds : options;
                options = ( ssl_settings->has_enabled_single_diffie_hellman_use( ) ) ? options | asio::ssl::context::single_dh_use : options;
                ssl_context->set_options( options );
                
                if ( not ssl_settings->get_bind_address( ).empty( ) )
                {
                    const auto address = address::from_string( ssl_settings->get_bind_address( ) );
                    ssl_acceptor = make_shared< tcp::acceptor >( *io_service, tcp::endpoint( address, ssl_settings->get_port( ) ) );
                }
                else
                {
                    ssl_acceptor = make_shared< tcp::acceptor >( *io_service, tcp::endpoint( tcp::v6( ), ssl_settings->get_port( ) ) );
                }
                
                ssl_acceptor->set_option( socket_base::reuse_address( true ) );
                ssl_acceptor->listen( settings->get_connection_limit( ) );
                
                https_listen( );
                
                auto endpoint = ssl_acceptor->local_endpoint( );
                auto address = endpoint.address( );
                auto location = address.is_v4( ) ? address.to_string( ) : "[" + address.to_string( ) + "]:";
                location += ::to_string( endpoint.port( ) );
                log( Logger::Level::INFO, String::format( "Service accepting HTTPS connections at '%s'.",  location.data( ) ) );
            }
        }
        
        void ServiceImpl::https_listen( void ) const
        {
            auto socket = make_shared< asio::ssl::stream< tcp::socket > >( ssl_acceptor->get_io_service( ), *ssl_context );
            ssl_acceptor->async_accept( socket->lowest_layer( ), bind( &ServiceImpl::create_ssl_session, this, socket, _1 ) );
        }
        
        void ServiceImpl::create_ssl_session( const shared_ptr< asio::ssl::stream< tcp::socket > >& socket, const error_code& error ) const
        {
            if ( not error )
            {
                socket->async_handshake( asio::ssl::stream_base::server, [ this, socket ]( const asio::error_code & error )
                {
                    if ( error )
                    {
                        log( Logger::Level::SECURITY, String::format( "Failed SSL handshake, '%s'.", error.message( ).data( ) ) );
                        return;
                    }
                    
                    auto connection = make_shared< SocketImpl >( socket, logger );
                    connection->set_timeout( settings->get_connection_timeout( ) );
                    
                    session_manager->create( [ this, connection ]( const shared_ptr< Session > session )
                    {
                        session->m_pimpl->logger = logger;
                        session->m_pimpl->socket = connection;
                        session->m_pimpl->settings = settings;
                        session->m_pimpl->manager = session_manager;
                        session->m_pimpl->error_handler = error_handler;
                        session->m_pimpl->router = bind( &ServiceImpl::authenticate, this, _1 );
                        session->m_pimpl->fetch( session, session->m_pimpl->router );
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
        
        void ServiceImpl::not_found( const shared_ptr< Session > session ) const
        {
            log( Logger::Level::INFO, String::format( "'%s' resource route not found '%s'.",
                    session->get_origin( ).data( ),
                    session->get_request( )->get_path( ).data( ) ) );
                    
            if ( not_found_handler not_eq nullptr )
            {
                not_found_handler( session );
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
                if ( resource_routes.count( path ) )
                {
                    return false;
                }
            }
            
            return true;
        }
        
        void ServiceImpl::log( const Logger::Level level, const string& message ) const
        {
            if ( logger not_eq nullptr )
            {
                logger->log( level, "%s", message.data( ) );
            }
        }
        
        void ServiceImpl::method_not_allowed( const shared_ptr< Session > session ) const
        {
            log( Logger::Level::INFO, String::format( "'%s' '%s' method not allowed '%s'.",
                    session->get_origin( ).data( ),
                    session->get_request( )->get_method( ).data( ),
                    session->get_request( )->get_path( ).data( ) ) );
                    
            if ( method_not_allowed_handler not_eq nullptr )
            {
                method_not_allowed_handler( session );
            }
            else
            {
                session->close( METHOD_NOT_ALLOWED );
            }
        }
        
        void ServiceImpl::method_not_implemented( const shared_ptr< Session > session ) const
        {
            log( Logger::Level::INFO, String::format( "'%s' '%s' method not implemented '%s'.",
                    session->get_origin( ).data( ),
                    session->get_request( )->get_method( ).data( ),
                    session->get_request( )->get_path( ).data( ) ) );
                    
            if ( method_not_implemented_handler not_eq nullptr )
            {
                method_not_implemented_handler( session );
            }
            else
            {
                session->close( NOT_IMPLEMENTED );
            }
        }
        
        void ServiceImpl::failed_filter_validation( const shared_ptr< Session > session ) const
        {
            log( Logger::Level::INFO, String::format( "'%s' failed filter validation '%s'.",
                    session->get_origin( ).data( ),
                    session->get_request( )->get_path( ).data( ) ) );
                    
            if ( failed_filter_validation_handler not_eq nullptr )
            {
                failed_filter_validation_handler( session );
            }
            else
            {
                session->close( BAD_REQUEST, { { "Connection", "close" } } );
            }
        }
        
        void ServiceImpl::router( const shared_ptr< Session > session ) const
        {
            if ( session->is_closed( ) )
            {
                return;
            }
            
            const auto resource_route = find_if( resource_routes.begin( ), resource_routes.end( ), bind( &ServiceImpl::resource_router, this, session, _1 ) );
            
            if ( resource_route == resource_routes.end( ) )
            {
                return not_found( session );
            }
            
            const auto path = resource_route->first;
            session->m_pimpl->resource = resource_route->second;
            const auto request = session->get_request( );
            extract_path_parameters( path, request );
            
            rule_engine( session, rules, [ this ]( const shared_ptr< Session > session )
            {
                const auto callback = [ this ]( const shared_ptr< Session > session )
                {
                    rule_engine( session, session->m_pimpl->resource->m_pimpl->rules, [ this ]( const shared_ptr< Session > session )
                    {
                        if ( session->is_closed( ) )
                        {
                            return;
                        }
                        
                        const auto request = session->get_request( );
                        auto method_handler = find_method_handler( session );
                        
                        if ( method_handler == nullptr )
                        {
                            if ( supported_methods.count( request->get_method( ) ) == 0 )
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
                };
                
                if ( session->m_pimpl->resource->m_pimpl->authentication_handler not_eq nullptr )
                {
                    session->m_pimpl->resource->m_pimpl->authentication_handler( session, callback );
                }
                else
                {
                    callback( session );
                }
            } );
        }
        
        void ServiceImpl::create_session( const shared_ptr< tcp::socket >& socket, const error_code& error ) const
        {
            if ( not error )
            {
                auto connection = make_shared< SocketImpl >( socket, logger );
                connection->set_timeout( settings->get_connection_timeout( ) );
                
                session_manager->create( [ this, connection ]( const shared_ptr< Session > session )
                {
                    session->m_pimpl->logger = logger;
                    session->m_pimpl->socket = connection;
                    session->m_pimpl->settings = settings;
                    session->m_pimpl->manager = session_manager;
                    session->m_pimpl->error_handler = error_handler;
                    session->m_pimpl->router = bind( &ServiceImpl::authenticate, this, _1 );
                    session->m_pimpl->fetch( session, session->m_pimpl->router );
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
            const auto declarations = String::split( resource_paths.at( sanitised_path ), '/' );
            
            for ( size_t index = 0; index < folders.size( ) and index < declarations.size( ); index++ )
            {
                const auto declaration = declarations[ index ];
                
                if ( declaration.front( ) == '{' and declaration.back( ) == '}' )
                {
                    regex_match( declaration, matches, pattern );
                    request->m_pimpl->path_parameters.insert( make_pair( matches[ 1 ].str( ), folders[ index ] ) );
                }
            }
        }
        
        function< void ( const shared_ptr< Session > ) > ServiceImpl::find_method_handler( const shared_ptr< Session > session ) const
        {
            const auto request = session->get_request( );
            const auto resource = session->get_resource( );
            const auto method_handlers = resource->m_pimpl->method_handlers.equal_range( request->get_method( ) );
            
            bool failed_filter_validation = false;
            function< void ( const shared_ptr< Session > ) > method_handler = nullptr;
            
            for ( auto handler = method_handlers.first; handler not_eq method_handlers.second and method_handler == nullptr; handler++ )
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
                const auto handler = resource->m_pimpl->failed_filter_validation_handler;
                method_handler = ( handler == nullptr ) ? bind( &ServiceImpl::failed_filter_validation, this, _1 ) : handler;
            }
            
            return method_handler;
        }
        
        void ServiceImpl::authenticate( const shared_ptr< Session > session ) const
        {
            if ( authentication_handler not_eq nullptr )
            {
                authentication_handler( session, [ this ]( const shared_ptr< Session > session )
                {
                    session_manager->load( session, bind( &ServiceImpl::router, this, _1 ) );
                } );
            }
            else
            {
                session_manager->load( session, bind( &ServiceImpl::router, this, _1 ) );
            }
        }
        
        bool ServiceImpl::resource_router( const shared_ptr< Session > session, const pair< string, shared_ptr< const Resource > >& route ) const
        {
            log( Logger::Level::INFO, String::format( "Incoming '%s' request from '%s' for route '%s'.",
                    session->get_request( )->get_method( ).data( ),
                    session->get_origin( ).data( ),
                    session->get_request( )->get_path( ).data( ) ) );
                    
            const auto request = session->get_request( );
            const auto path_folders = String::split( request->get_path( ), '/' );
            const auto route_folders = String::split( settings->get_root( ) + "/" + route.first, '/' );
            
            if ( path_folders.empty( ) and route_folders.empty( ) )
            {
                return true;
            }
            
            bool match = false;
            
            if ( path_folders.size( ) == route_folders.size( ) )
            {
                for ( size_t index = 0; index < path_folders.size( ); index++ )
                {
                    if ( settings->get_case_insensitive_uris( ) )
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
