/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <regex>
#include <cstdio>
#include <sstream>
#include <utility>
#include <ciso646>
#include <cstdlib>
#include <clocale>
#include <stdexcept>
#include <algorithm>
#include <functional>

//Project Includes
#include "corvusoft/restbed/uri.hpp"
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
#include "corvusoft/restbed/detail/web_socket_manager_impl.hpp"

//External Includes

//System Namespaces
using std::set;
using std::map;
using std::free;
using std::pair;
using std::bind;
using std::regex;
using std::string;
using std::smatch;
using std::istream;
using std::find_if;
using std::function;
using std::setlocale;
using std::multimap;
using std::to_string;
using std::exception;
using std::shared_ptr;
using std::error_code;
using std::regex_error;
using std::make_shared;
using std::runtime_error;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::current_exception;
using std::rethrow_exception;
using std::chrono::steady_clock;
using std::regex_constants::icase;

//Project Namespaces

//External Namespaces
using asio::ip::tcp;
using asio::io_service;
using asio::signal_set;
using asio::ip::address;
using asio::socket_base;
using asio::system_error;

namespace restbed
{
    namespace detail
    {
        ServiceImpl::ServiceImpl( void ) : m_uptime( steady_clock::time_point::min( ) ),
            m_logger( nullptr ),
            m_supported_methods( ),
            m_settings( nullptr ),
            m_io_service( make_shared< ::io_service >( ) ),
            m_signal_set( nullptr ),
            m_session_manager( nullptr ),
            m_web_socket_manager( nullptr ),
            m_rules( ),
            m_workers( ),
#ifdef BUILD_SSL
            m_ssl_settings( nullptr ),
            m_ssl_context( nullptr ),
            m_ssl_acceptor( nullptr ),
#endif
            m_acceptor( nullptr ),
            m_resource_paths( ),
            m_resource_routes( ),
            m_ready_handler( nullptr ),
            m_signal_handlers( ),
            m_not_found_handler( nullptr ),
            m_method_not_allowed_handler( nullptr ),
            m_method_not_implemented_handler( nullptr ),
            m_failed_filter_validation_handler( nullptr ),
            m_error_handler( ServiceImpl::default_error_handler ),
            m_authentication_handler( nullptr )
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
        
            if ( m_ssl_settings == nullptr or m_ssl_settings->has_disabled_http( ) == false )
            {
#endif
            
                if ( not m_settings->get_bind_address( ).empty( ) )
                {
                    const auto address = address::from_string( m_settings->get_bind_address( ) );
                    m_acceptor = make_shared< tcp::acceptor >( *m_io_service, tcp::endpoint( address, m_settings->get_port( ) ) );
                }
                else
                {
                    m_acceptor = make_shared< tcp::acceptor >( *m_io_service, tcp::endpoint( tcp::v6( ), m_settings->get_port( ) ) );
                }
                
                m_acceptor->set_option( socket_base::reuse_address( true ) );
                m_acceptor->listen( m_settings->get_connection_limit( ) );
                
                http_listen( );
                
                const auto location = get_http_uri( )->to_string( );
                log( Logger::INFO, String::format( "Service accepting HTTP connections at '%s'.",  location.data( ) ) );
#ifdef BUILD_SSL
            }
            
#endif
        }
        
        void ServiceImpl::http_listen( void ) const
        {
            auto socket = make_shared< tcp::socket >( m_acceptor->get_io_service( ) );
            m_acceptor->async_accept( *socket, bind( &ServiceImpl::create_session, this, socket, _1 ) );
        }
        
        void ServiceImpl::setup_signal_handler( void )
        {
            if ( m_signal_handlers.empty( ) )
            {
                return;
            }
            
            m_signal_set = make_shared< signal_set >( *m_io_service );
            
            for ( const auto signal_handler : m_signal_handlers )
            {
                m_signal_set->add( signal_handler.first );
            }
            
            m_signal_set->async_wait( bind( &ServiceImpl::signal_handler, this, _1, _2 ) );
        }
        
