/*
 * Site: restbed.corvusoft.co.uk
 * Author: Ben Crowhurst
 *
 * Copyright (c) 2013 Restbed Core Development Team and Community Contributors
 *
 * This file is part of Restbed.
 *
 * Restbed is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Restbed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with Restbed.  If not, see <http://www.gnu.org/licenses/>.
 */

//System Includes
#include <sstream>

//Project Includes
#include "restbed/string.h"
#include "restbed/status_code.h"
#include "restbed/detail/request_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::stod;
using std::string;
using std::istream;
using std::istreambuf_iterator;

//Project Namespaces
using restbed::detail::RequestImpl;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        RequestImpl::RequestImpl( void ) : m_version( 1.1 ),
                                           m_path( String::empty ),
                                           m_body( String::empty ),
                                           m_method( String::empty ),
                                           m_headers( ),
                                           m_path_parameters( ),
                                           m_query_parameters( )
        {
            //n/a
        }
        
        RequestImpl::RequestImpl( const RequestImpl& original ) : m_version( original.m_version ),
                                                                  m_path( original.m_path ),
                                                                  m_body( original.m_body ),
                                                                  m_method( original.m_method ),
                                                                  m_headers( original.m_headers ),
                                                                  m_path_parameters( original.m_path_parameters ),
                                                                  m_query_parameters( original.m_query_parameters )
        {
            //n/a
        }
        
        RequestImpl::~RequestImpl( void )
        {
            //n/a
        }

        RequestImpl RequestImpl::parse( istream& socket )
        {
            RequestImpl pimpl;

            string method = parse_http_method( socket );
            pimpl.set_method( method ); 

            string path = parse_http_path( socket );
            pimpl.set_path( path );

            auto query_parameters = parse_http_query_parameters( socket );
            pimpl.set_query_parameters( query_parameters );

            double version = parse_http_version( socket );
            pimpl.set_version( version );

            auto headers = parse_http_headers( socket );
            pimpl.set_headers( headers );

            string body = parse_http_body( socket );
            pimpl.set_body( body );

            return pimpl;
        }
        
        double RequestImpl::get_version( void ) const
        {
            return m_version;
        }

        string RequestImpl::get_path( void ) const
        {
            return m_path;
        }
        
        string RequestImpl::get_body( void ) const
        {
            return m_body;
        }

        string RequestImpl::get_method( void ) const
        {
            return m_method;
        }
        
        string RequestImpl::get_header( const string& name ) const
        {
            return m_headers.at( name );
        }
        
        map< string, string > RequestImpl::get_headers( void ) const
        {
            return m_headers;
        }
        
        string RequestImpl::get_query_parameter( const string& name ) const
        {
            return m_query_parameters.at( name );
        }
        
        map< string, string > RequestImpl::get_query_parameters( void ) const
        {
            return m_query_parameters;
        }
        
        string RequestImpl::get_path_parameter( const string& name ) const
        {
            return m_path_parameters.at( name );
        }
        
        map< string, string > RequestImpl::get_path_parameters( void ) const
        {
            return m_path_parameters;
        }

        void RequestImpl::set_version( const double value )
        {
            if ( value not_eq 1.0 and value not_eq 1.1 )
            {
                throw StatusCode::HTTP_VERSION_NOT_SUPPORTED;
            }

            m_version = value;
        }
        
        void RequestImpl::set_path( const string& value )
        {
            m_path = value;
        }
        
        void RequestImpl::set_body( const string& value )
        {
            m_body = value;
        }

        void RequestImpl::set_method( const string& value )
        {
            m_method = value;
        }
        
        void RequestImpl::set_headers( const map< string, string >& value )
        {
            m_headers = value;
        }

        void RequestImpl::set_path_parameter( const string& name, const string& value )
        {
            m_path_parameters[ name ] = value;
        }
        
        void RequestImpl::set_query_parameters( const map< string, string >& value )
        {
            m_query_parameters = value;
        }

        bool RequestImpl::operator <( const RequestImpl& rhs ) const
        {
            return m_path < rhs.m_path;
        }
        
        bool RequestImpl::operator >( const RequestImpl& rhs ) const
        {
            return m_path > rhs.m_path;
        }
        
        bool RequestImpl::operator ==( const RequestImpl& rhs ) const
        {
            return m_path == rhs.m_path;
        }
        
        bool RequestImpl::operator !=( const RequestImpl& rhs ) const
        {
            return m_path not_eq rhs.m_path;
        }
        
        RequestImpl& RequestImpl::operator =( const RequestImpl& rhs )
        {
            m_path = rhs.m_path;
                                
            m_method = rhs.m_method;
            
            m_version = rhs.m_version;
            
            m_headers = rhs.m_headers;
            
            m_path_parameters = rhs.m_path_parameters;
            
            m_query_parameters = rhs.m_query_parameters;

            return *this;
        }

        char RequestImpl::reverse_peek( istream& socket ) //restbed::istream::reverse_peek
        {
            socket.unget( );

            char previous_byte = socket.get( );

            return previous_byte;
        }

        double RequestImpl::parse_http_version( istream& socket )
        {
            string version = String::empty;

            socket >> version;
            socket.ignore( 2 ); //ignore carriage return-line feed sequence.

            version = String::remove( "HTTP/", version, true );

            return stod( version );
        }

        string RequestImpl::parse_http_path( istream& socket )
        {
            string path = String::empty;

            for ( char character = socket.get( ); character not_eq ' ' and character not_eq '?'; character = socket.get( ) )
            {
                path.push_back( character );
            }

            return path;
        }

        string RequestImpl::parse_http_body( istream& socket )
        {
            istreambuf_iterator< char > end_of_stream;

            string body( istreambuf_iterator< char >( socket ), end_of_stream );

            return body;
        }

        string RequestImpl::parse_http_method( istream& socket )
        {
            string method = String::empty;

            socket >> method;
            socket.ignore( 1 );  //ignore whitespace character.
            
            return method;
        }
    
        map< string, string > RequestImpl::parse_http_headers( istream& socket )
        {
            map< string, string > headers;

            const char* CR = "\r";
            
            string header = String::empty;
            
            while ( getline( socket, header ) && header not_eq CR )
            {
                header.erase( header.length( ) - 1 ); //erase carriage return.
                
                string::size_type index = header.find_first_of( ':' );
                
                string name = String::trim( header.substr( 0, index ) );
                
                string value = String::trim( header.substr( index + 1 ) );
                
                headers[ name ] = value;
            }

            return headers;
        }

        map< string, string > RequestImpl::parse_http_query_parameters( istream& socket )
        {
            map< string, string > parameters;

            if ( reverse_peek( socket ) == '?' )
            {
                string query_string = String::empty;

                socket >> query_string;

                const auto& query = String::split( query_string, '&' );

                for ( const auto& parameter : query )
                {
                    string::size_type index = parameter.find_first_of( '=' );
                    
                    string name = parameter.substr( 0, index );
                    
                    string value = parameter.substr( index + 1, parameter.length( ) );

                    parameters[ name ] = value;
                }
            }

            return parameters;
        }
    }
}
