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
#include <array>
#include <algorithm>

//Project Includes
#include "restbed/status_code.h"
#include "restbed/detail/method_impl.h"
#include "restbed/detail/helpers/string.h"
 
//External Includes

//System Namespaces
using std::find;
using std::array;
using std::string;
using std::invalid_argument;

//Project Namespaces
using restbed::detail::helpers::String;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        MethodImpl::MethodImpl( const char* value ) : m_value( String::empty )
        {
            setup( string( value ) );
        }

        MethodImpl::MethodImpl( const string& value ) : m_value( String::empty )
        {
            setup( value );
        }
        
        MethodImpl::MethodImpl( const MethodImpl& original ) : m_value( original.m_value )
        {
            //n/a
        }
        
        MethodImpl::~MethodImpl( void )
        {
            //n/a
        }

        string MethodImpl::to_string( void ) const
        {
            return m_value;
        }

        bool MethodImpl::operator <( const MethodImpl& rhs ) const
        {
            return m_value < rhs.m_value;
        }
        
        bool MethodImpl::operator >( const MethodImpl& rhs ) const
        {
            return m_value > rhs.m_value;
        }
        
        bool MethodImpl::operator ==( const MethodImpl& rhs ) const
        {
            return m_value == rhs.m_value;
        }
        
        bool MethodImpl::operator !=( const MethodImpl& rhs ) const
        {
            return m_value not_eq rhs.m_value;
        }

        MethodImpl& MethodImpl::operator =( const MethodImpl& rhs )
        {
            m_value = rhs.m_value;

            return *this;
        }

        void MethodImpl::setup( const string& value )
        {
            const static array< string, 8 > methods = {{
                "GET",
                "PUT",
                "POST",            
                "HEAD",
                "TRACE",
                "DELETE",
                "CONNECT",            
                "OPTIONS"
            }};
            
            string method = String::uppercase( value );

            auto iterator = find( methods.begin( ), methods.end( ), method );

            if ( iterator == methods.end( ) )
            {
                throw StatusCode::METHOD_NOT_ALLOWED;
            }

            m_value = method;
        }
    }
}
