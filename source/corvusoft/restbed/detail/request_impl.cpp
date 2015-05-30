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
        RequestImpl::RequestImpl( void ) :
            m_version( 1.1 ),
            m_path( "/" ),
            m_method( "GET" ),
            m_protocol( "HTTP" ),
            m_body( nullptr ),
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

        const string RequestImpl::get_path( const function< string ( const string& ) >& transform ) const
        {
            if ( transform not_eq nullptr )
            {
                return transform( m_path );
            }

            return m_path;
        }

        const string RequestImpl::get_method( const function< string ( const string& ) >& transform ) const
        {
            if ( transform not_eq nullptr )
            {
                return transform( m_method );
            }

            return m_method;
        }

        const string RequestImpl::get_protocol( const function< string ( const string& ) >& transform ) const
        {
            if ( transform not_eq nullptr )
            {
                return transform( m_protocol );
            }

            return m_protocol;
        }

        const shared_ptr< Bytes > RequestImpl::get_body( const function< shared_ptr< Bytes > ( const shared_ptr< Bytes >& ) >& transform ) const
        {
            if ( transform not_eq nullptr )
            {
                return transform( m_body );
            }

            return m_body;
        }

        void RequestImpl::get_header( const string& name, int& value, const int default_value, const function< string ( const string& ) >& transform ) const
        {
            if ( not has_header( name ) )
            {
                value = default_value;
                return;
            }

            string header = get_header( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                header = transform( header );
            }

            value = stoi( header );
        }

        void RequestImpl::get_header( const string& name, unsigned int& value, const unsigned int default_value, const function< string ( const string& ) >& transform ) const
        {
            if ( not has_header( name ) )
            {
                value = default_value;
                return;
            }

            string header = get_header( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                header = transform( header );
            }

            value = stoul( header );
        }

        void RequestImpl::get_header( const string& name, long& value, const long default_value, const function< string ( const string& ) >& transform ) const
        {
            if ( not has_header( name ) )
            {
                value = default_value;
                return;
            }

            string header = get_header( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                header = transform( header );
            }

            value = stol( header );
        }

        void RequestImpl::get_header( const string& name, unsigned long& value, const unsigned long default_value, const function< string ( const string& ) >& transform ) const
        {
            if ( not has_header( name ) )
            {
                value = default_value;
                return;
            }

            string header = get_header( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                header = transform( header );
            }

            value = stoul( header );
        }

        void RequestImpl::get_header( const string& name, float& value, const float default_value, const function< string ( const string& ) > transform ) const
        {
            if ( not has_header( name ) )
            {
                value = default_value;
                return;
            }

            string header = get_header( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                header = transform( header );
            }

            value = stof( header );
        }

        void RequestImpl::get_header( const string& name, double& value, const double default_value, const function< string ( const string& ) >& transform ) const
        {
            if ( not has_header( name ) )
            {
                value = default_value;
                return;
            }

            string header = get_header( name, String::empty, nullptr );

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

            for ( const auto& header : m_headers )
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

        void RequestImpl::get_query_parameter( const string& name, int& value, const int default_value, const function< string ( const string& ) >& transform ) const
        {
            if ( not has_query_parameter( name, true ) )
            {
                value = default_value;
                return;
            }

            string parameter = get_query_parameter( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                parameter = transform( parameter );
            }

            value = stoi( parameter );
        }

        void RequestImpl::get_query_parameter( const string& name, unsigned int& value, const unsigned int default_value, const function< string ( const string& ) >& transform ) const
        {
            if ( not has_query_parameter( name, true ) )
            {
                value = default_value;
                return;
            }

            string parameter = get_query_parameter( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                parameter = transform( parameter );
            }

            value = stoul( parameter );
        }

        void RequestImpl::get_query_parameter( const string& name, long& value, const long default_value, const function< string ( const string& ) >& transform ) const
        {
            if ( not has_query_parameter( name, true ) )
            {
                value = default_value;
                return;
            }

            string parameter = get_query_parameter( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                parameter = transform( parameter );
            }

            value = stol( parameter );
        }

        void RequestImpl::get_query_parameter( const string& name, unsigned long& value, const unsigned long default_value, const function< string ( const string& ) >& transform ) const
        {
            if ( not has_query_parameter( name, true ) )
            {
                value = default_value;
                return;
            }

            string parameter = get_query_parameter( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                parameter = transform( parameter );
            }

            value = stoul( parameter );
        }

        void RequestImpl::get_query_parameter( const string& name, float& value, const float default_value, const function< string ( const string& ) > transform ) const
        {
            if ( not has_query_parameter( name, true ) )
            {
                value = default_value;
                return;
            }

            string parameter = get_query_parameter( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                parameter = transform( parameter );
            }

            value = stof( parameter );
        }

        void RequestImpl::get_query_parameter( const string& name, double& value, const double default_value, const function< string ( const string& ) >& transform ) const
        {
            if ( not has_query_parameter( name, true ) )
            {
                value = default_value;
                return;
            }

            string parameter = get_query_parameter( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                parameter = transform( parameter );
            }

            value = stod( parameter );
        }

        string RequestImpl::get_query_parameter( const string& name, const string& default_value, const function< string ( const string& ) >& transform ) const
        {
            string value = default_value;

            const auto parameters = get_query_parameters( name, transform );

            if ( parameters.size( ) not_eq 0 )
            {
                value = parameters.begin( )->second;
            }

            return value;
        }

        multimap< string, string > RequestImpl::get_query_parameters( const string& name, const function< string ( const string& ) >& transform ) const
        {
            multimap< string, string > parameters;

            for ( const auto& parameter : m_query_parameters )
            {
                if ( parameter.first == name )
                {
                    if ( transform == nullptr )
                    {
                        parameters.insert( parameter );
                    }
                    else
                    {
                        parameters.insert( make_pair( parameter.first, transform( parameter.second ) ) );
                    }
                }
            }

            return parameters;
        }

        void RequestImpl::get_path_parameter( const string& name, int& value, const int default_value, const function< string ( const string& ) >& transform ) const
        {
            if ( not has_path_parameter( name, true ) )
            {
                value = default_value;
                return;
            }

            string parameter = get_path_parameter( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                parameter = transform( parameter );
            }

            value = stoi( parameter );
        }

        void RequestImpl::get_path_parameter( const string& name, unsigned int& value, const unsigned int default_value, const function< string ( const string& ) >& transform ) const
        {
            if ( not has_path_parameter( name, true ) )
            {
                value = default_value;
                return;
            }

            string parameter = get_path_parameter( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                parameter = transform( parameter );
            }

            value = stoul( parameter );
        }

        void RequestImpl::get_path_parameter( const string& name, long& value, const long default_value, const function< string ( const string& ) >& transform ) const
        {
            if ( not has_path_parameter( name, true ) )
            {
                value = default_value;
                return;
            }

            string parameter = get_path_parameter( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                parameter = transform( parameter );
            }

            value = stol( parameter );
        }

        void RequestImpl::get_path_parameter( const string& name, unsigned long& value, const unsigned long default_value, const function< string ( const string& ) >& transform ) const
        {
            if ( not has_path_parameter( name, true ) )
            {
                value = default_value;
                return;
            }

            string parameter = get_path_parameter( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                parameter = transform( parameter );
            }

            value = stoul( parameter );
        }

        void RequestImpl::get_path_parameter( const string& name, float& value, const float default_value, const function< string ( const string& ) > transform ) const
        {
            if ( not has_path_parameter( name, true ) )
            {
                value = default_value;
                return;
            }

            string parameter = get_path_parameter( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                parameter = transform( parameter );
            }

            value = stof( parameter );
        }

        void RequestImpl::get_path_parameter( const string& name, double& value, const double default_value, const function< string ( const string& ) >& transform ) const
        {
            if ( not has_path_parameter( name, true ) )
            {
                value = default_value;
                return;
            }

            string parameter = get_path_parameter( name, String::empty, nullptr );

            if ( transform not_eq nullptr )
            {
                parameter = transform( parameter );
            }

            value = stod( parameter );
        }

        string RequestImpl::get_path_parameter( const string& name, const string& default_value, const function< string ( const string& ) >& transform ) const
        {
            string value = default_value;

            const auto parameters = get_path_parameters( name, transform );

            if ( parameters.size( ) not_eq 0 )
            {
                value = parameters.begin( )->second;
            }

            return value;
        }

        map< string, string > RequestImpl::get_path_parameters( const string& name, const function< string ( const string& ) >& transform ) const
        {
            map< string, string > parameters;

            for ( const auto& parameter : m_path_parameters )
            {
                if ( parameter.first == name )
                {
                    if ( transform == nullptr )
                    {
                        parameters.insert( parameter );
                    }
                    else
                    {
                        parameters.insert( make_pair( parameter.first, transform( parameter.second ) ) );
                    }
                }
            }

            return parameters;
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

        void RequestImpl::set_body( const shared_ptr< Bytes >& value )
        {
            m_body = value;
        }

        void RequestImpl::set_headers( const multimap< string, string >& values )
        {
            m_headers = values;
        }

        void RequestImpl::set_path_parameter( const string& name, const string& value )
        {
            m_path_parameters.insert( make_pair( name, value ) );
        }

        void RequestImpl::set_query_parameters( const multimap< string, string >& values )
        {
            m_query_parameters = values;
        }
    }
}
