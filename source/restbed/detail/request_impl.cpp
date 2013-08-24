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
#include "restbed/string.h"
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
    namespace detail
    {
        RequestImpl::RequestImpl( void ) : m_uri( String::empty ),
                                           m_method( String::empty ),
                                           m_version( String::empty ),
                                           m_headers( ),
                                           m_path_parameters( ),
                                           m_query_parameters( )
        {
            //n/a
        }
        
        RequestImpl::RequestImpl( const RequestImpl& original ) : m_uri( original.m_uri ),
                                                                  m_method( original.m_method ),
                                                                  m_version( original.m_version ),
                                                                  m_headers( original.m_headers ),
                                                                  m_path_parameters( original.m_path_parameters ),
                                                                  m_query_parameters( original.m_query_parameters )
        {
            //n/a
        }
        
        RequestImpl::~RequestImpl( void )
        {
            //n/a
        }
        
        Uri RequestImpl::get_uri( void ) const
        {
            return m_uri;
        }
        
        string RequestImpl::get_method( void ) const
        {
            return m_method;
        }
        
        string RequestImpl::get_version( void ) const
        {
            return m_version;
        }
        
        string RequestImpl::get_header( const string& name ) const
        {
            return m_headers.at( name );
        }
        
        map< string, string > RequestImpl::get_headers( void ) const
        {
            return m_headers;
        }
        
        string RequestImpl::get_query_parameter( const string& name ) const
        {
            return m_query_parameters.at( name );
        }
        
        map< string, string > RequestImpl::get_query_parameters( void ) const
        {
            return m_query_parameters;
        }
        
        string RequestImpl::get_path_parameter( const string& name ) const
        {
            return m_path_parameters.at( name );
        }
        
        map< string, string > RequestImpl::get_path_parameters( void ) const
        {
            return m_path_parameters;
        }
        
        void RequestImpl::set_uri( const Uri& value )
        {
            m_uri = value.to_string( );
        }
        
        void RequestImpl::set_method( const string& value )
        {
            m_method = value;
        }
        
        void RequestImpl::set_version( const string& value )
        {
            m_version = value;
        }
        
        void RequestImpl::set_header( const string& name, const string& value )
        {
            m_headers[ name ] = value;
        }
        
        void RequestImpl::set_path_parameter( const string& name, const string& value )
        {
            m_path_parameters[ name ] = value;
        }
        
        void RequestImpl::set_query_parameter( const string& name, const string& value )
        {
            m_query_parameters[ name ] = value;
        }
        
        bool RequestImpl::operator <( const RequestImpl& rhs ) const
        {
            return m_uri < rhs.m_uri;
        }
        
        bool RequestImpl::operator >( const RequestImpl& rhs ) const
        {
            return m_uri > rhs.m_uri;
        }
        
        bool RequestImpl::operator ==( const RequestImpl& rhs ) const
        {
            return m_uri == rhs.m_uri;
        }
        
        bool RequestImpl::operator !=( const RequestImpl& rhs ) const
        {
            return m_uri not_eq rhs.m_uri;
        }
        
        RequestImpl& RequestImpl::operator =( const RequestImpl& rhs )
        {
            m_uri = rhs.m_uri;
                                
            m_method = rhs.m_method;
            
            m_version = rhs.m_version;
            
            m_headers = rhs.m_headers;
            
            m_path_parameters = rhs.m_path_parameters;
            
            m_query_parameters = rhs.m_query_parameters;

            return *this;
        }
    }
}
