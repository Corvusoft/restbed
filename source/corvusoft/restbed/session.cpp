/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/session.h"
#include "corvusoft/restbed/detail/session_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::string;
using std::multimap;

//Project Namespaces
using restbed::detail::SessionImpl;

//External Namespaces
using framework::Bytes;

namespace restbed
{
    Session::Session( void ) : m_pimpl( new SessionImpl )
    {
        return;
    }
    
    Session::Session( const Session& original ) : m_pimpl( new SessionImpl( *original.m_pimpl ) )
    {
        return;
    }
    
    Session::~Session( void )
    {
        return;
    }
    
    bool Session::has_header( const string& name ) const
    {
        return m_pimpl->has_header( name );
    }
    
    bool Session::has_path_parameter( const string& name ) const
    {
        return m_pimpl->has_path_parameter( name );
    }
    
    bool Session::has_query_parameter( const string& name ) const
    {
        return m_pimpl->has_query_parameter( name );
    }
    
    Bytes Session::get_body( void ) const
    {
        return m_pimpl->get_body( );
    }

    Bytes Session::get_body( const size_t length ) const
    {
        return m_pimpl->get_body( length );
    }

    Bytes Session::get_body( const string& delimiter ) const
    {
        return m_pimpl->get_body( delimiter );
    }
    
    double Session::get_version( void ) const
    {
        return m_pimpl->get_version( );
    }

    string Session::get_method( void ) const
    {
        return m_pimpl->get_method( );
    }
    
    string Session::get_path( void ) const
    {
        return m_pimpl->get_path( );
    }
    
    string Session::get_origin( void ) const
    {
        return m_pimpl->get_origin( );
    }

    string Session::get_destination( void ) const
    {
        return m_pimpl->get_destination( );
    }

    string Session::get_protocol( void ) const
    {
        return m_pimpl->get_protocol( );
    }
    
    string Session::get_header( const string& name, const string& default_value ) const
    {
        return m_pimpl->get_header( name, default_value );
    }
    
    multimap< string, string > Session::get_headers( void ) const
    {
        return m_pimpl->get_headers( );
    }
    
    multimap< string, string > Session::get_headers( const string& name ) const
    {
        return m_pimpl->get_headers( name );
    }
    
    string Session::get_query_parameter( const string& name, const string& default_value ) const
    {
        return m_pimpl->get_query_parameter( name, default_value );
    }

    multimap< string, string > Session::get_query_parameters( void ) const
    {
        return m_pimpl->get_query_parameters( );
    }
    
    multimap< string, string > Session::get_query_parameters( const string& name ) const
    {
        return m_pimpl->get_query_parameters( name );
    }
    
    string Session::get_path_parameter( const string& name, const string& default_value ) const
    {
        return m_pimpl->get_path_parameter( name, default_value );
    }
    
    map< string, string > Session::get_path_parameters( void ) const
    {
        return m_pimpl->get_path_parameters( );
    }
    
    Session& Session::operator =( const Session& value )
    {
        *m_pimpl = *value.m_pimpl;
        
        return *this;
    }
    
    bool Session::operator <( const Session& value ) const
    {
        return *m_pimpl < *value.m_pimpl;
    }
    
    bool Session::operator >( const Session& value ) const
    {
        return *m_pimpl > *value.m_pimpl;
    }
    
    bool Session::operator ==( const Session& value ) const
    {
        return *m_pimpl == *value.m_pimpl;
    }
    
    bool Session::operator !=( const Session& value ) const
    {
        return *m_pimpl != *value.m_pimpl;
    }
}
