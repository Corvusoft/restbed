/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <istream>

//Project Includes
#include "corvusoft/restbed/detail/request_impl.h"

//External Includes
#include <corvusoft/framework/map>
#include <corvusoft/framework/string>

//System Namespaces
using std::map;
using std::stod;
using std::string;
using std::istream;
using std::multimap;
using std::function;
using std::shared_ptr;
using std::istreambuf_iterator;

//Project Namespaces
using restbed::detail::RequestImpl;

//External Namespaces
using framework::Map;
using framework::Bytes;
using framework::String;

namespace restbed
{
    namespace detail
    {
        RequestImpl::RequestImpl( void ) : m_body( ),
            m_version( 1.1 ),
            m_path( "/" ),
            m_method( "GET" ),
            m_origin( String::empty ),
            m_destination( String::empty ),
            m_protocol( "HTTP" ),
            m_headers( ),
            m_path_parameters( ),
            m_query_parameters( )
        {
            return;
        }
        
        RequestImpl::~RequestImpl( void )
        {
            return;
        }
//        
//        bool RequestImpl::has_header( const string& name ) const
//        {
//            return ( Map::find_ignoring_case( name, m_headers ) not_eq m_headers.end( ) );
//        }
//        
//        bool RequestImpl::has_path_parameter( const string& name ) const
//        {
//            return ( Map::find_ignoring_case( name, m_path_parameters ) not_eq m_path_parameters.end( ) );
//        }
//        
//        bool RequestImpl::has_query_parameter( const string& name ) const
//        {
//            return ( m_query_parameters.find( name ) not_eq m_query_parameters.end( ) );
//        }
//        
//        Bytes RequestImpl::get_body( void )
//        {
//            return m_body;
//        }

        double RequestImpl::get_version( void ) const
        {
            return m_version;
        }
        
        const string& RequestImpl::get_path( void ) const
        {
            return m_path;
        }
        
        const string& RequestImpl::get_method( void ) const
        {
            return m_method;
        }
        
//        string RequestImpl::get_origin( void ) const
//        {
//            return m_origin;
//        }
//
//        string RequestImpl::get_destination( void ) const
//        {
//            return m_destination;
//        }
//
        const string& RequestImpl::get_protocol( void ) const
        {
            return m_protocol;
        }
//
//        string RequestImpl::get_header( const string& name, const string& default_value ) const
//        {
//            string value = default_value;
//            
//            if ( has_header( name ) )
//            {
//                const auto iterator = Map::find_ignoring_case( name, m_headers );
//                
//                value = iterator->second;
//            }
//            
//            return value;
//        }
//        
//        multimap< string, string > RequestImpl::get_headers( void ) const
//        {
//            return m_headers;
//        }
//        
        multimap< string, string > RequestImpl::get_headers( const string& name, const function< string ( const string& ) >& transform ) const
        {
            const auto key = transform( name );

            multimap< string, string > headers;
            
            for ( auto header : m_headers )
            {
                if ( transform( header.first ) == key )
                {
                    headers.insert( header );
                }
            }
            
            return headers;
        }

//        string RequestImpl::get_query_parameter( const string& name, const string& default_value ) const
//        {
//            string parameter = default_value;
//            
//            if ( has_query_parameter( name ) )
//            {
//                const auto iterator = m_query_parameters.find( name );
//                
//                parameter = iterator->second;
//            }
//            
//            return parameter;
//        }
//        
//        multimap< string, string > RequestImpl::get_query_parameters( void ) const
//        {
//            return m_query_parameters;
//        }
//
//        multimap< string, string > RequestImpl::get_query_parameters( const string& name ) const
//        {
//            multimap< string, string > parameters;
//            
//            for ( auto parameter : m_query_parameters )
//            {
//                if ( parameter.first == name )
//                {
//                    parameters.insert( parameter );
//                }
//            }
//            
//            return parameters;
//        }

        string RequestImpl::get_path_parameter( const string& name,
                                                const string& default_value,
                                                function< string ( const string& ) > transform ) const
        {
            string parameter = default_value;

            if ( m_path_parameters.count( name ) )
            {
                parameter = m_path_parameters.at( name );
            }

            return ( transform not_eq nullptr ) ? transform( parameter ) : parameter;
        }

//        string RequestImpl::get_path_parameter( const string& name, const string& default_value ) const
//        {
//            string parameter = default_value;
//            
//            if ( has_path_parameter( name ) )
//            {
//                const auto iterator = Map::find_ignoring_case( name, m_path_parameters );
//                
//                parameter = iterator->second;
//            }
//            
//            return parameter;
//        }
//        
//        map< string, string > RequestImpl::get_path_parameters( void ) const
//        {
//            return m_path_parameters;
//        }
//        
//        void RequestImpl::set_body( const Bytes& value )
//        {
//            m_body = value;
//        }
//        
       void RequestImpl::set_version( const double value )
       {
           m_version = value;
       }
       
       void RequestImpl::set_path( const string& value )
       {
           m_path = value;
       }
       
       void RequestImpl::set_method( const string& value )
       {
           m_method = value;
       }

       void RequestImpl::set_protocol( const string& value )
       {
           m_protocol = value;
       }

       void RequestImpl::set_headers( const multimap< string, string >& values )
       {
           m_headers = values;
       }
        
        void RequestImpl::set_path_parameter( const string& name, const string& value )
        {
            m_path_parameters[ name ] = value;
        }

       void RequestImpl::set_query_parameters( const multimap< string, string >& values )
       {
           m_query_parameters = values;
       }
    }
}
