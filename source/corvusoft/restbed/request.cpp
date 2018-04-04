/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <utility>
#include <ciso646>
#include <algorithm>

//Project Includes
#include "corvusoft/restbed/uri.hpp"
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/response.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"
#include "corvusoft/restbed/detail/request_impl.hpp"
#include "corvusoft/restbed/detail/response_impl.hpp"

//External Includes

//System Namespaces
using std::map;
using std::pair;
using std::stof;
using std::stod;
using std::string;
using std::function;
using std::multimap;
using std::make_pair;
using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;
using std::out_of_range;
using std::invalid_argument;

//Project Namespaces
using restbed::Common;
using restbed::detail::RequestImpl;

//External Namespaces

namespace restbed
{
    Request::Request( void ) : m_pimpl( new detail::RequestImpl )
    {
        return;
    }
    
    Request::Request( const Uri& value ) : m_pimpl( new detail::RequestImpl )
    {
        m_pimpl->m_uri = make_shared< Uri >( value );
        m_pimpl->m_path = value.get_path( );
        m_pimpl->m_port = value.get_port( );
        m_pimpl->m_host = value.get_authority( );
        m_pimpl->m_query_parameters = value.get_query_parameters( );
        m_pimpl->m_protocol = String::uppercase( value.get_scheme( ) );
        
        if ( m_pimpl->m_path.empty( ) )
        {
            m_pimpl->m_path = "/";
        }
        
        if ( m_pimpl->m_port == 0 )
        {
            m_pimpl->m_port = ( m_pimpl->m_protocol == "HTTPS" ) ? 443 : 80;
        }
    }
    
    Request::~Request( void )
    {
        return;
    }
    
    bool Request::has_header( const string& name ) const
    {
        return Common::has_parameter( name, m_pimpl->m_headers );
    }
    
    bool Request::has_path_parameter( const string& name ) const
    {
        return Common::has_parameter( name, m_pimpl->m_path_parameters );
    }
    
    bool Request::has_query_parameter( const string& name ) const
    {
        return Common::has_parameter( name, m_pimpl->m_query_parameters );
    }
    
    uint16_t Request::get_port( void ) const
    {
        return m_pimpl->m_port;
    }
    
    double Request::get_version( void ) const
    {
        return m_pimpl->m_version;
    }
    
    const Bytes& Request::get_body( void ) const
    {
        return m_pimpl->m_body;
    }
    
    const shared_ptr< const Response > Request::get_response( void ) const
    {
        return m_pimpl->m_response;
    }
    
    string Request::get_host( const function< string ( const string& ) >& transform ) const
    {
        return Common::transform( m_pimpl->m_host, transform );
    }
    
    string Request::get_path( const function< string ( const string& ) >& transform ) const
    {
        return Common::transform( m_pimpl->m_path, transform );
    }
    
    string Request::get_method( const function< string ( const string& ) >& transform ) const
    {
        return Common::transform( m_pimpl->m_method, transform );
    }
    
    string Request::get_protocol( const function< string ( const string& ) >& transform ) const
    {
        return Common::transform( m_pimpl->m_protocol, transform );
    }
    
    void Request::get_body( string& body, const function< string ( const Bytes& ) >& transform ) const
    {
        body = ( transform == nullptr ) ? String::to_string( m_pimpl->m_body ) : transform( m_pimpl->m_body );
    }
    
    float Request::get_header( const string& name, const float default_value ) const
    {
        float header = 0;
        
        try
        {
            header = stof( get_header( name ) );
        }
        catch ( const out_of_range )
        {
            header = default_value;
        }
        catch ( const invalid_argument )
        {
            header = default_value;
        }
        
        return header;
    }
    
    double Request::get_header( const string& name, const double default_value ) const
    {
        double header = 0;
        
        try
        {
            header = stod( get_header( name ) );
        }
        catch ( const out_of_range )
        {
            header = default_value;
        }
        catch ( const invalid_argument )
        {
            header = default_value;
        }
        
        return header;
    }
    
    string Request::get_header( const string& name, const string& default_value ) const
    {
        if ( name.empty( ) )
        {
            return default_value;
        }
        
        const auto headers = Common::get_parameters( name, m_pimpl->m_headers );
        return ( headers.empty( ) ) ? default_value : headers.begin( )->second;
    }
    
    string Request::get_header( const string& name, const function< string ( const string& ) >& transform ) const
    {
        if ( name.empty( ) )
        {
            return String::empty;
        }
        
        const auto headers = Common::get_parameters( name, m_pimpl->m_headers );
        const auto value = ( headers.empty( ) ) ? String::empty : headers.begin( )->second;
        
        return Common::transform( value, transform );
    }
    
    multimap< string, string > Request::get_headers( const string& name ) const
    {
        return Common::get_parameters( name, m_pimpl->m_headers );
    }
    
