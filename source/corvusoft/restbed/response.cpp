/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/response.hpp"
#include "corvusoft/restbed/detail/response_impl.hpp"

//External Includes
#include <corvusoft/framework/string>

//System Namespaces
using std::string;
using std::multimap;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using restbed::detail::ResponseImpl;

//External Namespaces
using framework::Bytes;
using framework::String;

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
    
    Bytes Response::to_bytes( void ) const
    {
        return m_pimpl->to_bytes( );
    }
    
    double Response::get_version( void ) const
    {
        return m_pimpl->get_version( );
    }
    
    int Response::get_status_code( void ) const
    {
        return m_pimpl->get_status_code( );
    }
    
    Bytes Response::get_body( void ) const
    {
        return m_pimpl->get_body( );
    }
    
    string Response::get_protocol( void ) const
    {
        return m_pimpl->get_protocol( );
    }
    
    string Response::get_status_message( void ) const
    {
        return m_pimpl->get_status_message( );
    }
    
    multimap< string, string > Response::get_headers( void ) const
    {
        return m_pimpl->get_headers( );
    }
    
    void Response::set_version( const double value )
    {
        m_pimpl->set_version( value );
    }
    
    void Response::set_protocol( const string& value )
    {
        m_pimpl->set_protocol( value );
    }
    
    void Response::set_status_code( const int value )
    {
        m_pimpl->set_status_code( value );
    }
    
    void Response::set_status_message( const string& value )
    {
        m_pimpl->set_status_message( value );
    }
    
    void Response::set_body( const string& value )
    {
        m_pimpl->set_body( String::to_bytes( value ) );
    }
    
    void Response::set_body( const Bytes& value )
    {
        m_pimpl->set_body( value );
    }
    
    void Response::set_header( const string& name, const string& value )
    {
        m_pimpl->set_header( name, value );
    }
    
    void Response::set_headers( const multimap< string, string >& values )
    {
        m_pimpl->set_headers( values );
    }
}
