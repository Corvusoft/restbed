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
#include "restbed/response.h"
#include "restbed/detail/response_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::string;

//Project Namespaces
using restbed::detail::ResponseImpl;

//External Namespaces

namespace restbed
{
    Response::Response( void ) : m_pimpl( new ResponseImpl )
    {
        //n/a
    }
    
    Response::Response( const Response& original ) : m_pimpl( new ResponseImpl( *original.m_pimpl ) )
    {
        //n/a
    }
    
    Response::~Response( void )
    {
        //n/a
    }
            
    string Response::get_data( void ) const
    {
        return m_pimpl->get_data( );
    }

    string Response::get_header( const string& name ) const
    {
        return m_pimpl->get_header( name );
    }

    map< string, string > Response::get_headers( void ) const
    {
        return m_pimpl->get_headers( );
    }
    
    void Response::set_data( const string& value )
    {
        m_pimpl->set_data( value );
    }

    void Response::set_header( const string& name, const string& value )
    {
        m_pimpl->set_header( name, value );
    }

    void Response::set_headers( const map< std::string, string >& values )
    {
        m_pimpl->set_headers( values );
    }

    Response& Response::operator =( const Response& rhs )
    {
        *m_pimpl = *rhs.m_pimpl;

        return *this;
    }

    bool Response::operator <( const Response& rhs ) const
    {
        return *m_pimpl < *rhs.m_pimpl;
    }
    
    bool Response::operator >( const Response& rhs ) const
    {
        return *m_pimpl > *rhs.m_pimpl;
    }
    
    bool Response::operator ==( const Response& rhs ) const
    {
        return *m_pimpl == *rhs.m_pimpl;
    }
    
    bool Response::operator !=( const Response& rhs ) const
    {
        return *m_pimpl != *rhs.m_pimpl;
    }
}
