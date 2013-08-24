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
#include "restbed/uri.h"
#include "restbed/request.h"
#include "restbed/detail/request_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::string;

//Project Namespaces
using restbed::detail::RequestImpl;

//External Namespaces

namespace restbed
{
    Request::Request( void ) : m_pimpl( new RequestImpl )
    {
        //n/a
    }
    
    Request::Request( const Request& original ) : m_pimpl( new RequestImpl( *original.m_pimpl ) )
    {
        //n/a
    }
    
    Request::~Request( void )
    {
        //n/a
    }

    Uri Request::get_uri( void ) const
    {
        return m_pimpl->get_uri( );
    }
    
    string Request::get_method( void ) const
    {
        return m_pimpl->get_method( );
    }
    
    string Request::get_version( void ) const
    {
        return m_pimpl->get_version( );
    }
    
    string Request::get_header( const string& name ) const
    {
        return m_pimpl->get_header( name );
    }
    
    map< string, string > Request::get_headers( void ) const
    {
        return m_pimpl->get_headers( );
    }
    
    string Request::get_query_parameter( const string& name ) const
    {
        return m_pimpl->get_query_parameter( name );
    }
    
    map< string, string > Request::get_query_parameters( void ) const
    {
        return m_pimpl->get_query_parameters( );
    }
    
    string Request::get_path_parameter( const string& name ) const
    {
        return m_pimpl->get_path_parameter( name );
    }
    
    map< string, string > Request::get_path_parameters( void ) const
    {
        return m_pimpl->get_path_parameters( );
    }

    void Request::set_uri( const Uri& value )
    {
        m_pimpl->set_uri( value );
    }
    
    void Request::set_method( const string& value )
    {
        m_pimpl->set_method( value );
    }
    
    void Request::set_version( const string& value )
    {
        m_pimpl->set_version( value );
    }
    
    void Request::set_header( const string& name, const string& value )
    {
        m_pimpl->set_header( name, value );
    }
    
    void Request::set_path_parameter( const string& name, const string& value )
    {
        m_pimpl->set_path_parameter( name, value );
    }
    
    void Request::set_query_parameter( const string& name, const string& value )
    {
        m_pimpl->set_query_parameter( name, value );
    }

    Request& Request::operator =( const Request& rhs )
    {
        *m_pimpl = *rhs.m_pimpl;

        return *this;
    }

    bool Request::operator <( const Request& rhs ) const
    {
        return *m_pimpl < *rhs.m_pimpl;
    }
    
    bool Request::operator >( const Request& rhs ) const
    {
        return *m_pimpl > *rhs.m_pimpl;
    }
    
    bool Request::operator ==( const Request& rhs ) const
    {
        return *m_pimpl == *rhs.m_pimpl;
    }
    
    bool Request::operator !=( const Request& rhs ) const
    {
        return *m_pimpl != *rhs.m_pimpl;
    }
}
