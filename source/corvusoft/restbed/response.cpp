/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <ciso646>

//Project Includes
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/response.hpp"
#include "corvusoft/restbed/detail/response_impl.hpp"

//External Includes

//System Namespaces
using std::string;
using std::multimap;
using std::make_pair;

//Project Namespaces
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
    
    Bytes Response::to_bytes( void ) const
    {
        auto data = String::format( "%s/%.1f %i %s\r\n",
                                    m_pimpl->m_protocol.data( ),
                                    m_pimpl->m_version,
                                    m_pimpl->m_status_code,
                                    m_pimpl->m_status_message.data( ) );
                                    
        if ( not m_pimpl->m_headers.empty( ) )
        {
            const auto headers = String::join( m_pimpl->m_headers, ": ", "\r\n" );
            data += headers + "\r\n";
        }
        
        data += "\r\n";
        
        Bytes bytes = String::to_bytes( data );
        
        if ( not m_pimpl->m_body.empty( ) )
        {
            bytes.insert( bytes.end( ), m_pimpl->m_body.begin( ), m_pimpl->m_body.end( ) );
        }
        
        return bytes;
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
    
    multimap< string, string > Response::get_headers( void ) const
    {
        return m_pimpl->m_headers;
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
