/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/method.h"
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/detail/request_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::string;
using std::multimap;

//Project Namespaces
using restbed::detail::RequestImpl;

//External Namespaces
using framework::Bytes;

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
    
    Request::Request( const RequestImpl& implementation ) : m_pimpl( new RequestImpl( implementation ) )
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
    
    Bytes Request::get_body( void ) const
    {
        return m_pimpl->get_body( );
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
    
    string Request::get_origin( void ) const
    {
        return m_pimpl->get_origin( );
    }

    string Request::get_protocol( void ) const
    {
        return m_pimpl->get_protocol( );
    }
    
    string Request::get_header( const string& name, const string& default_value ) const
    {
        return m_pimpl->get_header( name, default_value );
    }
    
    multimap< string, string > Request::get_headers( void ) const
    {
        return m_pimpl->get_headers( );
    }
    
    multimap< string, string > Request::get_headers( const string& name ) const
    {
        return m_pimpl->get_headers( name );
    }
    
    string Request::get_query_parameter( const string& name, const string& default_value ) const
    {
        return m_pimpl->get_query_parameter( name, default_value );
    }

    multimap< string, string > Request::get_query_parameters( void ) const
    {
        return m_pimpl->get_query_parameters( );
    }
    
    multimap< string, string > Request::get_query_parameters( const string& name ) const
    {
        return m_pimpl->get_query_parameters( name );
    }
    
    string Request::get_path_parameter( const string& name, const string& default_value ) const
    {
        return m_pimpl->get_path_parameter( name, default_value );
    }
    
    map< string, string > Request::get_path_parameters( void ) const
    {
        return m_pimpl->get_path_parameters( );
    }
    
    Request& Request::operator =( const Request& value )
    {
        *m_pimpl = *value.m_pimpl;
        
        return *this;
    }
    
    bool Request::operator <( const Request& value ) const
    {
        return *m_pimpl < *value.m_pimpl;
    }
    
    bool Request::operator >( const Request& value ) const
    {
        return *m_pimpl > *value.m_pimpl;
    }
    
    bool Request::operator ==( const Request& value ) const
    {
        return *m_pimpl == *value.m_pimpl;
    }
    
    bool Request::operator !=( const Request& value ) const
    {
        return *m_pimpl != *value.m_pimpl;
    }
}
