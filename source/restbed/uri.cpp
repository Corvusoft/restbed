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
#include "restbed/detail/uri_impl.h"

//External Includes

//System Namespaces
using std::string;
using std::unique_ptr;

//Project Namespaces
using restbed::detail::UriImpl;

//External Namespaces

namespace restbed
{
    Uri::Uri( const string& value ) : m_pimpl( new UriImpl )
    {
        m_pimpl->set_uri( value );
    }
    
    Uri::Uri( const Uri& original ) : m_pimpl( new UriImpl( *original.m_pimpl ) )
    {
        //n/a
    }
    
    Uri::~Uri( void )
    {
        //n/a
    }
    
    string Uri::to_string( void ) const
    {
        return m_pimpl->to_string( );
    }
    
    string Uri::to_native_path( void ) const
    {
        return m_pimpl->to_native_path( );
    }
    
    Uri Uri::parse( const string& value )
    {
        Uri uri;
        
        uri.m_pimpl->set_uri( value );
        
        return uri;
    }
    
    string Uri::decode( const Bytes& value )
    {
        return UriImpl::decode( value );
    }
    
    string Uri::decode( const string& value )
    {
        return UriImpl::decode( value );
    }
    
    string Uri::encode( const Bytes& value )
    {
        return UriImpl::encode( value );
    }
    
    string Uri::encode( const string& value )
    {
        return UriImpl::encode( value );
    }
    
    int Uri::get_port( void ) const
    {
        return m_pimpl->get_port( );
    }
    
    string Uri::get_path( void ) const
    {
        return m_pimpl->get_path( );
    }
    
    string Uri::get_query( void ) const
    {
        return m_pimpl->get_query( );
    }
    
    string Uri::get_scheme( void ) const
    {
        return m_pimpl->get_scheme( );
    }
    
    string Uri::get_fragment( void ) const
    {
        return m_pimpl->get_fragment( );
    }
    
    string Uri::get_username( void ) const
    {
        return m_pimpl->get_username( );
    }
    
    string Uri::get_password( void ) const
    {
        return m_pimpl->get_password( );
    }
    
    string Uri::get_authority( void ) const
    {
        return m_pimpl->get_authority( );
    }
    
    Uri& Uri::operator =( const Uri& rhs )
    {
        *m_pimpl = *rhs.m_pimpl;
        
        return *this;
    }
    
    bool Uri::operator <( const Uri& rhs ) const
    {
        return ( *m_pimpl < *rhs.m_pimpl );
    }
    
    bool Uri::operator >( const Uri& rhs ) const
    {
        return ( *m_pimpl > *rhs.m_pimpl );
    }
    
    bool Uri::operator ==( const Uri& rhs ) const
    {
        return ( *m_pimpl == *rhs.m_pimpl );
    }
    
    bool Uri::operator !=( const Uri& rhs ) const
    {
        return ( *m_pimpl not_eq * rhs.m_pimpl );
    }
    
    Uri::Uri( void ) : m_pimpl( new UriImpl )
    {
        //n/a
    }
}
