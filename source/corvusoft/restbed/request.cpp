/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
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
using std::string;
using std::function;
using std::multimap;
using std::shared_ptr;
using std::make_shared;
using std::invalid_argument;

//Project Namespaces
using restbed::detail::RequestImpl;

//External Namespaces

namespace restbed
{
    Request::Request( void ) : m_pimpl( new detail::RequestImpl )
    {
        return;
    }
    
    Request::Request( const Uri& uri ) : m_pimpl( new detail::RequestImpl )
    {
        m_pimpl->m_uri = make_shared< Uri >( uri );
        m_pimpl->m_path = uri.get_path( );
        m_pimpl->m_port = uri.get_port( );
        m_pimpl->m_host = uri.get_authority( );
        m_pimpl->m_query_parameters = uri.get_query_parameters( );
        m_pimpl->m_protocol = String::uppercase( uri.get_scheme( ) );
        
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
        delete m_pimpl;
    }
    
    bool Request::has_header( const string& name ) const
    {
        const auto key = String::lowercase( name );
        
        auto iterator = find_if( m_pimpl->m_headers.begin( ), m_pimpl->m_headers.end( ), [ &key ]( const pair< string, string >& value )
        {
            return ( key == String::lowercase( value.first ) );
        } );
        
        return iterator not_eq m_pimpl->m_headers.end( );
    }
    
    bool Request::has_path_parameter( const string& name, const String::Option option ) const
    {
        if ( option == String::Option::CASE_SENSITIVE )
        {
            return m_pimpl->m_path_parameters.find( name ) not_eq m_pimpl->m_path_parameters.end( );
        }
        
        const auto key = String::lowercase( name );
        const auto iterator = find_if( m_pimpl->m_path_parameters.begin( ), m_pimpl->m_path_parameters.end( ), [ &key ]( const pair< string, string >& value )
        {
            return ( key == String::lowercase( value.first ) );
        } );
        
        return iterator not_eq m_pimpl->m_path_parameters.end( );
    }
    
    bool Request::has_query_parameter( const string& name, const String::Option option ) const
    {
        if ( option == String::Option::CASE_SENSITIVE )
        {
            return m_pimpl->m_query_parameters.find( name ) not_eq m_pimpl->m_query_parameters.end( );
        }
        
        const auto key = String::lowercase( name );
        const auto iterator = find_if( m_pimpl->m_query_parameters.begin( ), m_pimpl->m_query_parameters.end( ), [ &key ]( const pair< string, string >& value )
        {
            return ( key == String::lowercase( value.first ) );
        } );
        
        return iterator not_eq m_pimpl->m_query_parameters.end( );
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
        return ( transform == nullptr ) ? m_pimpl->m_host : transform( m_pimpl->m_host );
    }
    
    string Request::get_path( const function< string ( const string& ) >& transform ) const
    {
        return ( transform == nullptr ) ? m_pimpl->m_path : transform( m_pimpl->m_path );
    }
    
    string Request::get_method( const function< string ( const string& ) >& transform ) const
    {
        return ( transform == nullptr ) ? m_pimpl->m_method : transform( m_pimpl->m_method );
    }
    
    string Request::get_protocol( const function< string ( const string& ) >& transform ) const
    {
        return ( transform == nullptr ) ? m_pimpl->m_protocol : transform( m_pimpl->m_protocol );
    }
    
    void Request::get_body( string& body, const function< string ( const Bytes& ) >& transform ) const
    {
        body = ( transform == nullptr ) ? string( m_pimpl->m_body.begin( ), m_pimpl->m_body.end( ) ) : transform( m_pimpl->m_body );
    }
    
    void Request::get_header( const string& name, int& value, const int default_value ) const
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
    
    void Request::get_header( const string& name, long& value, const long default_value ) const
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
    
    void Request::get_header( const string& name, float& value, const float default_value ) const
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
    
    void Request::get_header( const string& name, double& value, const double default_value ) const
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
    
    void Request::get_header( const string& name, long long& value, const long long default_value ) const
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
    
    void Request::get_header( const string& name, unsigned int& value, const unsigned int default_value ) const
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
    
    void Request::get_header( const string& name, unsigned long& value, const unsigned long default_value ) const
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
    
    void Request::get_header( const string& name, unsigned long long& value, const unsigned long long default_value ) const
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
    
    multimap< string, string > Request::get_headers( const string& name ) const
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
    
    string Request::get_header( const string& name, const string& default_value ) const
    {
        const auto key = String::lowercase( name );
        const auto iterator = find_if( m_pimpl->m_headers.begin( ), m_pimpl->m_headers.end( ), [ &key ]( const pair< string, string >& value )
        {
            return ( key == String::lowercase( value.first ) );
        } );
        
        return ( iterator == m_pimpl->m_headers.end( ) ) ? default_value : iterator->second;
    }
    
    string Request::get_header( const string& name, const function< string ( const string& ) >& transform ) const
    {
        const string header = get_header( name );
        return ( transform == nullptr ) ? header : transform( header );
    }
    
