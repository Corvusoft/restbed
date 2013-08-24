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
        ResponseImpl::ResponseImpl( void ) : m_data( String::empty ),
                                             m_headers( )
        {
            //n/a
        }
        
        ResponseImpl::ResponseImpl( const ResponseImpl& original ) : m_data( original.m_data ),
                                                                     m_headers( original.m_headers )
        {
            //n/a
        }
        
        ResponseImpl::~ResponseImpl( void )
        {
            //n/a
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
