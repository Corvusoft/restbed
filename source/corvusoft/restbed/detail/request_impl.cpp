/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <istream>

//Project Includes
#include "corvusoft/restbed/detail/request_impl.h"

//External Includes
#include <corvusoft/framework/map>

//System Namespaces
using std::map;
using std::stoi;
using std::stod;
using std::stof;
using std::stoul;
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
        RequestImpl::RequestImpl( void ) : m_body( nullptr ),
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
        
        bool RequestImpl::has_header( const string& name ) const
        {
            return ( Map::find_ignoring_case( name, m_headers ) not_eq m_headers.end( ) );
        }
        
        bool RequestImpl::has_path_parameter( const string& name, const bool ignore_case ) const
        {
            if ( ignore_case )
            {
                return ( Map::find_ignoring_case( name, m_path_parameters ) not_eq m_path_parameters.end( ) );
            }

            return m_path_parameters.find( name ) not_eq m_path_parameters.end( );
        }
        
        bool RequestImpl::has_query_parameter( const string& name, const bool ignore_case ) const
        {
            if ( ignore_case )
            {
                return ( Map::find_ignoring_case( name, m_query_parameters ) not_eq m_query_parameters.end( ) );
            }

            return m_query_parameters.find( name ) not_eq m_query_parameters.end( );
        }

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

        const shared_ptr< Bytes >& RequestImpl::get_body( void ) const
        {
            return m_body;
        }

        void RequestImpl::get_header( const string& name,
                                      int& value,
                                      const int default_value,
                                      const function< string ( const string& ) >& transform ) const
        {
            if ( not has_header( name ) )
            {
                value = default_value;
                return;
            }

            string header = get_header( name );

            if ( transform not_eq nullptr )
            {
                header = transform( header );
            }

            value = stoi( header );
        }

        void RequestImpl::get_header( const string& name,
                                      unsigned int& value,
                                      const unsigned int default_value,
                                      const function< string ( const string& ) >& transform ) const
        {
            if ( not has_header( name ) )
            {
                value = default_value;
                return;
            }

            string header = get_header( name );

            if ( transform not_eq nullptr )
            {
                header = transform( header );
            }

            value = stoul( header );
        }

        void RequestImpl::get_header( const string& name,
                                      long& value,
                                      const long default_value,
                                      const function< string ( const string& ) >& transform ) const
        {
            if ( not has_header( name ) )
            {
                value = default_value;
                return;
            }

            string header = get_header( name );

            if ( transform not_eq nullptr )
            {
                header = transform( header );
            }

            value = stol( header );
        }

        void RequestImpl::get_header( const string& name,
                                      unsigned long& value,
                                      const unsigned long default_value,
                                      const function< string ( const string& ) >& transform ) const
        {
            if ( not has_header( name ) )
            {
                value = default_value;
                return;
            }

            string header = get_header( name );

            if ( transform not_eq nullptr )
            {
                header = transform( header );
            }
            
            value = stoul( header );
        }

        void RequestImpl::get_header( const string& name,
                                      float& value,
                                      const float default_value,
                                      const function< string ( const string& ) > transform ) const
        {
            if ( not has_header( name ) )
            {
                value = default_value;
                return;
            }

            string header = get_header( name );

            if ( transform not_eq nullptr )
            {
                header = transform( header );
            }

            value = stof( header );
        }

        void RequestImpl::get_header( const string& name,
                                      double& value,
                                      const double default_value,
                                      const function< string ( const string& ) >& transform ) const
        {
            if ( not has_header( name ) )
            {
                value = default_value;
                return;
            }

            string header = get_header( name );

            if ( transform not_eq nullptr )
            {
                header = transform( header );
            }

            value = stod( header );
        }

        string RequestImpl::get_header( const string& name, const string& default_value, const function< string ( const string& ) >& transform ) const
        {
            string value = default_value;

            const auto headers = get_headers( name, transform );

            if ( headers.size( ) not_eq 0 )
            {
                value = headers.begin( )->second;
            }
            
            return value;
        }

        multimap< string, string > RequestImpl::get_headers( const string& name, const function< string ( const string& ) >& transform ) const
        {
            multimap< string, string > headers;

            const auto key = String::lowercase( name );
            
            for ( auto header : m_headers )
            {
                if ( String::lowercase( header.first ) == key )
                {
                    if ( transform == nullptr )
                    {
                        headers.insert( header );
                    }
                    else
                    {
                        headers.insert( make_pair( header.first, transform( header.second ) ) );
                    }
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
                                                const function< string ( const string& ) >& transform ) const
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

        void RequestImpl::set_body( const shared_ptr< Bytes >& value )
        {
            m_body = value;
        }
        
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
