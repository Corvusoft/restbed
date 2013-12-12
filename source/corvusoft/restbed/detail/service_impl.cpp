/*
 * Copyright (c) 2013 Corvusoft
 */

//System Includes
#include <cstdio>
#include <chrono>
#include <stdexcept>
#include <functional>

//Project Includes
#include "corvusoft/restbed/mode.h"
#include "corvusoft/restbed/method.h"
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/response.h"
#include "corvusoft/restbed/resource.h"
#include "corvusoft/restbed/settings.h"
#include "corvusoft/restbed/log_level.h"
#include "corvusoft/restbed/status_code.h"
#include "corvusoft/restbed/detail/helpers/date.h"
#include "corvusoft/restbed/detail/helpers/string.h"
#include "corvusoft/restbed/detail/service_impl.h"
#include "corvusoft/restbed/detail/path_parameter.h"
#include "corvusoft/restbed/detail/request_builder.h"
#include "corvusoft/restbed/detail/resource_matcher.h"

//External Includes

//System Namespaces
using std::list;
using std::thread;
using std::string;
using std::find_if;
using std::to_string;
using std::exception;
using std::shared_ptr;
using std::make_shared;
using std::placeholders::_1;
using std::chrono::system_clock;

//Project Namespaces
using restbed::detail::helpers::Date;
using restbed::detail::helpers::String;

//External Namespaces
using asio::buffer;
using asio::ip::tcp;
using asio::io_service;
using asio::error_code;
using asio::system_error;

namespace restbed
{
    namespace detail
    {
        ServiceImpl::ServiceImpl( const Settings& settings ) : m_mode( settings.get_mode( ) ),
                                                               m_port( settings.get_port( ) ),
                                                               m_root( settings.get_root( ) ),
                                                               m_maximum_connections( settings.get_maximum_connections( ) ),
                                                               m_resources( ),
                                                               m_thread( nullptr ),
                                                               m_work ( nullptr ),
                                                               m_io_service( nullptr ),
                                                               m_acceptor( nullptr )
        {
            //n/a
        }
        
