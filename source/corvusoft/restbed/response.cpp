/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
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
using std::shared_ptr;
using std::invalid_argument;

//Project Namespaces
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
        delete m_pimpl;
    }
    
    bool Response::has_header( const string& name ) const
    {
        const auto key = String::lowercase( name );
        
        auto iterator = find_if( m_pimpl->m_headers.begin( ), m_pimpl->m_headers.end( ), [ &key ]( const pair< string, string >& value )
        {
            return ( key == String::lowercase( value.first ) );
        } );
        
        return iterator not_eq m_pimpl->m_headers.end( );
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
    
    const shared_ptr< const Request > Response::get_request( void ) const
    {
        return m_pimpl->m_request.lock( );
    }
    
    void Response::get_body( string& body, const function< string ( const Bytes& ) >& transform ) const
    {
        body = ( transform == nullptr ) ? string( m_pimpl->m_body.begin( ), m_pimpl->m_body.end( ) ) : transform( m_pimpl->m_body );
    }
    
    void Response::get_header( const string& name, int& value, const int default_value ) const
    {
        try
        {
            value = stoi( get_header( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Response::get_header( const string& name, long& value, const long default_value ) const
    {
        try
        {
            value = stol( get_header( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Response::get_header( const string& name, float& value, const float default_value ) const
    {
        try
        {
            value = stof( get_header( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Response::get_header( const string& name, double& value, const double default_value ) const
    {
        try
        {
            value = stod( get_header( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Response::get_header( const string& name, long long& value, const long long default_value ) const
    {
        try
        {
            value = stoll( get_header( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Response::get_header( const string& name, unsigned int& value, const unsigned int default_value ) const
    {
        try
        {
            value = stoul( get_header( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Response::get_header( const string& name, unsigned long& value, const unsigned long default_value ) const
    {
        try
        {
            value = stoul( get_header( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Response::get_header( const string& name, unsigned long long& value, const unsigned long long default_value ) const
    {
        try
        {
            value = stoull( get_header( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    multimap< string, string > Response::get_headers( const string& name ) const
    {
        if ( name.empty( ) )
        {
            return m_pimpl->m_headers;
        }
        
        decltype( m_pimpl->m_headers ) headers;
        const auto key = String::lowercase( name );
        
        for ( const auto& header : m_pimpl->m_headers )
        {
            if ( key == String::lowercase( header.first ) )
            {
                headers.insert( header );
            }
        }
        
        return headers;
    }
    
    string Response::get_header( const string& name, const string& default_value ) const
    {
        const auto key = String::lowercase( name );
        const auto iterator = find_if( m_pimpl->m_headers.begin( ), m_pimpl->m_headers.end( ), [ &key ]( const pair< string, string >& value )
        {
            return ( key == String::lowercase( value.first ) );
        } );
        
        return ( iterator == m_pimpl->m_headers.end( ) ) ? default_value : iterator->second;
    }
    
    string Response::get_header( const string& name, const function< string ( const string& ) >& transform ) const
    {
        const string header = get_header( name );
        return ( transform == nullptr ) ? header : transform( header );
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
    
    void Response::set_header( const string& name, const string& value )
    {
        m_pimpl->m_headers.insert( make_pair( name, value ) );
    }
    
    void Response::set_headers( const multimap< string, string >& values )
    {
        m_pimpl->m_headers = values;
    }
}
