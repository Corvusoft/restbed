/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <regex>
#include <vector>
#include <sstream>

//Project Includes
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/status_code.h"
#include "corvusoft/restbed/detail/request_impl.h"
#include "corvusoft/restbed/detail/request_builder_impl.h"

//External Includes
#include <corvusoft/framework/uri>
#include <corvusoft/framework/map>
#include <corvusoft/framework/string>
#include <corvusoft/framework/istream>

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

//External Namespaces
using framework::Uri;
using framework::Map;
using framework::Bytes;
using framework::String;
using framework::IStream;

namespace restbed
{
    namespace detail
    {
        RequestBuilderImpl::RequestBuilderImpl( istream& socket ) : Request( )
        {
            parse( socket );
        }
        
        RequestBuilderImpl::RequestBuilderImpl( const RequestBuilderImpl& original ) : Request( original )
        {
            //n/a
        }
        
        RequestBuilderImpl::~RequestBuilderImpl( void )
        {
            //n/a
        }
        
        Request RequestBuilderImpl::build( void ) const
        {
            return *this;
        }
        
        void RequestBuilderImpl::parse( istream& socket )
        {
            m_pimpl->set_method( parse_http_method( socket ) );
            m_pimpl->set_path( parse_http_path( socket ) );
            m_pimpl->set_query_parameters( parse_http_query_parameters( socket ) );
            m_pimpl->set_version( parse_http_version( socket ) );
            m_pimpl->set_headers( parse_http_headers( socket ) );
            m_pimpl->set_body( parse_http_body( socket ) );
        }
        
        void RequestBuilderImpl::set_origin( const string& value )
        {
            m_pimpl->set_origin( value );
        }
        
        void RequestBuilderImpl::set_path_parameters( const map< string, string >& parameters )
        {
            m_pimpl->set_path_parameters( parameters );
        }
        
        RequestBuilderImpl& RequestBuilderImpl::operator =( const RequestBuilderImpl& rhs )
        {
            *m_pimpl = *rhs.m_pimpl;
            
            return *this;
        }
        
        Bytes RequestBuilderImpl::parse_http_body( istream& socket )
        {
            istreambuf_iterator< char > end_of_stream;
            
            Bytes body( istreambuf_iterator< char >( socket ), end_of_stream );
            
            return body;
        }
        
        double RequestBuilderImpl::parse_http_version( istream& socket )
        {
            string version = String::empty;
            
            socket >> version;
            socket.ignore( 2 );
            
            version = String::remove( "HTTP/", version, true );
            
            return stod( version );
        }
        
        string RequestBuilderImpl::parse_http_path( istream& socket )
        {
            string path = String::empty;
            
            for ( char character = socket.get( ); character not_eq ' ' and character not_eq '?'; character = socket.get( ) )
            {
                path.push_back( character );
            }
            
            return Uri::decode( path );
        }
        
        string RequestBuilderImpl::parse_http_method( istream& socket )
        {
            string method = String::empty;
            
            socket >> method;
            socket.ignore( 1 );
            
            return method;
        }
        
        map< string, string > RequestBuilderImpl::parse_http_headers( istream& socket )
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
        
        map< string, string > RequestBuilderImpl::parse_http_query_parameters( istream& socket )
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
                    
                    string name = Uri::decode_parameter( parameter.substr( 0, index ) );
                    
                    string value = Uri::decode_parameter( parameter.substr( index + 1, parameter.length( ) ) );
                    
                    parameters[ name ] = value;
                }
            }
            
            return parameters;
        }
    }
}