        ServiceImpl::ServiceImpl( const ServiceImpl& original ) : m_mode( original.m_mode ),
                                                                  m_port( original.m_port ),
                                                                  m_root( original.m_root ),
                                                                  m_maximum_connections( original.m_maximum_connections ),
                                                                  m_resources( original.m_resources ),
                                                                  m_thread( original.m_thread ),
                                                                  m_work( original.m_work ),
                                                                  m_io_service( original.m_io_service ),
                                                                  m_acceptor( original.m_acceptor )
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
                log_handler( LogLevel::WARNING, "Service failed graceful shutdown: " + string( ex.what( ) ) );
            }
        }

        void ServiceImpl::start( void )
        {
            m_io_service = make_shared< io_service >( );

            m_acceptor = make_shared< tcp::acceptor >( *m_io_service, tcp::endpoint( tcp::v6( ), m_port ) );

            m_acceptor->listen( m_maximum_connections );

            listen( );

            switch ( m_mode )
            {
                case SYNCHRONOUS:
                    start_synchronous( );
                    break;
                case ASYNCHRONOUS:
                    start_asynchronous( );
                    break;
                default:
                    log_handler( LogLevel::FATAL, "Service failed, unknown service mode: " + ::to_string( m_mode ) );
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
        }

        void ServiceImpl::publish( const Resource& value )
        {
            string path = String::format( "/%s/%s", m_root.data( ), value.get_path( ).data( ) );

            auto iterator = find_if( m_resources.begin( ),
                                     m_resources.end( ),
                                    [&] ( const Resource& resource ) {
                                        return resource.get_path( ) == path;
                                    });

            if ( iterator not_eq m_resources.end( ) )
            {
                *iterator = value;
            }
            else
            {
                Resource resource( value );
                resource.set_path( path );

                m_resources.push_back( resource );
            }
        }

        void ServiceImpl::suppress( const Resource& value )
        {
            auto position = std::find( m_resources.begin( ), m_resources.end( ), value );
        
            m_resources.erase( position );
        }

        void ServiceImpl::error_handler( const Request& request, Response& response )
        {
            log_handler( LogLevel::ERROR, "Internal Server Error" );
            log_handler( LogLevel::INFO, "Request\n%s", request.to_bytes( ).data( ) );
            log_handler( LogLevel::INFO, "Response\n%s", response.to_bytes( ).data( ) );

            response.set_status_code( StatusCode::INTERNAL_SERVER_ERROR );
        }

        void ServiceImpl::log_handler(  const LogLevel level, const string& format, ... )
        {
            FILE* descriptor = nullptr;

            switch ( level )
            {
                case INFO:
                case DEBUG:
                    descriptor = stdout;
                    break;
                case FATAL:
                case ERROR:
                case WARNING:
                case SECURITY:
                default:
                    descriptor = stderr;
            }

            string label = build_log_label( level );

            va_list arguments;
            
            va_start( arguments, format );

            fprintf( descriptor, "%s", label.data( ) );
            vfprintf( descriptor, format.data( ), arguments );
            fprintf( descriptor, "\n" );

            va_end( arguments );
        }

        void ServiceImpl::authentication_handler( const Request&, Response& response )
        {
            response.set_status_code( StatusCode::OK );
        }

        bool ServiceImpl::operator <( const ServiceImpl& rhs ) const
        {
            return m_port < rhs.m_port;
        }
        
        bool ServiceImpl::operator >( const ServiceImpl& rhs ) const
        {
            return m_port > rhs.m_port;
        }
        
        bool ServiceImpl::operator ==( const ServiceImpl& rhs ) const
        {
            return m_port == rhs.m_port;
        }
        
        bool ServiceImpl::operator !=( const ServiceImpl& rhs ) const
        {
            return m_port not_eq rhs.m_port;
        }

        ServiceImpl& ServiceImpl::operator =( const ServiceImpl& rhs )
        {
            m_port = rhs.m_port;

            m_root = rhs.m_root;

            m_resources = rhs.m_resources;

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
        }

        void ServiceImpl::start_asynchronous( void )
        {
            m_work = make_shared< io_service::work >( *m_io_service );

            auto task = static_cast< size_t ( io_service::* )( ) >( &io_service::run );

            m_thread = make_shared< thread >( task, m_io_service );
        }

        void ServiceImpl::router( shared_ptr< tcp::socket > socket, const error_code& error )
        {
            Request request;
            Response response;

            try
            {
                if ( error )
                {
                    throw StatusCode::INTERNAL_SERVER_ERROR;
                }

                RequestBuilder builder;
                builder.parse( socket );
                request = builder.build( );

                Resource resource = resolve_resource_route( request );

                auto parameters = PathParameter::parse( request.get_path( ), resource.get_path( ) );
                builder.set_path_parameters( parameters );

                request = builder.build( );

                authentication_handler( request, response );

                const int status = response.get_status_code( );

                if ( status not_eq StatusCode::UNAUTHORIZED and status not_eq StatusCode::FORBIDDEN )
                {
                    response = invoke_method_handler( request, resource );
                }
                else
                {
                    log_handler( LogLevel::SECURITY, "Unauthorized access attempted." );
                }
            }
            catch ( const int status_code )
            {
                response.set_status_code( status_code );

                error_handler( request, response );
            }

            asio::write( *socket, buffer( response.to_bytes( ) ), asio::transfer_all( ) );

            listen( );
        }

        string ServiceImpl::build_log_label( const LogLevel level ) const
        {
            string tag = String::empty;

            switch ( level )
            {
                case INFO:
                    tag = "INFO";
                    break;
                case DEBUG:
                    tag = "DEBUG";
                    break;
                case FATAL:
                    tag = "FATAL";
                    break;
                case ERROR:
                    tag = "ERROR";
                    break;
                case WARNING:
                    tag = "WARNING";
                    break;
                case SECURITY:
                    tag = "SECURITY";
                    break;
                default:
                    tag = "UNKNOWN";
            }

            string timestamp = Date::format( system_clock::now( ) );

            string label = String::format( "[%s %s] ", tag.data( ), timestamp.data( ) );
    
            return label;
        }

        Resource ServiceImpl::resolve_resource_route( const Request& request ) const
        {
            Resource resource;
    
            auto iterator = find_if( m_resources.begin( ), m_resources.end( ), ResourceMatcher( request ) ); 

            if ( iterator not_eq m_resources.end( ) )
            {
                resource = *iterator;
            }
            else
            {
                resource.set_method_handler( request.get_method( ), ServiceImpl::resource_not_found_handler );
            }

            return resource;
        }

        Response ServiceImpl::invoke_method_handler( const Request& request, const Resource& resource  ) const
        {
            Method method = request.get_method( );  

            auto handle = resource.get_method_handler( method );
            
            return handle( request );
        }

        Response ServiceImpl::resource_not_found_handler( const Request& )
        {
            Response response;
            response.set_status_code( StatusCode::NOT_FOUND );

            return response;
        }
    }
}
