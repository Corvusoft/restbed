/*
 * Site: restbed.corvusoft.co.uk
 * Author: Ben Crowhurst
 *
 * Copyright (c) 2013 Restbed Core Development Team and Community Contributors
 *
 * This file is part of Restbed.
 *
 * Restbed is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Restbed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with Restbed.  If not, see <http://www.gnu.org/licenses/>.
 */

//System Includes
#include <cstdarg>
#include <sstream>
#include <stdexcept>
#include <functional>

//Project Includes
#include "restbed/method.h"
#include "restbed/request.h"
#include "restbed/response.h"
#include "restbed/resource.h"
#include "restbed/settings.h"
#include "restbed/log_level.h"
#include "restbed/status_code.h"
#include "restbed/detail/service_impl.h"
#include "restbed/detail/helpers/string.h"
#include "restbed/detail/resource_matcher.h"

//External Includes
using asio::buffer;
using asio::ip::tcp;
using asio::io_service;
using asio::error_code;
using asio::system_error;

//System Namespaces
using std::list;
using std::string;
using std::find_if;
using std::istream;
using std::shared_ptr;
using std::stringstream;
using std::runtime_error;
using std::placeholders::_1;

//Project Namespaces
using restbed::detail::helpers::String;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        ServiceImpl::ServiceImpl( const Settings& settings ) : m_port( settings.get_port( ) ),
                                                               m_root( settings.get_root( ) ),
                                                               m_resources( ),
                                                               m_io_service( nullptr ),
                                                               m_acceptor( nullptr )
        {
            //n/a
        }
        
        ServiceImpl::ServiceImpl( const ServiceImpl& original ) : m_port( original.m_port ),
                                                                  m_root( original.m_root ),
                                                                  m_resources( original.m_resources ),
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
            m_io_service = shared_ptr< io_service >( new io_service );
                
            m_acceptor = shared_ptr< tcp::acceptor >( new tcp::acceptor( *m_io_service, tcp::endpoint( tcp::v6( ), m_port ) ) );

            listen( );

            m_io_service->run( );
        }

        void ServiceImpl::stop( void )
        {
            if ( m_io_service not_eq nullptr )
            {
                m_io_service->stop( );
            }
        }

        void ServiceImpl::publish( const Resource& value )
        {
            //when comparing... don't change user data!
            //path = String::join( "%s/%s", m_root, value.get_path( ) );
            //path = String::deduplicate( root, '/' );
            //path = String::lowercase( path );

            Resource resource( value );
            resource.set_path( "/" + m_root + "/" + value.get_path( ) );

            m_resources.push_back( resource );
        }

        void ServiceImpl::suppress( const Resource& value )
        {
            auto position = std::find( m_resources.begin( ), m_resources.end( ), value );
        
            m_resources.erase( position ); //if async == true grab mutex first!
        }

        void ServiceImpl::error_handler( const Request& request, Response& response )
        {
            log_handler( LogLevel::ERROR, "Failed to process request." );

            response.set_status_code( StatusCode::INTERNAL_SERVER_ERROR );
        }

        void ServiceImpl::log_handler(  const LogLevel level, const string& format, ... )
        {
            //[Error 12:18:08] Failed to process request.
            //[Error 12:18:08] Headers
            //[Error 12:18:08] Url

            //string message = "[" + LogLevel::to_string( level ) + time + "] " + format;

            va_list arguments;
            
            va_start( arguments, format );
            
            vfprintf( stderr, format.data( ), arguments );
            
            va_end( arguments );
        }

        void ServiceImpl::authentication_handler( const Request&, Response& response )
        {
            response.set_status_code( StatusCode::OK );
        }

        void ServiceImpl::listen( void )
        {
            shared_ptr< tcp::socket > socket( new tcp::socket( m_acceptor->get_io_service( ) ) );
        
            m_acceptor->async_accept( *socket, bind( &ServiceImpl::router, this, socket, _1 ) );
        }

        Resource ServiceImpl::resolve_resource_route( const Request& request ) const
        {
            auto resource = find_if( m_resources.begin( ), m_resources.end( ), ResourceMatcher( request ) ); 

            return *resource;
        }

        Request ServiceImpl::parse_incoming_request( shared_ptr< tcp::socket >& socket ) const
        {
            error_code status;
            
            asio::streambuf buffer;
            
            asio::read_until( *socket, buffer, "\r\n", status );
            
            istream stream( &buffer );

            return Request::parse( stream );
        }

        Response ServiceImpl::invoke_method_handler( const Request& request, const Resource& resource  ) const
        {
            Method method = request.get_method( );  

            auto handle = resource.get_method_handler( method );
                
            return handle( request );
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

                request = parse_incoming_request( socket );

                authentication_handler( request, response );

                const int status = response.get_status_code( );

                if ( status not_eq StatusCode::UNAUTHORIZED and status not_eq StatusCode::FORBIDDEN )
                {
                    const auto& resource = resolve_resource_route( request );

                    response = invoke_method_handler( request, resource );
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
    }
}
