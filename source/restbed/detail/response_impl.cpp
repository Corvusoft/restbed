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
#include "restbed/string.h"
#include "restbed/status_code.h"
#include "restbed/detail/response_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::string;

//Project Namespaces

//External Namespaces

namespace restbed
{
    namespace detail
    {
        ResponseImpl::ResponseImpl( void ) : m_status_code( StatusCode::OK ),
                                             m_data( String::empty ),
                                             m_headers( )
        {
            //n/a
        }
        
        ResponseImpl::ResponseImpl( const ResponseImpl& original ) : m_status_code( original.m_status_code ),
                                                                     m_data( original.m_data ),
                                                                     m_headers( original.m_headers )
        {
            //n/a
        }
        
        ResponseImpl::~ResponseImpl( void )
        {
            //n/a
        }

        string ResponseImpl::to_string( void ) const
        {
            string response = "HTTP/1.1 200 OK\r\n";
            //general headers //get_general_headers
            response += "Date: Thu, 20 May 2003 21:12:58 GMT\r\n";
            response += "Connection: close\r\n";
            //response headers //get_response_headers
            response += "Server: Restbed/1.0.23\r\n";
            response += "Accept-Ranges: bytes\r\n";
            //entity headers //get_entity_headers
            response += "Content-Type: text/html\r\n";
            response += "Content-Length: 12\r\n";
            response += "Last-Modified: Tue, 18 May 2004 10:14:49 GMT\r\n\r\n";
            //message body //get_content
            response += "1234567890jk";

            //date for free
            //content length
            //connection: close
            //also make sure the ':' is added automatically for all headers!

            return response;
        }
         
        int ResponseImpl::get_status_code( void ) const
        {
            return m_status_code;
        }

        string ResponseImpl::get_data( void ) const
        {
            return m_data;
        }

        string ResponseImpl::get_header( const string& name ) const
        {
            return m_headers.at( name );
        }

        map< string, string > ResponseImpl::get_headers( void ) const
        {
            return m_headers;
        }
        
        void ResponseImpl::set_status_code( const int value )
        {
            m_status_code = value;
        }

        void ResponseImpl::set_data( const string& value )
        {
            m_data = value;
        }

        void ResponseImpl::set_header( const string& name, const string& value )
        {
            m_headers[ name ] = value;
        }

        void ResponseImpl::set_headers( const map< std::string, string >& values )
        {
            m_headers = values;
        }

        bool ResponseImpl::operator <( const ResponseImpl& rhs ) const
        {
            return m_data < rhs.m_data;
        }
        
        bool ResponseImpl::operator >( const ResponseImpl& rhs ) const
        {
            return m_data > rhs.m_data;
        }
        
        bool ResponseImpl::operator ==( const ResponseImpl& rhs ) const
        {
            return m_data == rhs.m_data and m_headers == rhs.m_headers;
        }
        
        bool ResponseImpl::operator !=( const ResponseImpl& rhs ) const
        {
            return m_data not_eq rhs.m_data or m_headers not_eq rhs.m_headers;
        }
        
        ResponseImpl& ResponseImpl::operator =( const ResponseImpl& rhs )
        {
            m_data = rhs.m_data;

            m_headers = rhs.m_headers;

            return *this;
        }
    }
}
