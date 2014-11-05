/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <cstdio>
#include <chrono>
#include <sstream>
#include <stdexcept>
#include <functional>

//Project Includes
#include "corvusoft/restbed/mode.h"
#include "corvusoft/restbed/method.h"
#include "corvusoft/restbed/logger.h"
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/response.h"
#include "corvusoft/restbed/resource.h"
#include "corvusoft/restbed/settings.h"
#include "corvusoft/restbed/log_level.h"
#include "corvusoft/restbed/status_code.h"
#include "corvusoft/restbed/detail/service_impl.h"
#include "corvusoft/restbed/detail/path_parameter_impl.h"
#include "corvusoft/restbed/detail/request_builder_impl.h"
#include "corvusoft/restbed/detail/resource_matcher_impl.h"

//External Includes
#include <corvusoft/framework/string>

//System Namespaces
using std::list;
using std::find;
using std::bind;
using std::thread;
using std::string;
using std::istream;
using std::find_if;
using std::function;
using std::to_string;
using std::exception;
using std::shared_ptr;
using std::make_shared;
using std::invalid_argument;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::chrono::milliseconds;
using std::chrono::system_clock;

//Project Namespaces

//External Namespaces
using asio::buffer;
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
        ServiceImpl::ServiceImpl( const Settings& settings ) : m_mode( settings.get_mode( ) ),
            m_port( settings.get_port( ) ),
            m_root( settings.get_root( ) ),
            m_maximum_connections( settings.get_maximum_connections( ) ),
            m_resources( ),
            m_log_handler( nullptr ),
            m_thread( nullptr ),
            m_work( nullptr ),
            m_io_service( nullptr ),
            m_acceptor( nullptr ),
            m_authentication_handler( bind( &ServiceImpl::authentication_handler, this, _1, _2 ) ),
            m_error_handler( bind( &ServiceImpl::error_handler, this, _1, _2, _3 ) )
        {
            //n/a
        }
        
        ServiceImpl::ServiceImpl( const ServiceImpl& original ) : m_mode( original.m_mode ),
            m_port( original.m_port ),
            m_root( original.m_root ),
            m_maximum_connections( original.m_maximum_connections ),
            m_resources( original.m_resources ),
            m_log_handler( original.m_log_handler ),
            m_thread( original.m_thread ),
            m_work( original.m_work ),
            m_io_service( original.m_io_service ),
            m_acceptor( original.m_acceptor ),
            m_authentication_handler( original.m_authentication_handler ),
            m_error_handler( original.m_error_handler )
        {
            //n/a
        }
        
        ServiceImpl::~ServiceImpl( void )
        {
            try
            {
                stop( );
            }
            catch ( const exception& ex )
            {
                log( LogLevel::WARNING, String::format( "Service failed graceful shutdown: %s",  ex.what( ) ) );
            }
        }
        
        void ServiceImpl::start( void )
        {
            start( m_mode );
        }

        void ServiceImpl::start( const Mode& value )
        {
            m_io_service = make_shared< io_service >( );
            
            m_acceptor = make_shared< tcp::acceptor >( *m_io_service, tcp::endpoint( tcp::v6( ), m_port ) );
            
            m_acceptor->set_option( socket_base::reuse_address( true ) );
            
            m_acceptor->listen( m_maximum_connections );
            
            listen( );
            
            switch ( value )
            {
                case SYNCHRONOUS:
                    start_synchronous( );
                    break;
                    
                case ASYNCHRONOUS:
                    start_asynchronous( );
                    break;
                    
                default:
                    log( LogLevel::FATAL, String::format( "Service failed, unknown service mode: %i",  m_mode ) );
            }
        }
        
        void ServiceImpl::stop( void )
        {
            if ( m_work not_eq nullptr )
            {
                m_work.reset( );
            }
            
            if ( m_io_service not_eq nullptr )
            {
                m_io_service->stop( );
            }
            
            if ( m_thread not_eq nullptr and m_thread->joinable( ) )
            {
                m_thread->join( );
            }
            
            log( LogLevel::INFO, "Service stopped" );
        }
        
        void ServiceImpl::publish( const Resource& value )
        {
            auto paths = value.get_paths( );
            
            if ( paths.empty( ) )
            {
                paths.push_back( m_root );
            }
            else if ( m_root not_eq "/" )
            {
                for ( auto& path : paths )
                {
                    path = String::format( "/%s/%s", m_root.data( ), path.data( ) );
                }
            }
            
            Resource resource( value );
            resource.set_paths( paths );
            
            auto iterator = find_if( m_resources.begin( ),
                                     m_resources.end( ),
                                     [&] ( const Resource & item )
            {
                return item == resource;
            } );
            
            if ( iterator not_eq m_resources.end( ) )
            {
                *iterator = resource;
            }
            else
            {
                m_resources.push_back( resource );
            }
            
            log( LogLevel::INFO, String::format( "Published '%s' resource", resource.get_path( ).data( ) ) );
        }
        
        void ServiceImpl::suppress( const Resource& value )
        {
            auto position = find( m_resources.begin( ), m_resources.end( ), value );
            
            if ( position not_eq m_resources.end( ) )
            {
                string path = position->get_path( );
                
                m_resources.erase( position );
                
                log( LogLevel::INFO, String::format( "Suppressed '%s' resource", path.data( ) ) );
            }
            else
            {
                log( LogLevel::INFO, String::format( "Failed to suppress  '%s' resource, not found", value.get_path( ).data( ) ) );
            }
        }
        
        void ServiceImpl::set_log_handler(  const shared_ptr< Logger >& value )
        {
            m_log_handler = value;
        }
        
        void ServiceImpl::set_authentication_handler( function< void ( const Request&, Response& ) > value )
        {
            m_authentication_handler = value;
        }
        
        void ServiceImpl::set_error_handler( function< void ( const int, const Request&, Response& ) > value )
        {
            m_error_handler = value;
        }
        
        ServiceImpl& ServiceImpl::operator =( const ServiceImpl& value )
        {
            m_mode = value.m_mode;
            
            m_port = value.m_port;
            
            m_root = value.m_root;
            
            m_resources = value.m_resources;
            
            m_log_handler = value.m_log_handler;
            
            m_maximum_connections = value.m_maximum_connections;
            
            m_error_handler = value.m_error_handler;
            
            m_authentication_handler = value.m_authentication_handler;
            
            return *this;
        }
        
        void ServiceImpl::listen( void )
        {
            auto socket = make_shared< tcp::socket >( m_acceptor->get_io_service( ) );
            
            m_acceptor->async_accept( *socket, bind( &ServiceImpl::router, this, socket, _1 ) );
        }
        
        void ServiceImpl::start_synchronous( void )
        {
            m_io_service->run( );
            
            log( LogLevel::INFO, "Synchronous Service Started" );
        }
        
        void ServiceImpl::start_asynchronous( void )
        {
            m_work = make_shared< io_service::work >( *m_io_service );
            
            auto task = static_cast< size_t ( io_service::* )( ) >( &io_service::run );
            
            m_thread = make_shared< thread >( task, m_io_service );
            
            log( LogLevel::INFO, "Asynchronous Service Started" );
        }
        
        void ServiceImpl::router( shared_ptr< tcp::socket > socket, const error_code& error )
        {
            Request request;
            Response response;
            
            try
            {
                if ( error )
                {
                    throw asio::system_error( error );
                }
                
                error_code code;
                
                while ( socket->available( code ) == 0 )
                {
                    if ( code )
                    {
                        throw asio::system_error( code );
                    }
                    
                    std::this_thread::sleep_for( milliseconds( 250 ) );
                }
                
                asio::streambuf buffer;
                read( *socket, buffer, asio::transfer_at_least( socket->available( ) ), code );

                if ( code )
                {
                    throw asio::system_error( code );
                }
                
                istream stream( &buffer );
                
                RequestBuilderImpl builder( stream );
                builder.set_origin( socket->remote_endpoint( ).address( ).to_string( ) );
                request = builder.build( );
                
                Resource resource = resolve_resource_route( request );
                
                auto parameters = PathParameterImpl::parse( request.get_path( ), resource.get_path( ) );
                builder.set_path_parameters( parameters );
                
                request = builder.build( );
                
                m_authentication_handler( request, response );
                
                const int status = response.get_status_code( );
                
                if ( status == StatusCode::OK )
                {
                    log( LogLevel::INFO, String::format( "Incoming %s request for '%s' resource from %s",
                                                         request.get_method( ).to_string( ).data( ),
                                                         request.get_path( ).data( ),
                                                         request.get_origin( ).data( ) ) );
                                                         
                    response = invoke_method_handler( request, resource );
                }
                else
                {
                    log( LogLevel::SECURITY, String::format( "Unauthorised %s request for '%s' resource from %s",
                                                             request.get_method( ).to_string( ).data( ),
                                                             request.get_path( ).data( ),
                                                             request.get_origin( ).data( ) ) );
                }
            }
            catch ( const asio::system_error& se )
            {
                log( LogLevel::FATAL, se.what( ) );
                
                response.set_status_code( StatusCode::INTERNAL_SERVER_ERROR );
            }
            catch ( const StatusCode::Value status_code )
            {
                m_error_handler( status_code, request, response );
            }
            
            asio::write( *socket, buffer( response.to_bytes( ) ), asio::transfer_all( ) );
            
            listen( );
        }
        
        Resource ServiceImpl::resolve_resource_route( const Request& request ) const
        {
            Resource resource;
            
            auto iterator = find_if( m_resources.begin( ), m_resources.end( ), ResourceMatcherImpl( request ) );
            
            if ( iterator not_eq m_resources.end( ) )
            {
                resource = *iterator;
            }
            else
            {
                throw StatusCode::NOT_FOUND;
            }
            
            return resource;
        }
        
        Response ServiceImpl::invoke_method_handler( const Request& request, const Resource& resource  ) const
        {
            Method method = request.get_method( );
            
            auto handle = resource.get_method_handler( method );
            
            return handle( request );
        }
        
        void ServiceImpl::log( const LogLevel level, const string& message )
        {
            if ( m_log_handler not_eq nullptr )
            {
                m_log_handler->log( level, "%s", message.data( ) );
            }
        }
        
        void ServiceImpl::error_handler( const int status_code, const Request& request, Response& response )
        {
            string status_message = String::empty;
            
            try
            {
                status_message = StatusCode::to_string( status_code );
            }
            catch ( const invalid_argument& ia )
            {
                status_message = ia.what( );
            }
            
            log( LogLevel::ERROR, String::format( "Error %i (%s) requesting '%s' resource\n",
                                                  status_code,
                                                  status_message.data( ),
                                                  request.get_path( ).data( ) ) );
                                                  
            response.set_status_code( status_code );
            response.set_header( "Content-Type", "text/plain" );
            response.set_body( status_message );
        }
        
        void ServiceImpl::authentication_handler( const Request&, Response& response )
        {
            response.set_status_code( StatusCode::OK );
        }
    }
}
