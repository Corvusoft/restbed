/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/status_code.h"
#include "corvusoft/restbed/detail/response_impl.h"

//External Includes
#include <corvusoft/framework/map>
#include <corvusoft/framework/string>

//System Namespaces
using std::string;
using std::function;
using std::multimap;

//Project Namespaces

//External Namespaces
using framework::Map;
using framework::Bytes;
using framework::String;

namespace restbed
{
    namespace detail
    {
        ResponseImpl::ResponseImpl( void ) : m_body( ),
            m_body_callback( ),
            m_version( 1.1 ),
            m_status_code( StatusCode::OK ),
            m_status_message( String::empty ),
            m_headers( )
        {
            return;
        }
        
        ResponseImpl::ResponseImpl( const ResponseImpl& original ) : m_body( original.m_body ),
            m_body_callback( original.m_body_callback ),
            m_version( original.m_version ),
            m_status_code( original.m_status_code ),
            m_status_message( original.m_status_message ),
            m_headers( original.m_headers )
        {
            return;
        }
        
        ResponseImpl::~ResponseImpl( void )
        {
            return;
        }

        bool ResponseImpl::has_header( const string& name ) const
        {
            return ( Map::find_ignoring_case( name, m_headers ) not_eq m_headers.end( ) );
        }
        
        Bytes ResponseImpl::get_body( void ) const
        {
            return m_body;
        }

        function< Bytes ( void ) > ResponseImpl::get_body_callback( void ) const
        {
            return m_body_callback;
        }

        double ResponseImpl::get_version( void ) const
        {
            return m_version;
        }
        
        int ResponseImpl::get_status_code( void ) const
        {
            return m_status_code;
        }
        
        string ResponseImpl::get_status_message( void ) const
        {
            string status_message = m_status_message;

            if ( m_status_message.empty( ) )
            {
                status_message = StatusCode::to_string( m_status_code );
            }

            return status_message;
        }
        
        string ResponseImpl::get_header( const string& name ) const
        {
            string value = String::empty;
            
            if ( has_header( name ) )
            {
                const auto iterator = Map::find_ignoring_case( name, m_headers );
                
                value = iterator->second;
            }
            
            return value;
        }

        multimap< string, string > ResponseImpl::get_headers( void ) const
        {
            return m_headers;
        }

        multimap< string, string > ResponseImpl::get_headers( const string& name ) const
        {
            multimap< string, string > headers;

            auto key = String::lowercase( name );

            for ( auto header : m_headers )
            {
                if ( String::lowercase( header.first ) == key )
                {
                    headers.insert( header );
                }
            }

            return headers;
        }

        void ResponseImpl::set_body( const string& value )
        {
            m_body = Bytes( value.begin( ), value.end( ) );
        }
        
        void ResponseImpl::set_body( const Bytes& value )
        {
            m_body = value;
        }

        void ResponseImpl::set_body_callback( const function< Bytes ( void ) >& value )
        {
            m_body_callback = value;
        }
        
        void ResponseImpl::set_version( const double value )
        {
            m_version = value;
        }
        
        void ResponseImpl::set_status_code( const int value )
        {
            m_status_code = value;
        }
        
        void ResponseImpl::set_status_message( const string& value )
        {
            m_status_message = value;
        }
        
        void ResponseImpl::set_header( const string& name, const string& value )
        {
            if ( has_header( name ) )
            {
                const auto iterator = Map::find_ignoring_case( name, m_headers );

                iterator->second = value;
            }
            else
            {
                m_headers.insert( make_pair( name, value ) );
            }
        }
        
        void ResponseImpl::set_headers( const multimap< string, string >& values )
        {
            m_headers = values;
        }
        
        bool ResponseImpl::operator <( const ResponseImpl& value ) const
        {
            return m_status_code < value.m_status_code;
        }
        
        bool ResponseImpl::operator >( const ResponseImpl& value ) const
        {
            return m_status_code > value.m_status_code;
        }
        
        bool ResponseImpl::operator ==( const ResponseImpl& value ) const
        {
            return m_status_code == value.m_status_code and m_body == value.m_body and m_headers == value.m_headers;
        }
        
        bool ResponseImpl::operator !=( const ResponseImpl& value ) const
        {
            return not ( *this == value );
        }
        
        ResponseImpl& ResponseImpl::operator =( const ResponseImpl& value )
        {
            m_body = value.m_body;

            m_body_callback = value.m_body_callback;
            
            m_version = value.m_version;
            
            m_status_code = value.m_status_code;
            
            m_status_message = value.m_status_message;
            
            m_headers = value.m_headers;
            
            return *this;
        }
    }
}
