/*
 * Copyright (c) 2013 Corvusoft
 */

//System Includes
#include <regex>
#include <vector>
#include <sstream>

//Project Includes
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/status_code.h"
#include "corvusoft/restbed/detail/helpers/map.h"
#include "corvusoft/restbed/detail/request_impl.h"
#include "corvusoft/restbed/detail/request_builder.h"
#include "corvusoft/restbed/detail/helpers/string.h"
#include "corvusoft/restbed/detail/helpers/istream.h"

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

        void RequestBuilder::set_path_parameters( const map< string, string >& parameters )
        {
            m_pimpl->set_path_parameters( parameters );
        }

        RequestBuilder& RequestBuilder::operator =( const RequestBuilder& rhs )
        {
            *m_pimpl = *rhs.m_pimpl;

            return *this;
        }

        Bytes RequestBuilder::parse_http_body( istream& socket )
        {
            istreambuf_iterator< char > end_of_stream;

            Bytes body( istreambuf_iterator< char >( socket ), end_of_stream );

            return body;
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
