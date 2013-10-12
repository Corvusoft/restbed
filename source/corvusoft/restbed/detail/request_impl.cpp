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
#include <sstream>

//Project Includes
#include "restbed/status_code.h"
#include "restbed/detail/helpers/map.h"
#include "restbed/detail/request_impl.h"
#include "restbed/detail/helpers/string.h"
#include "restbed/detail/helpers/istream.h"

//External Includes

//System Namespaces
using std::map;
using std::stod;
using std::string;
using std::istream;
using std::istreambuf_iterator;

//Project Namespaces
using restbed::detail::RequestImpl;
using restbed::detail::helpers::Map;
using restbed::detail::helpers::String;
using restbed::detail::helpers::IStream;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        RequestImpl::RequestImpl( void ) : m_version( 1.1 ),
                                           m_path( String::empty ),
                                           m_body( String::empty ),
                                           m_method( String::empty ),
                                           m_headers( ),
                                           m_path_parameters( ),
                                           m_query_parameters( )
        {
            //n/a
        }
        
        RequestImpl::RequestImpl( const RequestImpl& original ) : m_version( original.m_version ),
                                                                  m_path( original.m_path ),
                                                                  m_body( original.m_body ),
                                                                  m_method( original.m_method ),
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

        bool RequestImpl::has_header( const string& name ) const
        {
            return ( Map::find_key_ignoring_case( name, m_headers ) not_eq m_headers.end( ) );
        }

        bool RequestImpl::has_path_parameter( const string& name ) const
        {
            return ( Map::find_key_ignoring_case( name, m_path_parameters ) not_eq m_path_parameters.end( ) );
        }

        bool RequestImpl::has_query_parameter( const string& name ) const
        {
            return ( Map::find_key_ignoring_case( name, m_query_parameters ) not_eq m_query_parameters.end( ) );
        }
        
        double RequestImpl::get_version( void ) const
        {
            return m_version;
        }

        string RequestImpl::get_path( void ) const
        {
            return m_path;
        }
        
        string RequestImpl::get_body( void ) const
        {
            return m_body;
        }

        string RequestImpl::get_method( void ) const
        {
            return m_method;
        }
        
        string RequestImpl::get_header( const string& name ) const
        {
            string value = String::empty;
            
            if ( has_header( name ) )
            {
                const auto iterator = Map::find_key_ignoring_case( name, m_headers );

                value = iterator->second;
            }

            return value;
        }
        
        map< string, string > RequestImpl::get_headers( void ) const
        {
            return m_headers;
        }
        
        string RequestImpl::get_query_parameter( const string& name ) const
        {
            const auto iterator = Map::find_key_ignoring_case( name, m_query_parameters );
            
            return iterator->second;
        }
        
        map< string, string > RequestImpl::get_query_parameters( void ) const
        {
            return m_query_parameters;
        }
        
        string RequestImpl::get_path_parameter( const string& name ) const
        {
            const auto iterator = Map::find_key_ignoring_case( name, m_path_parameters );
            
            return iterator->second;
        }
        
        map< string, string > RequestImpl::get_path_parameters( void ) const
        {
            return m_path_parameters;
        }

        void RequestImpl::set_version( const double value )
        {
            if ( value not_eq 1.0 and value not_eq 1.1 )
            {
                throw StatusCode::HTTP_VERSION_NOT_SUPPORTED;
            }

            m_version = value;
        }
        
        void RequestImpl::set_path( const string& value )
        {
            m_path = value;
        }
        
        void RequestImpl::set_body( const string& value )
        {
            m_body = value;
        }

        void RequestImpl::set_method( const string& value )
        {
            m_method = value;
        }
        
        void RequestImpl::set_headers( const map< string, string >& value )
        {
            m_headers = value;
        }

        void RequestImpl::set_path_parameter( const string& name, const string& value )
        {
            m_path_parameters[ name ] = value;
        }
        
        void RequestImpl::set_query_parameters( const map< string, string >& value )
        {
            m_query_parameters = value;
        }

        bool RequestImpl::operator <( const RequestImpl& rhs ) const
        {
            return m_path < rhs.m_path;
        }
        
        bool RequestImpl::operator >( const RequestImpl& rhs ) const
        {
            return m_path > rhs.m_path;
        }
        
        bool RequestImpl::operator ==( const RequestImpl& rhs ) const
        {
            return m_path == rhs.m_path;
        }
        
        bool RequestImpl::operator !=( const RequestImpl& rhs ) const
        {
            return m_path not_eq rhs.m_path;
        }
        
        RequestImpl& RequestImpl::operator =( const RequestImpl& rhs )
        {
            m_path = rhs.m_path;
                                
            m_method = rhs.m_method;
            
            m_version = rhs.m_version;
            
            m_headers = rhs.m_headers;
            
            m_path_parameters = rhs.m_path_parameters;
            
            m_query_parameters = rhs.m_query_parameters;

            return *this;
        }
    }
}
