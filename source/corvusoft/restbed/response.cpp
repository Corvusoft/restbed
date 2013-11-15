/*
 * Copyright (c) 2013 Corvusoft
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

    Bytes Response::to_bytes( void ) const
    {
        return m_pimpl->to_bytes( );
    }

    Bytes Response::get_body( void ) const
    {
        return m_pimpl->get_body( );
    }

    int Response::get_status_code( void ) const
    {
        return m_pimpl->get_status_code( );
    }

    string Response::get_header( const string& name ) const
    {
        return m_pimpl->get_header( name );
    }

    map< string, string > Response::get_headers( void ) const
    {
        return m_pimpl->get_headers( );
    }

    void Response::set_body( const Bytes& value )
    {
        m_pimpl->set_body( value );
    }

    void Response::set_body( const string& value )
    {
        m_pimpl->set_body( value );
    }

    void Response::set_status_code( const int value )
    {
        m_pimpl->set_status_code( value );
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
