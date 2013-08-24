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

//Project Includes
#include "restbed/method.h"
#include "restbed/request.h"
#include "restbed/response.h"
#include "restbed/detail/resource_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::string;
using std::function;

//Project Namespaces

//External Namespaces

namespace restbed
{
    namespace detail
    {
        ResourceImpl::ResourceImpl( void ) : m_path( ".*" ),
                                             m_content_type( ".*" ),
                                             m_method_handles( )

        {
            setup( );
        }
        
        ResourceImpl::ResourceImpl( const ResourceImpl& original ) : m_path( original.m_path ),
                                                                     m_content_type( original.m_content_type ),
                                                                     m_method_handles( original.m_method_handles )
        {
            //n/a
        }
        
        ResourceImpl::~ResourceImpl( void )
        {
            //n/a
        }

        string ResourceImpl::get_path( void ) const
        {
            return m_path;
        }
        
        string ResourceImpl::get_content_type( void ) const
        {
            return m_content_type;
        }

        function< Response ( Request& ) > ResourceImpl::get_method_handler( const Method& method ) const
        {
            return m_method_handles.at( method.to_string( ) );
        }

        void ResourceImpl::set_path( const string& value )
        {
            m_path = value;
        }

        void ResourceImpl::set_content_type( const string& value )
        {
            m_content_type = value;
        }

        void ResourceImpl::set_method_handler( const Method& method, const function< Response ( Request& ) >& callback )
        {
            m_method_handles[ method.to_string( ) ] = callback;
        }
        
        bool ResourceImpl::operator <( const ResourceImpl& rhs ) const
        {
            return m_path < rhs.m_path;
        }
        
        bool ResourceImpl::operator >( const ResourceImpl& rhs ) const
        {
            return m_path > rhs.m_path;
        }
        
        bool ResourceImpl::operator ==( const ResourceImpl& rhs ) const
        {
            return m_path == rhs.m_path;
        }
        
        bool ResourceImpl::operator !=( const ResourceImpl& rhs ) const
        {
            return m_path not_eq rhs.m_path;
        }

        ResourceImpl& ResourceImpl::operator =( const ResourceImpl& rhs )
        {
            m_path = rhs.m_path;

            m_content_type = rhs.m_content_type;

            m_method_handles = rhs.m_method_handles;

            return *this;
        }

        void ResourceImpl::setup( void )
        {
            set_method_handler( "GET",     &ResourceImpl::default_handler );
            set_method_handler( "PUT",     &ResourceImpl::default_handler );
            set_method_handler( "POST",    &ResourceImpl::default_handler );
            set_method_handler( "HEAD",    &ResourceImpl::default_handler );
            set_method_handler( "DELETE",  &ResourceImpl::default_handler );
            set_method_handler( "CONNECT", &ResourceImpl::default_handler );
            set_method_handler( "TRACE",   &ResourceImpl::default_trace_handler );
            set_method_handler( "OPTIONS", &ResourceImpl::default_options_handler );
        }

        Response ResourceImpl::default_handler( const Request& request )
        {
            Response response;

            //response.set_status(Status::NOT_FOUND);
            std::cout << "default handler 404!" << std::endl;

            return response;
        }
        
        Response ResourceImpl::default_trace_handler( const Request& request )
        {
            Response response;
            
            std::cout << "default trace handler" << std::endl;
            
            return response;
        }

        Response ResourceImpl::default_options_handler( const Request& request )
        {
            //default OPTIONS method handler.
            //HTTP/1.1 200 OK
            //Date: …
            //Allow: OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE
            //Content-Length: 0
            Response response;
            
            std::cout << "default options handler" << std::endl;
            
            return response;
        }
    }
}
