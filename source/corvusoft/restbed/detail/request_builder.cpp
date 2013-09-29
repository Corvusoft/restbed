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
#include <regex>
#include <vector>
#include <sstream>
#include <iostream> //debug

//Project Includes
#include "restbed/status_code.h"
#include "restbed/detail/helpers/map.h"
#include "restbed/request.h"
#include "restbed/detail/request_impl.h"
#include "restbed/detail/request_builder.h"
#include "restbed/detail/helpers/string.h"
#include "restbed/detail/helpers/istream.h"

//External Includes

//System Namespaces
using std::map;
using std::stod;
using std::string;
using std::vector;
using std::istream;
using std::shared_ptr;
using std::istreambuf_iterator;

//Project Namespaces
using restbed::Request;
using restbed::detail::helpers::Map;
using restbed::detail::helpers::String;
using restbed::detail::helpers::IStream;

//External Namespaces
using asio::buffer;
using asio::ip::tcp;
using asio::io_service;
using asio::error_code;
using asio::system_error;

namespace restbed
{
    namespace detail
    {
        RequestBuilder::RequestBuilder( void ) : Request( )
        {
            //n/a
        }
        
        RequestBuilder::RequestBuilder( const RequestBuilder& original ) : Request( original )
        {
            //n/a
        }
        
        RequestBuilder::~RequestBuilder( void )
        {
            //n/a
        }

        Request RequestBuilder::build( void ) const
        {
            return *this;
        }

        void RequestBuilder::parse( shared_ptr< tcp::socket >& socket )
        {
            asio::streambuf buffer;

            asio::read_until( *socket, buffer, "\r\n" );

            istream stream( &buffer );

            m_pimpl->set_method( parse_http_method( stream ) ); 
            m_pimpl->set_path( parse_http_path( stream ) );
            m_pimpl->set_query_parameters( parse_http_query_parameters( stream ) );
            m_pimpl->set_version( parse_http_version( stream ) );
            m_pimpl->set_headers( parse_http_headers( stream ) );
            m_pimpl->set_body( parse_http_body( stream ) );
        }

        void RequestBuilder::parse_path_parameters( const string& value )
        {
            string name = String::empty;
            auto definitions = String::split( value, '/' );

            auto path = String::split( get_path( ), '/' );

            for ( vector< string >::size_type index = 0; index not_eq definitions.size( ); index++ )
            {
                string definition = definitions[ index ];

                if ( definition.front( ) == '{' )
                {
                    if ( definition.back( ) == '}' )
                    { 
                        definition = String::trim( definition, "{" );
                        definition = String::trim( definition, "}" ); 
                        
                        auto segments = String::split( definition, ':' );

                        if ( segments.size( ) not_eq 2 )
                        {
                            //throw invalid_argument( String::empty );
                        }
                        
                        name = segments[ 0 ];
                        
                        definition = String::trim( segments[ 1 ] );
                    }
                }

                std::smatch match;

                if ( std::regex_search( path[ index ], match, std::regex( definition ) ) )
                {
                    std::cout << name << ": " << match[0] << std::endl;
                }
            }
        }

        double RequestBuilder::parse_http_version( istream& socket )
        {
            string version = String::empty;

            socket >> version;
            socket.ignore( 2 );

            version = String::remove( "HTTP/", version, true );

            return stod( version );
        }

        string RequestBuilder::parse_http_path( istream& socket )
        {
            string path = String::empty;

            for ( char character = socket.get( ); character not_eq ' ' and character not_eq '?'; character = socket.get( ) )
            {
                path.push_back( character );
            }

            return path;
        }

        string RequestBuilder::parse_http_body( istream& socket )
        {
            istreambuf_iterator< char > end_of_stream;

            string body( istreambuf_iterator< char >( socket ), end_of_stream );

            return body;
        }

        string RequestBuilder::parse_http_method( istream& socket )
        {
            string method = String::empty;

            socket >> method;
            socket.ignore( 1 );
            
            return method;
        }
    
        map< string, string > RequestBuilder::parse_http_headers( istream& socket )
        {
            map< string, string > headers;
                        
            string header = String::empty;
            
            while ( getline( socket, header ) and header not_eq "\r" )
            {
                header.erase( header.length( ) - 1 );
                
                string::size_type index = header.find_first_of( ':' );
                
                string name = String::trim( header.substr( 0, index ) );
                
                string value = String::trim( header.substr( index + 1 ) );
                
                headers[ name ] = value;
            }

            return headers;
        }

        map< string, string > RequestBuilder::parse_http_query_parameters( istream& socket )
        {
            map< string, string > parameters;

            char previous_byte = IStream::reverse_peek( socket );

            if ( previous_byte == '?' )
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