    void Request::get_query_parameter( const string& name, int& value, const int default_value ) const
    {
        try
        {
            value = stoi( get_query_parameter( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Request::get_query_parameter( const string& name, long& value, const long default_value ) const
    {
        try
        {
            value = stol( get_query_parameter( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Request::get_query_parameter( const string& name, float& value, const float default_value ) const
    {
        try
        {
            value = stof( get_query_parameter( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Request::get_query_parameter( const string& name, double& value, const double default_value ) const
    {
        try
        {
            value = stod( get_query_parameter( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Request::get_query_parameter( const string& name, long long& value, const long long default_value ) const
    {
        try
        {
            value = stoll( get_query_parameter( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Request::get_query_parameter( const string& name, unsigned int& value, const unsigned int default_value ) const
    {
        try
        {
            value = stoul( get_query_parameter( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Request::get_query_parameter( const string& name, unsigned long& value, const unsigned long default_value ) const
    {
        try
        {
            value = stoul( get_query_parameter( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Request::get_query_parameter( const string& name, unsigned long long& value, const unsigned long long default_value ) const
    {
        try
        {
            value = stoull( get_query_parameter( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    string Request::get_query_parameter( const string& name, const String::Option option ) const
    {
        return get_query_parameter( name, string( "" ), option );
    }
    
    string Request::get_query_parameter( const string& name, const string& default_value, const String::Option option ) const
    {
        if ( option == String::Option::CASE_SENSITIVE )
        {
            const auto iterator = m_pimpl->m_query_parameters.find( name );
            return ( iterator == m_pimpl->m_query_parameters.end( ) ) ? default_value : iterator->second;
        }
        
        const auto key = String::lowercase( name );
        const auto iterator = find_if( m_pimpl->m_query_parameters.begin( ), m_pimpl->m_query_parameters.end( ), [ &key ]( const pair< string, string >& value )
        {
            return ( key == String::lowercase( value.first ) );
        } );
        
        return ( iterator == m_pimpl->m_query_parameters.end( ) ) ? default_value : iterator->second;
    }
    
    string Request::get_query_parameter( const string& name, const function< string ( const string& ) >& transform, const String::Option option ) const
    {
        const auto parameter = get_query_parameter( name, string( "" ), option );
        return ( transform == nullptr ) ? parameter : transform( parameter );
    }
    
    multimap< string, string > Request::get_query_parameters( const string& name, const String::Option option ) const
    {
        if ( name.empty( ) )
        {
            return m_pimpl->m_query_parameters;
        }
        
        if ( option == String::Option::CASE_SENSITIVE )
        {
            const auto iterators = m_pimpl->m_query_parameters.equal_range( name );
            return decltype( m_pimpl->m_query_parameters )( iterators.first, iterators.second );
        }
        
        const auto key = String::lowercase( name );
        decltype( m_pimpl->m_query_parameters ) parameters;
        
        for ( const auto& parameter : m_pimpl->m_query_parameters )
        {
            if ( key == String::lowercase( parameter.first ) )
            {
                parameters.insert( parameter );
            }
        }
        
        return parameters;
    }
    
    void Request::get_path_parameter( const string& name, int& value, const int default_value ) const
    {
        try
        {
            value = stoi( get_path_parameter( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Request::get_path_parameter( const string& name, long& value, const long default_value ) const
    {
        try
        {
            value = stol( get_path_parameter( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Request::get_path_parameter( const string& name, float& value, const float default_value ) const
    {
        try
        {
            value = stof( get_path_parameter( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Request::get_path_parameter( const string& name, double& value, const double default_value ) const
    {
        try
        {
            value = stod( get_path_parameter( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Request::get_path_parameter( const string& name, long long& value, const long long default_value ) const
    {
        try
        {
            value = stoll( get_path_parameter( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Request::get_path_parameter( const string& name, unsigned int& value, const unsigned int default_value ) const
    {
        try
        {
            value = stoul( get_path_parameter( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Request::get_path_parameter( const string& name, unsigned long& value, const unsigned long default_value ) const
    {
        try
        {
            value = stoul( get_path_parameter( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    void Request::get_path_parameter( const string& name, unsigned long long& value, const unsigned long long default_value ) const
    {
        try
        {
            value = stoull( get_path_parameter( name ) );
        }
        catch ( const invalid_argument& )
        {
            value = default_value;
        }
    }
    
    string Request::get_path_parameter( const string& name, const String::Option option ) const
    {
        return get_path_parameter( name, string( "" ), option );
    }
    
    string Request::get_path_parameter( const string& name, const string& default_value, const String::Option option ) const
    {
        if ( option == String::Option::CASE_SENSITIVE )
        {
            const auto iterator = m_pimpl->m_path_parameters.find( name );
            return ( iterator == m_pimpl->m_path_parameters.end( ) ) ? default_value : iterator->second;
        }
        
        const auto key = String::lowercase( name );
        const auto iterator = find_if( m_pimpl->m_path_parameters.begin( ), m_pimpl->m_path_parameters.end( ), [ &key ]( const pair< string, string >& value )
        {
            return ( key == String::lowercase( value.first ) );
        } );
        
        return ( iterator == m_pimpl->m_path_parameters.end( ) ) ? default_value : iterator->second;
    }
    
    string Request::get_path_parameter( const string& name, const function< string ( const string& ) >& transform, const String::Option option ) const
    {
        const auto parameter = get_path_parameter( name, string( "" ), option );
        return ( transform == nullptr ) ? parameter : transform( parameter );
    }
    
    map< string, string > Request::get_path_parameters( const string& name, const String::Option option ) const
    {
        if ( name.empty( ) )
        {
            return m_pimpl->m_path_parameters;
        }
        
        if ( option == String::Option::CASE_SENSITIVE )
        {
            const auto iterators = m_pimpl->m_path_parameters.equal_range( name );
            return decltype( m_pimpl->m_path_parameters )( iterators.first, iterators.second );
        }
        
        const auto key = String::lowercase( name );
        decltype( m_pimpl->m_path_parameters ) parameters;
        
        for ( const auto& parameter : m_pimpl->m_path_parameters )
        {
            if ( key == String::lowercase( parameter.first ) )
            {
                parameters.insert( parameter );
            }
        }
        
        return parameters;
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
    
    void Request::set_header( const string& name, const string& value )
    {
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
