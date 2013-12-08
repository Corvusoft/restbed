/*
 * Copyright (c) 2013 Corvusoft
 */

//System Includes
#include <ctime>
#include <chrono>

//Project Includes
#include "corvusoft/restbed/status_code.h"
#include "corvusoft/restbed/detail/response_impl.h"
#include "corvusoft/restbed/detail/helpers/map.h"
#include "corvusoft/restbed/detail/helpers/date.h"
#include "corvusoft/restbed/detail/helpers/string.h"

//External Includes

//System Namespaces
using std::map;
using std::string;
using std::time_t;
using std::to_string;
using std::chrono::system_clock;

//Project Namespaces
using restbed::detail::helpers::Map;
using restbed::detail::helpers::Date;
using restbed::detail::helpers::String;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        ResponseImpl::ResponseImpl( void ) : m_body( ),
                                             m_status_code( StatusCode::OK ),
                                             m_headers( )
        {
            //n/a
        }
        
        ResponseImpl::ResponseImpl( const ResponseImpl& original ) : m_body( original.m_body ),
                                                                     m_status_code( original.m_status_code ),
                                                                     m_headers( original.m_headers )
        {
            //n/a
        }
        
        ResponseImpl::~ResponseImpl( void )
        {
            //n/a
        }

        Bytes ResponseImpl::to_bytes( void ) const
        {
            string headers = String::format( "%s%s\r\n", generate_status_section( ).data( ), generate_header_section( ).data( ) );

            Bytes bytes( headers.begin( ), headers.end( ) );
            bytes.insert( bytes.end( ), m_body.begin( ), m_body.end( ) );

            return bytes;
        }

        Bytes ResponseImpl::get_body( void ) const
        {
            return m_body;
        }
         
        int ResponseImpl::get_status_code( void ) const
        {
            return m_status_code;
        }

        string ResponseImpl::get_header( const string& name ) const
        {
            string value = String::empty;
            
            if ( has_header( name ) )
            {
                const auto iterator = Map::find_key_ignoring_case( name, m_headers );

                value = iterator->second;
            }

            return value;
        }

        map< string, string > ResponseImpl::get_headers( void ) const
        {
            return m_headers;
        }
        
        void ResponseImpl::set_body( const Bytes& value )
        {
            m_body = value;
        }

        void ResponseImpl::set_body( const string& value )
        {
            m_body = Bytes( value.begin( ), value.end( ) );
        }

        void ResponseImpl::set_status_code( const int value )
        {
            m_status_code = value;
        }

        void ResponseImpl::set_header( const string& name, const string& value )
        {
            string key = String::lowercase( name );

            m_headers[ key ] = value;
        }

        void ResponseImpl::set_headers( const map< std::string, string >& values )
        {
            m_headers = values;
        }

        bool ResponseImpl::operator <( const ResponseImpl& rhs ) const
        {
            return m_status_code < rhs.m_status_code;
        }
        
        bool ResponseImpl::operator >( const ResponseImpl& rhs ) const
        {
            return m_status_code > rhs.m_status_code;
        }
        
        bool ResponseImpl::operator ==( const ResponseImpl& rhs ) const
        {
            return m_status_code == rhs.m_status_code and m_body == rhs.m_body and m_headers == rhs.m_headers;
        }
        
        bool ResponseImpl::operator !=( const ResponseImpl& rhs ) const
        {
            return not ( *this == rhs );
        }
        
        ResponseImpl& ResponseImpl::operator =( const ResponseImpl& rhs )
        {
            m_body = rhs.m_body;

            m_headers = rhs.m_headers;

            m_status_code = rhs.m_status_code;

            return *this;
        }

        bool ResponseImpl::has_header( const string& name ) const
        {
            return ( Map::find_key_ignoring_case( name, m_headers ) not_eq m_headers.end( ) );
        }

        string ResponseImpl::generate_status_section( void ) const
        {
            return String::format( "HTTP/1.1 %i %s\r\n", m_status_code, StatusCode::to_string( m_status_code ).data( ) );
        }

        string ResponseImpl::generate_header_section( void ) const
        {
            string section = generate_default_date_header( );
            section += generate_default_connection_header( );
            section += generate_default_server_header( );
            section += generate_default_content_type_header( );
            section += generate_default_content_length_header( );

            for ( auto header : m_headers )
            {
                section += String::format( "%s: %s\r\n", header.first.data( ), header.second.data( ) );
            }

            return section;
        }

        string ResponseImpl::generate_default_date_header( void ) const
        {
            string header = String::empty;

            if ( not has_header( "Date" ) )
            {
                string date = Date::format( system_clock::now( ) );

                header = String::format( "Date: %s\r\n", date.data( ) );
            }

            return header;
        }

        string ResponseImpl::generate_default_server_header( void ) const
        {
            string header = String::empty;

            if ( not has_header( "Server" ) )
            {
                header = "Server: Corvusoft - restbed/1.0\r\n";
            }

            return header;
        }
        
        string ResponseImpl::generate_default_connection_header( void ) const
        {
            string header = String::empty;

            if ( not has_header( "Connection" ) )
            {
                header = "Connection: close\r\n";
            }

            return header;
        }

        string ResponseImpl::generate_default_content_type_header( void ) const
        {
            string header = String::empty;

            if ( not has_header( "Content-Type" ) )
            {
                header = "Content-Type: application/json; charset=utf-8\r\n";
            }

            return header;
        }

        string ResponseImpl::generate_default_content_length_header( void ) const
        {
            string header = String::empty;

            if ( not has_header( "Content-Length" ) )
            {
                header = String::format( "Content-Length: %i\r\n", m_body.size( ) );
            }

            return header;
        }
    }
}
