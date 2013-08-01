/*
 * Site: restbed.net
 * Author: Ben Crowhurst
 *
 * Copyright (c) 2013 Restbed Core Development Team and Community Contributors
 *
 * This file is part of Restbed.
 *
 * AppOn is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AppOn is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with AppOn.  If not, see <http://www.gnu.org/licenses/>.
 */

//System Includes
#include <cstdarg>
#include <sstream>
#include <stdexcept>
#include <functional>
#include <iostream> //debug

//Project Includes
#include "restbed/uri.h"
#include "restbed/method.h"
#include "restbed/string.h"
#include "restbed/request.h"
#include "restbed/response.h"
#include "restbed/resource.h"
#include "restbed/settings.h"
#include "restbed/log_level.h"
#include "restbed/resource_matcher.h"
#include "restbed/detail/service_impl.h"

//External Includes
using asio::buffer;
using asio::ip::tcp;
using asio::io_service;
using asio::error_code;
using asio::system_error;

//System Namespaces
using std::list;
using std::string;
using std::istream;
using std::shared_ptr;
using std::stringstream;
using std::runtime_error;
using std::placeholders::_1;

//Project Namespaces

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
            catch ( const runtime_error& re )
            {
                log_handler( LogLevel::WARNING, "Service failed graceful shutdown: " + string( re.what( ) ) );
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
            m_io_service->stop( );
        }

        void ServiceImpl::publish( const Resource& value )
        {
            string path = "/" + m_root + "/" + value.get_path( ); //remove double /////

            Resource resource = value;
            resource.set_path( path );

            m_resources.push_back( resource );
        }

        void ServiceImpl::suppress( const Resource& value )
        {
            auto position = std::find( m_resources.begin( ), m_resources.end( ), value );
        
            m_resources.erase( position );
        }

        void ServiceImpl::error_handler( const Request& request ) //message
        {
            //500 Internal Server Error

            log_handler( LogLevel::ERROR, "Failed to process request." );
        }
        
        bool ServiceImpl::authentication_handler( const Request& request )
        {
            return true;
        }

        void ServiceImpl::log_handler(  const LogLevel level, const std::string& format, ... )
        {
            //check for a log file first!?
            //timestamp the entry!
            //[Error 12:18:08] Failed to process request.
            //[Error 12:18:08] Headers
            //[Error 12:18:08] Url

            va_list arguments;
            
            va_start( arguments, format );
            
            vfprintf( stderr, format.data( ), arguments );
            
            va_end( arguments );
        }

        void ServiceImpl::listen( void )
        {
            shared_ptr< tcp::socket > socket( new tcp::socket( m_acceptor->get_io_service( ) ) );
        
            m_acceptor->async_accept( *socket, bind( &ServiceImpl::router, this, socket, _1 ) );
        }

        void ServiceImpl::build_request_path( istream& stream, Request& request, shared_ptr< tcp::socket >& socket )
        {
            string value = "";
            
            stream >> value;
            
            string::size_type index = value.find_first_of( '?' );
            
            string path = value.substr( 0, index );
                        
            asio::ip::tcp::resolver resolver(*m_io_service);

            asio::ip::tcp::resolver::iterator destination = resolver.resolve(socket->local_endpoint());

            uint16_t port = socket->local_endpoint().port();

            std::cout << "Uri path: " << "http://" << destination->host_name( ) << ":" << std::to_string( port ) << path << std::endl;

            //check if we need forward slash for concat.
            request.set_uri( Uri( "http://" + destination->host_name( ) + ":" + std::to_string( port ) + path ) );
            
            std::cout << "Uri: " << request.get_uri( ).to_string( ) << std::endl;

            string query = value.substr( index + 1, value.length( ) );
            
            stringstream  data( query );
            
            string parameter = "";
            
            while( std::getline( data, parameter, '&' ) )
            {
                string::size_type index = parameter.find_first_of( '=' );
                
                string name = parameter.substr( 0, index );
                
                string value = parameter.substr( index + 1, parameter.length( ) );
                
                //decode url
                
                request.set_query_parameter( name, value );
            }
        }

        void ServiceImpl::build_request_method( istream& stream, Request& request )
        {
            string value = ""; //String::empty
            
            stream >> value;
            
            request.set_method( value );
        }

        void ServiceImpl::build_request_version( istream& stream, Request& request )
        {
            string value = "";
            
            stream >> value;
            
            request.set_version( value );
        }

        void ServiceImpl::build_request_headers( istream& stream, Request& request )
        {
            const char* CR = "\r";
            
            std::string header = "";
            
            while( std::getline(stream, header) && header != CR )
            {
                header.erase( header.length( ) - 1 ); //remove CR
                
                std::string::size_type index = header.find_first_of( ':' );
                
                std::string name = String::trim( header.substr( 0, index ) );
                
                std::string value = String::trim( header.substr( index + 1 ) );
                
                request.set_header( name, value );
            }
        }

        Request ServiceImpl::build_request( shared_ptr< tcp::socket >& socket )
        {
            const char* CRLF = "\r\n";
            
            error_code status;
            
            asio::streambuf buffer;
            
            asio::read_until( *socket, buffer, CRLF, status );
            
            istream stream( &buffer );
            
            Request request;
            
            build_request_method( stream, request );
            
            build_request_path( stream, request, socket );
            
            build_request_version( stream, request );
            
            buffer.consume( 2 ); //remove trailing CRLF
            
            build_request_headers( stream, request );
            
            return request;
        }

        void ServiceImpl::router( shared_ptr< tcp::socket > socket, const error_code& error )
        {
            if ( not error )
            {
                Request request = build_request( socket ); //Request::build( socket );
                
                bool authenticated = authentication_handler( request ); //put this on resource?
                
                if ( authenticated )
                {
                    std::cout << "authenticated!" << std::endl;
                    
                    std::cout << "Path: " << request.get_uri( ).get_path( ) << std::endl;
                    
                    const auto& resource = std::find_if( m_resources.begin( ), m_resources.end( ), ResourceMatcher( request ) );
                    
                    std::string method = request.get_method( ); //Why is this not Method? do curl with a fake Method is gets all the way to get_method_handler :s It should fail at build_request( socket );
                        
                    auto handle = resource->get_method_handler( method );
                        
                    Response response = handle( request );
                }
                else
                {
                    //not authorized!
                }
            }
            else
            {
                //internal server error!
            }

            //send back response!
            //response
            
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
            return m_port != rhs.m_port;
        }

        ServiceImpl& ServiceImpl::operator =( const ServiceImpl& rhs )
        {
            m_port = rhs.m_port;

            m_resources = rhs.m_resources;

            return *this;
        }
    }
}
