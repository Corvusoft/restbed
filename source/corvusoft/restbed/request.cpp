/*
 * Copyright (c) 2013 Corvusoft
 */

//System Includes
 
//Project Includes
#include "restbed/method.h"
#include "restbed/request.h"
#include "restbed/detail/request_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::string;
using std::istream;

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
    
    Bytes Request::to_bytes( void ) const
    {
        return m_pimpl->to_bytes( );
    }

    bool Request::has_header( const string& name ) const
    {
        return m_pimpl->has_header( name );
    }

    bool Request::has_path_parameter( const string& name ) const
    {
        return m_pimpl->has_path_parameter( name );
    }

    bool Request::has_query_parameter( const string& name ) const
    {
        return m_pimpl->has_query_parameter( name );
    }

    Method Request::get_method( void ) const
    {
        return m_pimpl->get_method( );
    }

    double Request::get_version( void ) const
    {
        return m_pimpl->get_version( );
    }

    string Request::get_path( void ) const
    {
        return m_pimpl->get_path( );
    }

    string Request::get_body( void ) const
    {
        return m_pimpl->get_body( );
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