        void ServiceImpl::signal_handler( const error_code& error, const int signal_number ) const
        {
            if ( error )
            {
                log( Logger::WARNING, String::format( "Failed to process signal '%i', '%s'.", signal_number, error.message( ).data( ) ) );
                return;
            }
            
            if ( m_signal_handlers.count( signal_number ) )
            {
                m_signal_handlers.at( signal_number )( signal_number );
            }
            
            m_signal_set->async_wait( bind( &ServiceImpl::signal_handler, this, _1, _2 ) );
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
                
                if ( not m_ssl_settings->get_bind_address( ).empty( ) )
                {
                    const auto address = address::from_string( m_ssl_settings->get_bind_address( ) );
                    m_ssl_acceptor = make_shared< tcp::acceptor >( *m_io_service, tcp::endpoint( address, m_ssl_settings->get_port( ) ) );
                }
                else
                {
                    m_ssl_acceptor = make_shared< tcp::acceptor >( *m_io_service, tcp::endpoint( tcp::v6( ), m_ssl_settings->get_port( ) ) );
                }
                
                m_ssl_acceptor->set_option( socket_base::reuse_address( true ) );
                m_ssl_acceptor->listen( m_settings->get_connection_limit( ) );
                
                https_listen( );
                
                const auto location = get_https_uri( )->to_string( );
                log( Logger::INFO, String::format( "Service accepting HTTPS connections at '%s'.",  location.data( ) ) );
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
                socket->async_handshake( asio::ssl::stream_base::server, [ this, socket ]( const error_code & error )
                {
                    if ( error )
                    {
                        log( Logger::SECURITY, String::format( "Failed SSL handshake, '%s'.", error.message( ).data( ) ) );
                        return;
                    }
                    
                    auto connection = make_shared< SocketImpl >( socket, m_logger );
                    connection->set_timeout( m_settings->get_connection_timeout( ) );
                    
                    m_session_manager->create( [ this, connection ]( const shared_ptr< Session > session )
                    {
                        session->m_pimpl->m_settings = m_settings;
                        session->m_pimpl->m_manager = m_session_manager;
                        session->m_pimpl->m_web_socket_manager = m_web_socket_manager;
                        session->m_pimpl->m_error_handler = m_error_handler;
                        session->m_pimpl->m_request = make_shared< Request >( );
                        session->m_pimpl->m_request->m_pimpl->m_socket = connection;
                        session->m_pimpl->m_request->m_pimpl->m_socket->m_error_handler = m_error_handler;
                        session->m_pimpl->m_request->m_pimpl->m_buffer = make_shared< asio::streambuf >( );
                        session->m_pimpl->m_keep_alive_callback = bind( &ServiceImpl::parse_request, this, _1, _2, _3 );
                        session->m_pimpl->m_request->m_pimpl->m_socket->read( session->m_pimpl->m_request->m_pimpl->m_buffer, "\r\n\r\n", bind( &ServiceImpl::parse_request, this, _1, _2, session ) );
                    } );
                } );
            }
            else
            {
                if ( socket not_eq nullptr and socket->lowest_layer( ).is_open( ) )
                {
                    socket->lowest_layer( ).close( );
                }
                
                log( Logger::WARNING, String::format( "Failed to create session, '%s'.", error.message( ).data( ) ) );
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
            static const regex pattern( "^\\{[a-zA-Z0-9_\\-]+: ?(.*)\\}$" );
            
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
            log( Logger::INFO, String::format( "'%s' resource route not found '%s'.",
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
                try
                {
                    m_logger->log( level, "%s", message.data( ) );
                }
                catch ( ... )
                {
                    fprintf( stderr, "Failed to create log entry: %s", message.data( ) );
                }
            }
        }
        
        void ServiceImpl::method_not_allowed( const shared_ptr< Session > session ) const
        {
            log( Logger::INFO, String::format( "'%s' '%s' method not allowed '%s'.",
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
        
        void ServiceImpl::method_not_implemented( const shared_ptr< Session > session ) const
        {
            log( Logger::INFO, String::format( "'%s' '%s' method not implemented '%s'.",
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
        
        void ServiceImpl::failed_filter_validation( const shared_ptr< Session > session ) const
        {
            log( Logger::INFO, String::format( "'%s' failed filter validation '%s'.",
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
        
        void ServiceImpl::router( const shared_ptr< Session > session ) const
        {
            log( Logger::INFO, String::format( "Incoming '%s' request from '%s' for route '%s'.",
                                               session->get_request( )->get_method( ).data( ),
                                               session->get_origin( ).data( ),
                                               session->get_request( )->get_path( ).data( ) ) );
                                               
            if ( session->is_closed( ) )
            {
                return;
            }
            
            rule_engine( session, m_rules, [ this ]( const shared_ptr< Session > session )
            {
                const auto resource_route = find_if( m_resource_routes.begin( ), m_resource_routes.end( ), bind( &ServiceImpl::resource_router, this, session, _1 ) );
                
                if ( resource_route == m_resource_routes.end( ) )
                {
                    return not_found( session );
                }
                
                const auto path = resource_route->first;
                session->m_pimpl->m_resource = resource_route->second;
                const auto request = session->get_request( );
                extract_path_parameters( path, request );
                
                const auto callback = [ this ]( const shared_ptr< Session > session )
                {
                    rule_engine( session, session->m_pimpl->m_resource->m_pimpl->m_rules, [ this ]( const shared_ptr< Session > session )
                    {
                        if ( session->is_closed( ) )
                        {
                            return;
                        }
                        
                        const auto request = session->get_request( );
                        auto method_handler = find_method_handler( session );
                        
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
                };
                
                if ( session->m_pimpl->m_resource->m_pimpl->m_authentication_handler not_eq nullptr )
                {
                    session->m_pimpl->m_resource->m_pimpl->m_authentication_handler( session, callback );
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
                auto connection = make_shared< SocketImpl >( socket, m_logger );
                connection->set_timeout( m_settings->get_connection_timeout( ) );
                
                m_session_manager->create( [ this, connection ]( const shared_ptr< Session > session )
                {
                    session->m_pimpl->m_settings = m_settings;
                    session->m_pimpl->m_manager = m_session_manager;
                    session->m_pimpl->m_web_socket_manager = m_web_socket_manager;
                    session->m_pimpl->m_error_handler = m_error_handler;
                    session->m_pimpl->m_request = make_shared< Request >( );
                    session->m_pimpl->m_request->m_pimpl->m_socket = connection;
                    session->m_pimpl->m_request->m_pimpl->m_socket->m_error_handler = m_error_handler;
                    session->m_pimpl->m_request->m_pimpl->m_buffer = make_shared< asio::streambuf >( );
                    session->m_pimpl->m_keep_alive_callback = bind( &ServiceImpl::parse_request, this, _1, _2, _3 );
                    session->m_pimpl->m_request->m_pimpl->m_socket->read( session->m_pimpl->m_request->m_pimpl->m_buffer, "\r\n\r\n", bind( &ServiceImpl::parse_request, this, _1, _2, session ) );
                } );
            }
            else
            {
                if ( socket not_eq nullptr and socket->is_open( ) )
                {
                    socket->close( );
                }
                
                log( Logger::WARNING, String::format( "Failed to create session, '%s'.", error.message( ).data( ) ) );
            }
            
            http_listen( );
        }
        
        void ServiceImpl::extract_path_parameters( const string& sanitised_path, const shared_ptr< const Request >& request ) const
        {
            smatch matches;
            static const regex pattern( "^\\{([a-zA-Z0-9_\\-]+): ?.*\\}$" );
            
            const auto folders = String::split( request->get_path( ), '/' );
            const auto declarations = String::split( m_settings->get_root( ) + "/" + m_resource_paths.at( sanitised_path ), '/' );
            
            for ( size_t index = 0; index < folders.size( ) and index < declarations.size( ); index++ )
            {
                const auto declaration = declarations[ index ];
                
                if ( declaration.front( ) == '{' and declaration.back( ) == '}' )
                {
                    regex_match( declaration, matches, pattern );
                    request->m_pimpl->m_path_parameters.insert( make_pair( matches[ 1 ].str( ), folders[ index ] ) );
                }
            }
        }
        
        function< void ( const shared_ptr< Session > ) > ServiceImpl::find_method_handler( const shared_ptr< Session > session ) const
        {
            const auto request = session->get_request( );
            const auto resource = session->get_resource( );
            const auto method_handlers = resource->m_pimpl->m_method_handlers.equal_range( request->get_method( ) );
            
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
                const auto handler = resource->m_pimpl->m_failed_filter_validation_handler;
                method_handler = ( handler == nullptr ) ? bind( &ServiceImpl::failed_filter_validation, this, _1 ) : handler;
            }
            
            return method_handler;
        }
        
        void ServiceImpl::authenticate( const shared_ptr< Session > session ) const
        {
            if ( m_authentication_handler not_eq nullptr )
            {
                m_authentication_handler( session, [ this ]( const shared_ptr< Session > session )
                {
                    m_session_manager->load( session, bind( &ServiceImpl::router, this, _1 ) );
                } );
            }
            else
            {
                m_session_manager->load( session, bind( &ServiceImpl::router, this, _1 ) );
            }
        }
        
        bool ServiceImpl::resource_router( const shared_ptr< Session > session, const pair< string, shared_ptr< const Resource > >& route ) const
        {
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
        
        void ServiceImpl::default_error_handler( const int status, const exception& error, const shared_ptr< Session > session )
        {
            if ( session not_eq nullptr and session->is_open( ) )
            {
                string body = error.what( );
                session->close( status, body, { { "Content-Type", "text/plain" }, { "Content-Length", ::to_string( body.length( ) ) } } );
            }
        }
        
        void ServiceImpl::discard_request( istream& stream )
        {
            string line = String::empty;
            
            while ( getline( stream, line ) )
            {
                if ( line == "\r" )
                {
                    break;
                }
            }
        }
        
        const map< string, string > ServiceImpl::parse_request_line( istream& stream )
        {
            smatch matches;
            static const regex pattern( "^([0-9a-zA-Z]*) ([a-zA-Z0-9:@_~!,;=#%&'\\-\\.\\/\\?\\$\\(\\)\\*\\+]+) (HTTP\\/[0-9]\\.[0-9])\\s*$" );
            string data = "";
            getline( stream, data );
            
            if ( not regex_match( data, matches, pattern ) or matches.size( ) not_eq 4 )
            {
                throw runtime_error( "Your client has issued a malformed or illegal request status line. That’s all we know." );
            }
            
            const string protocol = matches[ 3 ].str( );
            const auto delimiter = protocol.find_first_of( "/" );
            
            return map< string, string >
            {
                { "path", matches[ 2 ].str( ) },
                { "method", matches[ 1 ].str( ) },
                { "version", protocol.substr( delimiter + 1 ) },
                { "protocol", protocol.substr( 0, delimiter ) }
            };
        }
        
        const multimap< string, string > ServiceImpl::parse_request_headers( istream& stream )
        {
            smatch matches;
            string data = "";
            multimap< string, string > headers;
            static const regex pattern( "^([^:.]*): *(.*)\\s*$" );
            
            while ( getline( stream, data ) and data not_eq "\r" )
            {
                if ( not regex_match( data, matches, pattern ) or matches.size( ) not_eq 3 )
                {
                    throw runtime_error( "Your client has issued a malformed or illegal request header. That’s all we know." );
                }
                
                headers.insert( make_pair( matches[ 1 ].str( ), matches[ 2 ].str( ) ) );
            }
            
            return headers;
        }
        
        void ServiceImpl::parse_request( const error_code& error, size_t, const shared_ptr< Session > session ) const
        {
            istream stream( session->m_pimpl->m_request->m_pimpl->m_buffer.get( ) );
            
            if ( error )
            {
                discard_request( stream );
                const auto error_handler = get_error_handler( session );
                return error_handler( 400, runtime_error( error.message( ) ), session );
            }
            
            try
            {
                const auto items = parse_request_line( stream );
                const auto uri = Uri::parse( "http://localhost" + items.at( "path" ) );
                
                session->m_pimpl->m_request->m_pimpl->m_path = Uri::decode( uri.get_path( ) );
                session->m_pimpl->m_request->m_pimpl->m_method = items.at( "method" );
                session->m_pimpl->m_request->m_pimpl->m_headers = parse_request_headers( stream );
                session->m_pimpl->m_request->m_pimpl->m_query_parameters = uri.get_query_parameters( );
                
                char* locale = strdup( setlocale( LC_NUMERIC, nullptr ) );
                setlocale( LC_NUMERIC, "C" );
                session->m_pimpl->m_request->m_pimpl->m_version = stod( items.at( "version" ) );
                setlocale( LC_NUMERIC, locale );
                free( locale );
                
                authenticate( session );
            }
            catch ( const int status_code )
            {
                discard_request( stream );
                const auto error_handler = get_error_handler( session );
                error_handler( status_code, runtime_error( m_settings->get_status_message( status_code ) ), session );
            }
            catch ( const regex_error& re )
            {
                discard_request( stream );
                const auto error_handler = get_error_handler( session );
                error_handler( 500, re, session );
            }
            catch ( const runtime_error& re )
            {
                discard_request( stream );
                const auto error_handler = get_error_handler( session );
                error_handler( 400, re, session );
            }
            catch ( const exception& ex )
            {
                discard_request( stream );
                const auto error_handler = get_error_handler( session );
                error_handler( 500, ex, session );
            }
            catch ( ... )
            {
                discard_request( stream );
                auto cex = current_exception( );
                
                if ( cex not_eq nullptr )
                {
                    try
                    {
                        rethrow_exception( cex );
                    }
                    catch ( const exception& ex )
                    {
                        const auto error_handler = get_error_handler( session );
                        error_handler( 500, ex, session );
                    }
                    catch ( ... )
                    {
                        const auto error_handler = get_error_handler( session );
                        error_handler( 500, runtime_error( "Internal Server Error" ), session );
                    }
                }
                else
                {
                    const auto error_handler = get_error_handler( session );
                    error_handler( 500, runtime_error( "Internal Server Error" ), session );
                }
            }
        }
        
        const shared_ptr< const Uri > ServiceImpl::get_http_uri( void ) const
        {
            if ( m_acceptor == nullptr )
            {
                return nullptr;
            }
            
            auto endpoint = m_acceptor->local_endpoint( );
            auto address = endpoint.address( );
            auto uri = String::empty;
            
            if ( address.is_v6( ) )
            {
                uri = String::format( "http://[%s]:%u", address.to_string( ).data( ), endpoint.port( ) );
            }
            else
            {
                uri = String::format( "http://%s:%u", address.to_string( ).data( ), endpoint.port( ) );
            }
            
            return make_shared< const Uri >( uri );
        }
        
        const shared_ptr< const Uri > ServiceImpl::get_https_uri( void ) const
        {
#ifdef BUILD_SSL
        
            if ( m_ssl_acceptor == nullptr )
            {
                return nullptr;
            }
            
            auto endpoint = m_ssl_acceptor->local_endpoint( );
            auto address = endpoint.address( );
            auto uri = String::empty;
            
            if ( address.is_v6( ) )
            {
                uri = String::format( "https://[%s]:%u", address.to_string( ).data( ), endpoint.port( ) );
            }
            else
            {
                uri = String::format( "https://%s:%u", address.to_string( ).data( ), endpoint.port( ) );
            }
            
            return make_shared< const Uri >( uri );
#else
            throw runtime_error( "Not Implemented! Rebuild Restbed with SSL funcationality enabled." );
#endif
        }
        
        const function< void ( const int, const exception&, const shared_ptr< Session > ) > ServiceImpl::get_error_handler( const shared_ptr< Session >& session ) const
        {
            return ( session->m_pimpl->m_resource not_eq nullptr and session->m_pimpl->m_resource->m_pimpl->m_error_handler not_eq nullptr ) ? session->m_pimpl->m_resource->m_pimpl->m_error_handler : m_error_handler;
        }
    }
}