    float Request::get_query_parameter( const string& name, const float default_value ) const
    {
        float parameter = 0;
        
        try
        {
            parameter = stof( get_query_parameter( name ) );
        }
        catch ( const out_of_range )
        {
            parameter = default_value;
        }
        catch ( const invalid_argument )
        {
            parameter = default_value;
        }
        
        return parameter;
    }
    
    double Request::get_query_parameter( const string& name, const double default_value ) const
    {
        double parameter = 0;
        
        try
        {
            parameter = stod( get_query_parameter( name ) );
        }
        catch ( const out_of_range )
        {
            parameter = default_value;
        }
        catch ( const invalid_argument )
        {
            parameter = default_value;
        }
        
        return parameter;
    }
    
    string Request::get_query_parameter( const string& name, const string& default_value ) const
    {
        if ( name.empty( ) )
        {
            return default_value;
        }
        
        const auto parameters = Common::get_parameters( name, m_pimpl->m_query_parameters );
        return ( parameters.empty( ) ) ? default_value : parameters.begin( )->second;
    }
    
    string Request::get_query_parameter( const string& name, const function< string ( const string& ) >& transform ) const
    {
        if ( name.empty( ) )
        {
            return String::empty;
        }
        
        const auto parameters = Common::get_parameters( name, m_pimpl->m_query_parameters );
        const auto value = ( parameters.empty( ) ) ? String::empty : parameters.begin( )->second;
        
        return Common::transform( value, transform );
    }
    
    multimap< string, string > Request::get_query_parameters( const string& name ) const
    {
        return Common::get_parameters( name, m_pimpl->m_query_parameters );
    }
    
    float Request::get_path_parameter( const string& name, const float default_value ) const
    {
        float parameter = 0;
        
        try
        {
            parameter = stof( get_path_parameter( name ) );
        }
        catch ( const out_of_range )
        {
            parameter = default_value;
        }
        catch ( const invalid_argument )
        {
            parameter = default_value;
        }
        
        return parameter;
    }
    
    double Request::get_path_parameter( const string& name, const double default_value ) const
    {
        double parameter = 0;
        
        try
        {
            parameter = stod( get_path_parameter( name ) );
        }
        catch ( const out_of_range )
        {
            parameter = default_value;
        }
        catch ( const invalid_argument )
        {
            parameter = default_value;
        }
        
        return parameter;
    }
    
    string Request::get_path_parameter( const string& name, const string& default_value ) const
    {
        if ( name.empty( ) )
        {
            return default_value;
        }
        
        const auto parameters = Common::get_parameters( name, m_pimpl->m_path_parameters );
        return ( parameters.empty( ) ) ? default_value : parameters.begin( )->second;
    }
    
    string Request::get_path_parameter( const string& name, const function< string ( const string& ) >& transform ) const
    {
        if ( name.empty( ) )
        {
            return String::empty;
        }
        
        const auto parameters = Common::get_parameters( name, m_pimpl->m_path_parameters );
        const auto value = ( parameters.empty( ) ) ? String::empty : parameters.begin( )->second;
        
        return Common::transform( value, transform );
    }
    
    map< string, string > Request::get_path_parameters( const string& name ) const
    {
        return Common::get_parameters( name, m_pimpl->m_path_parameters );
    }
    
    void Request::set_body( const Bytes& value )
    {
        m_pimpl->m_body = value;
    }
    
    void Request::set_body( const string& value )
    {
        m_pimpl->m_body = String::to_bytes( value );
    }
    
    void Request::set_port( const uint16_t value )
    {
        if ( m_pimpl->m_socket not_eq nullptr )
        {
            m_pimpl->m_socket->close( );
        }
        
        m_pimpl->m_port = value;
    }
    
    void Request::set_version( const double value )
    {
        m_pimpl->m_version = value;
    }
    
    void Request::set_path( const string& value )
    {
        m_pimpl->m_path = value;
    }
    
    void Request::set_host( const string& value )
    {
        if ( m_pimpl->m_socket not_eq nullptr )
        {
            m_pimpl->m_socket->close( );
        }
        
        m_pimpl->m_host = value;
    }
    
    void Request::set_method( const string& value )
    {
        m_pimpl->m_method = value;
    }
    
    void Request::set_protocol( const string& value )
    {
        m_pimpl->m_protocol = value;
    }
    
    void Request::add_header( const string& name, const string& value )
    {
        m_pimpl->m_headers.insert( make_pair( name, value ) );
    }
    
    void Request::set_header( const string& name, const string& value )
    {
        m_pimpl->m_headers.erase( name );
        m_pimpl->m_headers.insert( make_pair( name, value ) );
    }
    
    void Request::set_headers( const multimap< string, string >& values )
    {
        m_pimpl->m_headers = values;
    }
    
    void Request::set_query_parameter( const string& name, const string& value )
    {
        m_pimpl->m_query_parameters.insert( make_pair( name, value ) );
    }
    
    void Request::set_query_parameters( const multimap< string, string >& values )
    {
        m_pimpl->m_query_parameters = values;
    }
}
