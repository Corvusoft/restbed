/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <cstdio>
#include <stdexcept>
#include <functional>

//Project Includes
#include "corvusoft/restbed/logger.h"
#include "corvusoft/restbed/session.h"
#include "corvusoft/restbed/resource.h"
#include "corvusoft/restbed/settings.h"
#include "corvusoft/restbed/status_codes.h"
#include "corvusoft/restbed/detail/session_impl.h"
#include "corvusoft/restbed/detail/service_impl.h"
// #include "corvusoft/restbed/detail/path_parameter_impl.h"
// #include "corvusoft/restbed/detail/request_builder_impl.h"
// #include "corvusoft/restbed/detail/response_builder_impl.h"
// #include "corvusoft/restbed/detail/resource_matcher_impl.h"

//External Includes
#include <corvusoft/framework/string>

//System Namespaces
using std::list;
using std::find;
using std::bind;
using std::string;
using std::find_if;
using std::function;
using std::to_string;
using std::exception;
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;
using std::shared_ptr;
using std::invalid_argument;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

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
        ServiceImpl::ServiceImpl( const Settings& settings ) : m_port( settings.get_port( ) ),
            m_root( settings.get_root( ) ),
            // m_maximum_connections( settings.get_maximum_connections( ) ),
            // m_connection_timeout( settings.get_connection_timeout( ).count( ) ),
            m_resources( ),
            m_log_handler( nullptr ),
            m_io_service( nullptr ),
            m_acceptor( nullptr ),
            m_sessions( ),
            m_authentication_handler( &ServiceImpl::authentication_handler ),
            m_error_handler( bind( &ServiceImpl::error_handler, this, _1, _2 ) )
        {
            return;
        }
        
        // ServiceImpl::ServiceImpl( const ServiceImpl& original ) : m_port( original.m_port ),
        //     m_root( original.m_root ),
        //     // m_maximum_connections( original.m_maximum_connections ),
        //     // m_connection_timeout( original.m_connection_timeout ),
        //     m_resources( original.m_resources ),
        //     m_log_handler( original.m_log_handler ),
        //     m_io_service( original.m_io_service ),
        //     m_acceptor( original.m_acceptor ),
        //     m_authentication_handler( original.m_authentication_handler ),
        //     m_error_handler( original.m_error_handler )
        // {
        //     return;
        // }
        
        ServiceImpl::~ServiceImpl( void )
        {
            try
            {
                stop( );
            }
            catch ( ... )
            {
                log( Logger::Level::WARNING, "Service failed graceful shutdown." );
            }
        }
        
        void ServiceImpl::stop( void )
        {
            if ( m_io_service not_eq nullptr )
            {
                m_io_service->stop( );
            }

            // log( Logger::Level::INFO, "Service stopped" );
        }

        void ServiceImpl::start( void )
        {
            m_io_service = make_shared< io_service >( );
            
            m_acceptor = make_shared< tcp::acceptor >( *m_io_service, tcp::endpoint( tcp::v6( ), m_port ) );
            m_acceptor->set_option( socket_base::reuse_address( true ) );
            m_acceptor->listen(  );//m_maximum_connections );
            
            listen( );

            // log( Logger::Level::INFO, "Service Started" );

            m_io_service->run( );

            // log( Logger::Level::INFO, "Service Stopped" );
        }
        
        void ServiceImpl::publish( const shared_ptr< Resource >& value )
        {
            //if ( not has_unique_paths( value.get_paths( ) ) )
            //{
            //    throw invalid_argument( "Resource would pollute namespace. Please ensure all published resources have unique paths." );
            //}

            //const auto& paths = resource->get_paths( );
            //m_paths.insert( paths.begin( ), paths.end( ) );

            //m_resources.push_back( value );

            //log( Logger::Level::INFO,
            //     String::format( "Published resource at '%s'", String::join( resource.get_paths( ), ", " ) ) );

            //no need to check for root path.  before running resource match make sure it has the /root
            //otherwise call service->not_found_handler
        }
        
        void ServiceImpl::suppress( const shared_ptr< Resource >& value )
        {
            //if ( m_resource.erase( value ) )
            //{
            //    log( Logger::Level::INFO,
            //         String::format( "Resource with identifier '%s' suppressed.", value.get_id( ).data( ) ) );
            //}
            //else
            //{
            //    log( Logger::Level::INFO,
            //         String::format( "Failed to suppress resource with identifier '%s'; Not Found.", value.get_id( ).data( ) ) );
            //}
        }
        
        void ServiceImpl::set_log_handler(  const shared_ptr< Logger >& value )
        {
            m_log_handler = value;
        }
        
        void ServiceImpl::set_authentication_handler( const function< void ( const shared_ptr< Session >& ) >& value )
        {
            m_authentication_handler = value;
        }
        
        void ServiceImpl::set_error_handler( const function< void ( const int, const shared_ptr< Session >& ) >& value )
        {
            m_error_handler = value;
        }
        
        // ServiceImpl& ServiceImpl::operator =( const ServiceImpl& value )
        // {
        //     m_port = value.m_port;
            
        //     m_root = value.m_root;
            
        //     m_resources = value.m_resources;
            
        //     m_log_handler = value.m_log_handler;

        //     // m_connection_timeout = value.m_connection_timeout;
            
        //     // m_maximum_connections = value.m_maximum_connections; connection_limit
            
        //     m_error_handler = value.m_error_handler;
            
        //     m_authentication_handler = value.m_authentication_handler;
            
        //     return *this;
        // }
        
        void ServiceImpl::listen( void )
        {
            auto socket = make_shared< tcp::socket >( m_acceptor->get_io_service( ) );
            
            m_acceptor->async_accept( *socket, bind( &ServiceImpl::create_session, this, socket, _1 ) );
        }

        void ServiceImpl::router( const shared_ptr< Session >& session )
        try
        {
//            {
//                m_authentication_handler( session );
//
//                if ( session.is_closed( ) )
//                {
//                    return;
//                }
//
//                const auto resource = find_matching_resource_by_path( session );
//
//                if ( resource == nullptr )
//                {
//                    return m_not_found_handler( session );
//                }
//
//                const auto method_handler = find_first_matching_method_handler_by_filters( resource );
//
//                if ( method_handler == nullptr )
//                {
//                    if ( m_service_methods.count( session.get_request( ).get_method( ) ) == 0 )
//                    {
//                        //resource has m_method_not_implemented_handler )
//                        m_method_not_implemented_handler( session );
//                        return;
//                    }
//                    else
//                    {
//                        //if ( resource has method_not_allowed_handler )
//                        m_method_not_allowed_handler( session );
//                        return;
//                    }
//                }
//
//                session->m_pimpl->set_resource( resource );
//                session->m_pimpl->set_default_headers( m_default_headers ); 
//
//                method_handler( session );
//
//                if ( session.is_closed( ) )
//                {
//                    //delete from session store
//                }
//            } );
        }
        catch ( const exception& ex )
        {
            // resource_error_handler = resource->get_error_handler( );
            // resource_error_handler( session );
            // m_error_handler( session );
        }
        catch ( ... )
        {
            // resource_error_handler = resource->get_error_handler( );
            // resource_error_handler( session );
            // m_error_handler( session );
        }

        void ServiceImpl::create_session( shared_ptr< tcp::socket > socket, const error_code& error )
        {
            //if ( error )
            //{
            //   //log, error handler and close connection.
            //}

            auto session = make_shared< Session >( );
            session->m_pimpl->set_socket( socket );
            session->m_pimpl->fetch( bind( &ServiceImpl::router, this, _1 ), session );

            m_sessions[ session->get_id( ) ] = session;
        }





            // Request request;
            // Response response;

            // do
            // {
            //     try
            //     {
            //         if ( error )
            //         {
            //             throw asio::system_error( error );
            //         }

            //         set_socket_timeout( socket );
                    
            //         RequestBuilderImpl builder( socket );
            //         request = builder.build( );
                    
            //         Resource resource = resolve_resource_route( request );
                    
            //         auto parameters = PathParameterImpl::parse( request.get_path( ), resource.get_path( ) );
            //         builder.set_path_parameters( parameters );
                    
            //         request = builder.build( );

            //         m_authentication_handler( request, response );
                    
            //         const int status = response.get_status_code( );
                    
            //         if ( status == 200 )
            //         {
            //             log( Logger::Level::INFO, String::format( "Incoming %s request for '%s' resource from %s",
            //                                                       request.get_method( ).data( ),
            //                                                       request.get_path( ).data( ),
            //                                                       request.get_origin( ).data( ) ) );
                                                             
            //             response = invoke_method_handler( request, resource );
            //         }
            //         else
            //         {
            //             log( Logger::Level::SECURITY, String::format( "Unauthorised %s request for '%s' resource from %s",
            //                                                           request.get_method( ).data( ),
            //                                                           request.get_path( ).data( ),
            //                                                           request.get_origin( ).data( ) ) );
            //         }
            //     }
            //     catch ( const asio::system_error& se )
            //     {
            //         log( Logger::Level::FATAL, se.what( ) );
            //         response.set_status_code( 500 );
            //     }
            //     catch ( const int status_code )
            //     {
            //         m_error_handler( status_code, request, response );
            //     }
            //     catch ( const exception& ex )
            //     {
            //         log( Logger::Level::ERROR, String::format( "Error 500 (Internal Server Error) '%s'\nrequest:\n%s\n",
            //                                                    ex.what( ),
            //                                                    RequestBuilderImpl::to_bytes( request ).data( ) ) );

            //         m_error_handler( 500, request, response );
            //     }

            //     ResponseBuilderImpl::write( response, socket );
            // }
            // while ( "keep-alive" == String::lowercase( response.get_header( "Connection" ) ) );

            // listen( );
        //}
        
        //Resource ServiceImpl::resolve_resource_route( const Request& request ) const
        //{
            // Resource resource;
            
            // auto iterator = find_if( m_resources.begin( ), m_resources.end( ), ResourceMatcherImpl( request ) );
            
            // if ( iterator not_eq m_resources.end( ) )
            // {
            //     resource = *iterator;
            // }
            // else
            // {
            //     throw 404;
            // }

            // return resource;
        //}
        
        //Response ServiceImpl::invoke_method_handler( const Request& request, const Resource& resource  ) const
        //{   
            // auto callback = resource.get_method_handler( request.get_method( ) );   
            // return callback( request );
        //}
        
        void ServiceImpl::log( const Logger::Level level, const string& message )
        {
            // if ( m_log_handler not_eq nullptr )
            // {
            //     m_log_handler->log( level, "%s", message.data( ) );
            // }
        }

        void ServiceImpl::authentication_handler( const shared_ptr< Session >& value )
        {
            return;
        }
        
        void ServiceImpl::error_handler( const int status_code, const shared_ptr< Session >& session )
        {
            // const auto& iterator = status_codes.find( status_code );

            // const string status_message = ( iterator not_eq status_codes.end( ) ) ?
            //                                 iterator->second :
            //                                 "No Appropriate Status Message Found";
            
            // log( Logger::Level::ERROR, String::format( "Error %i (%s) requesting '%s' resource\n",
            //                                            status_code,
            //                                            status_message.data( ),
            //                                            request.get_path( ).data( ) ) );
                                                  
            // response.set_status_code( status_code );
            // response.set_header( "Content-Type", "text/plain; charset=us-ascii" );
            // response.set_body( status_message );
        }

        //void ServiceImpl::set_socket_timeout( shared_ptr< tcp::socket > socket )
        //{
            // struct timeval value;
            // value.tv_usec = 0;
            // value.tv_sec = m_connection_timeout;

            // auto native_socket = socket->native( );
            // int status = setsockopt( native_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast< char* >( &value ), sizeof( value ) );

            // if ( status == -1 )
            // {
            //     throw runtime_error( "Failed to set socket receive timeout" );
            // }

            // status = setsockopt( native_socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast< char* >( &value ), sizeof( value ) );

            // if ( status == -1 )
            // {
            //     throw runtime_error( "Failed to set socket send timeout" );
            // }
        //}
    }
}
