/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <utility>
#include <algorithm>

//Project Includes
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/detail/request_impl.hpp"

//External Includes

//System Namespaces
using std::map;
using std::pair;
using std::string;
using std::function;
using std::multimap;
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
    
    Request::~Request( void )
    {
        delete m_pimpl;
    }
    
    bool Request::has_header( const string& name ) const
    {
        const auto key = String::lowercase( name );
        
        auto iterator = find_if( m_pimpl->headers.begin( ), m_pimpl->headers.end( ), [ &key ]( const pair< string, string >& value )
        {
            return ( key == String::lowercase( value.first ) );
        } );
        
        return iterator not_eq m_pimpl->headers.end( );
    }
    
    bool Request::has_path_parameter( const string& name, const bool ignore_case ) const
    {
        if ( not ignore_case )
        {
            return m_pimpl->path_parameters.find( name ) not_eq m_pimpl->path_parameters.end( );
        }
        
        const auto key = String::lowercase( name );
        const auto iterator = find_if( m_pimpl->path_parameters.begin( ), m_pimpl->path_parameters.end( ), [ &key ]( const pair< string, string >& value )
        {
            return ( key == String::lowercase( value.first ) );
        } );
        
        return iterator not_eq m_pimpl->path_parameters.end( );
    }
    
    bool Request::has_query_parameter( const string& name, const bool ignore_case ) const
    {
        if ( not ignore_case )
        {
            return m_pimpl->query_parameters.find( name ) not_eq m_pimpl->query_parameters.end( );
        }
        
        const auto key = String::lowercase( name );
        const auto iterator = find_if( m_pimpl->query_parameters.begin( ), m_pimpl->query_parameters.end( ), [ &key ]( const pair< string, string >& value )
        {
            return ( key == String::lowercase( value.first ) );
        } );
        
        return iterator not_eq m_pimpl->query_parameters.end( );
    }
    
    double Request::get_version( void ) const
    {
        return m_pimpl->version;
    }
    
    const Bytes& Request::get_body( void ) const
    {
        return m_pimpl->body;
    }
    
    string Request::get_path( const function< string ( const string& ) >& transform ) const
    {
        return ( transform == nullptr ) ? m_pimpl->path : transform( m_pimpl->path );
    }
    
    string Request::get_method( const function< string ( const string& ) >& transform ) const
    {
        return ( transform == nullptr ) ? m_pimpl->method : transform( m_pimpl->method );
    }
    
    string Request::get_protocol( const function< string ( const string& ) >& transform ) const
    {
        return ( transform == nullptr ) ? m_pimpl->protocol : transform( m_pimpl->protocol );
    }
    
    void Request::get_body( string& body, const function< string ( const Bytes& ) >& transform ) const
    {
        body = ( transform == nullptr ) ? string( m_pimpl->body.begin( ), m_pimpl->body.end( ) ) : transform( m_pimpl->body );
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
    
    multimap< string, string > Request::get_headers( const string& name ) const
    {
        if ( name.empty( ) )
        {
            return m_pimpl->headers;
        }
        
        decltype( m_pimpl->headers ) headers;
        const auto key = String::lowercase( name );
        
        for ( const auto& header : m_pimpl->headers )
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
        const auto iterator = find_if( m_pimpl->headers.begin( ), m_pimpl->headers.end( ), [ &key ]( const pair< string, string >& value )
        {
            return ( key == String::lowercase( value.first ) );
        } );
        
        return ( iterator == m_pimpl->headers.end( ) ) ? default_value : iterator->second;
    }
    
    string Request::get_header( const string& name, const function< string ( const string& ) >& transform ) const
    {
        const auto header = get_header( name, "" );
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
    
    string Request::get_query_parameter( const string& name, const bool ignore_case ) const
    {
        return get_query_parameter( name, "", ignore_case );
    }
    
    string Request::get_query_parameter( const string& name, const string& default_value, bool ignore_case ) const
    {
        if ( not ignore_case )
        {
            const auto iterator = m_pimpl->query_parameters.find( name );
            return ( iterator == m_pimpl->query_parameters.end( ) ) ? default_value : iterator->second;
        }
        
        const auto key = String::lowercase( name );
        const auto iterator = find_if( m_pimpl->query_parameters.begin( ), m_pimpl->query_parameters.end( ), [ &key ]( const pair< string, string >& value )
        {
            return ( key == String::lowercase( value.first ) );
        } );
        
        return ( iterator == m_pimpl->query_parameters.end( ) ) ? default_value : iterator->second;
    }
    
    string Request::get_query_parameter( const string& name, const function< string ( const string& ) >& transform, bool ignore_case ) const
    {
        const auto parameter = get_query_parameter( name, "", ignore_case );
        return ( transform == nullptr ) ? parameter : transform( parameter );
    }
    
    multimap< string, string > Request::get_query_parameters( const string& name, const bool ignore_case ) const
    {
        if ( name.empty( ) )
        {
            return m_pimpl->query_parameters;
        }
        
        if ( not ignore_case )
        {
            const auto iterators = m_pimpl->query_parameters.equal_range( name );
            return decltype( m_pimpl->query_parameters )( iterators.first, iterators.second );
        }
        
        const auto key = String::lowercase( name );
        decltype( m_pimpl->query_parameters ) parameters;
        
        for ( const auto& parameter : m_pimpl->query_parameters )
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
    
    string Request::get_path_parameter( const string& name, const bool ignore_case ) const
    {
        return get_path_parameter( name, "", ignore_case );
    }
    
    string Request::get_path_parameter( const string& name, const string& default_value, bool ignore_case ) const
    {
        if ( not ignore_case )
        {
            const auto iterator = m_pimpl->path_parameters.find( name );
            return ( iterator == m_pimpl->path_parameters.end( ) ) ? default_value : iterator->second;
        }
        
        const auto key = String::lowercase( name );
        const auto iterator = find_if( m_pimpl->path_parameters.begin( ), m_pimpl->path_parameters.end( ), [ &key ]( const pair< string, string >& value )
        {
            return ( key == String::lowercase( value.first ) );
        } );
        
        return ( iterator == m_pimpl->path_parameters.end( ) ) ? default_value : iterator->second;
    }
    
    string Request::get_path_parameter( const string& name, const function< string ( const string& ) >& transform, bool ignore_case ) const
    {
        const auto parameter = get_path_parameter( name, "", ignore_case );
        return ( transform == nullptr ) ? parameter : transform( parameter );
    }
    
    map< string, string > Request::get_path_parameters( const string& name, const bool ignore_case ) const
    {
        if ( name.empty( ) )
        {
            return m_pimpl->path_parameters;
        }
        
        if ( not ignore_case )
        {
            const auto iterators = m_pimpl->path_parameters.equal_range( name );
            return decltype( m_pimpl->path_parameters )( iterators.first, iterators.second );
        }
        
        const auto key = String::lowercase( name );
        decltype( m_pimpl->path_parameters ) parameters;
        
        for ( const auto& parameter : m_pimpl->path_parameters )
        {
            if ( key == String::lowercase( parameter.first ) )
            {
                parameters.insert( parameter );
            }
        }
        
        return parameters;
    }
}
