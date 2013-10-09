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
#include "restbed/status_code.h"
#include "restbed/detail/resource_impl.h"
#include "restbed/detail/helpers/string.h"
#include "restbed/detail/helpers/functional.h"

//External Includes

//System Namespaces
using std::map;
using std::bind;
using std::string;
using std::function;
using std::placeholders::_1;

//Project Namespaces
using restbed::detail::helpers::String;
using restbed::detail::helpers::Functional;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        ResourceImpl::ResourceImpl( void ) : m_path( String::empty ),
                                             m_header_filters( ),
                                             m_method_handlers( )
        {
            setup( );
        }
        
        ResourceImpl::ResourceImpl( const ResourceImpl& original ) : m_path( original.m_path ),
                                                                     m_header_filters( original.m_header_filters ),
                                                                     m_method_handlers( original.m_method_handlers )
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
        
        string ResourceImpl::get_header_filter( const string& name ) const
        {
            string key = String::uppercase( name );

            return m_header_filters.at( key );
        }

        map< string, string > ResourceImpl::get_header_filters( void ) const
        {
            return m_header_filters;
        }

        function< Response ( const Request& ) > ResourceImpl::get_method_handler( const Method& method ) const
        {
            return m_method_handlers.at( method.to_string( ) );
        }

        void ResourceImpl::set_path( const string& value )
        {
            m_path = value;
        }

        void ResourceImpl::set_header_filter( const string& name, const string& value )
        {
            string key = String::uppercase(  name );

            m_header_filters[ key ] = value;
        }

        void ResourceImpl::set_method_handler( const Method& verb, const function< Response ( const Request& ) >& callback )
        {
            string key = String::uppercase(  verb.to_string( ) );

            m_method_handlers[ key ] = callback;
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

            m_header_filters = rhs.m_header_filters;

            m_method_handlers = rhs.m_method_handlers;

            return *this;
        }

        void ResourceImpl::setup( void )
        {
            set_method_handler( "GET", &ResourceImpl::default_handler );
            set_method_handler( "PUT", &ResourceImpl::default_handler );
            set_method_handler( "POST", &ResourceImpl::default_handler );
            set_method_handler( "HEAD", &ResourceImpl::default_handler );
            set_method_handler( "DELETE", &ResourceImpl::default_handler );
            set_method_handler( "CONNECT", &ResourceImpl::default_handler );
            set_method_handler( "TRACE", &ResourceImpl::default_trace_handler );
            set_method_handler( "OPTIONS", bind( &ResourceImpl::default_options_handler, this, _1 ) );
        }

        string ResourceImpl::generate_allow_header_value( void )
        {
            string value = String::empty;

            for ( auto& handler : m_method_handlers )
            {
                Functional::address_type callback_address = Functional::get_address( handler.second );
                Functional::address_type default_address = ( Functional::address_type ) ResourceImpl::default_handler;

                if ( callback_address not_eq default_address )
                {
                    value += String::format( "%s, ", handler.first.data( ) );
                }
            }

            if ( not value.empty( ) )
            {
                value = value.substr( 0, value.length( ) - 2 );
            }

            return value;   
        }

        string ResourceImpl::rebuild_path( const Request& request )
        {
            string query = "?";

            for ( auto parameter : request.get_query_parameters( ) )
            {
                query += String::format( "%s=%s&", parameter.first.data( ), parameter.second.data( ) );
            }

            query = String::trim( query, "&" );

            string path = request.get_path( );
            path += ( query.length( ) > 1 ) ? query : String::empty;

            return path;
        }

        string ResourceImpl::rebuild_headers( const Request& request )
        {
            string headers = String::empty;

            for ( auto header : request.get_headers( ) )
            {
                headers += String::format( "%s: %s\r\n", header.first.data( ), header.second.data( ) );
            }

            return headers;
        }

        Response ResourceImpl::default_options_handler( const Request& )
        {
            Response response;
            response.set_status_code( StatusCode::OK );
            response.set_header( "Allow", generate_allow_header_value( ) );
            
            return response;
        }

        Response ResourceImpl::default_handler( const Request& )
        {
            Response response;
            response.set_status_code( StatusCode::NOT_IMPLEMENTED );

            return response;
        }
        
        Response ResourceImpl::default_trace_handler( const Request& request )
        {
            string path = rebuild_path( request );

            string headers = rebuild_headers( request );

            string body = String::format( "TRACE %s HTTP/1.1\r\n%s", path.data( ), headers.data( ) );

            Response response;
            response.set_body( body );
            response.set_status_code( StatusCode::OK );
            response.set_header( "Content-Type", "message/http" );
            
            return response;
        }
    }
}
