/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <utility>
#include <ciso646>
#include <algorithm>

//Project Includes
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/response.hpp"
#include "corvusoft/restbed/detail/response_impl.hpp"

//External Includes

//System Namespaces
using std::map;
using std::pair;
using std::string;
using std::function;
using std::multimap;
using std::unique_ptr;
using std::shared_ptr;
using std::invalid_argument;

//Project Namespaces
using restbed::Common;
using restbed::Request;
using restbed::detail::ResponseImpl;

//External Namespaces

namespace restbed
{
    Response::Response( void ) : m_pimpl( new ResponseImpl )
    {
        return;
    }
    
    Response::~Response( void )
    {
        return;
    }
    
    bool Response::has_header( const string& name ) const
    {
        return Common::has_parameter( name, m_pimpl->m_headers );
    }
    
    Bytes Response::get_body( void ) const
    {
        return m_pimpl->m_body;
    }
    
    double Response::get_version( void ) const
    {
        return m_pimpl->m_version;
    }
    
    int Response::get_status_code( void ) const
    {
        return m_pimpl->m_status_code;
    }
    
    string Response::get_protocol( void ) const
    {
        return m_pimpl->m_protocol;
    }
    
    string Response::get_status_message( void ) const
    {
        return m_pimpl->m_status_message;
    }
    
    void Response::get_body( string& body, const function< string ( const Bytes& ) >& transform ) const
    {
        body = ( transform == nullptr ) ? string( m_pimpl->m_body.begin( ), m_pimpl->m_body.end( ) ) : transform( m_pimpl->m_body );
    }
    
    string Response::get_header( const string& name, const string& default_value ) const
    {
        if ( name.empty( ) )
        {
            return default_value;
        }
        
        const auto headers = Common::get_parameters( name, m_pimpl->m_headers );
        return ( headers.empty( ) ) ? default_value : headers.begin( )->second;
    }
    
    string Response::get_header( const string& name, const function< string ( const string& ) >& transform ) const
    {
        if ( name.empty( ) )
        {
            return String::empty;
        }
        
        const auto headers = Common::get_parameters( name, m_pimpl->m_headers );
        const auto value = ( headers.empty( ) ) ? String::empty : headers.begin( )->second;
        
        return Common::transform( value, transform );
    }
    
    multimap< string, string > Response::get_headers( const string& name ) const
    {
        return Common::get_parameters( name, m_pimpl->m_headers );
    }
    
    void Response::set_body( const Bytes& value )
    {
        m_pimpl->m_body = value;
    }
    
    void Response::set_body( const string& value )
    {
        m_pimpl->m_body = String::to_bytes( value );
    }
    
    void Response::set_version( const double value )
    {
        m_pimpl->m_version = value;
    }
    
    void Response::set_status_code( const int value )
    {
        m_pimpl->m_status_code = value;
    }
    
    void Response::set_protocol( const string& value )
    {
        m_pimpl->m_protocol = value;
    }
    
    void Response::set_status_message( const string& value )
    {
        m_pimpl->m_status_message = value;
    }
    
    void Response::add_header( const string& name, const string& value )
    {
        m_pimpl->m_headers.insert( make_pair( name, value ) );
    }

    void Response::set_header( const string& name, const string& value )
    {
        m_pimpl->m_headers.erase( name );
        m_pimpl->m_headers.insert( make_pair( name, value ) );
    }

    void Response::set_headers( const multimap< string, string >& values )
    {
        m_pimpl->m_headers = values;
    }
}
