/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <regex>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>

#if defined(_WIN32)
    #include <ciso646>
    #include <winsock2.h>
    #pragma comment( lib, "Ws2_32.lib" )
#else
    #include <netdb.h>
    #include <unistd.h>
    #include <arpa/inet.h>
#endif

//Project Includes
#include "corvusoft/restbed/uri.hpp"
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/detail/uri_impl.hpp"

//External Includes

//System Namespaces
using std::stoi;
using std::regex;
using std::smatch;
using std::strtol;
using std::string;
using std::multimap;
using std::snprintf;
using std::to_string;
using std::unique_ptr;
using std::runtime_error;
using std::invalid_argument;

//Project Namespaces
using restbed::detail::UriImpl;

//External Namespaces

namespace restbed
{
    Uri::Uri( const string& value, bool relative ) : m_pimpl( new UriImpl )
    {
        if ( not is_valid( value ) )
        {
            throw invalid_argument( "Argument is not a valid URI: " + value );
        }
        
        m_pimpl->m_uri = value;
        m_pimpl->m_relative = relative;
    }
    
    Uri::Uri( const Uri& original ) : m_pimpl( new UriImpl( *original.m_pimpl ) )
    {
        return;
    }
    
    Uri::~Uri( void )
    {
        return;
    }
    
    bool Uri::is_relative( void ) const
    {
        return m_pimpl->m_relative;
    }
    
    bool Uri::is_absolute( void ) const
    {
        return not m_pimpl->m_relative;
    }
    
    string Uri::to_string( void ) const
    {
        return m_pimpl->m_uri;
    }
    
    bool Uri::is_valid( const string& value )
    {
        static const regex pattern( "^[a-zA-Z][a-zA-Z0-9+\\-.]*://(([a-zA-Z0-9\\-._~%!$&'()*+,;=]+)(:([a-zA-Z0-9\\-._~%!$&'()*+,;=]+))?@)?([a-zA-Z0-9\\-._~%!$&'()*+,;=:\\[\\]]*(:[0-9]+)?)?[a-zA-Z0-9\\-._~%!$&'()*+,;=:@/]+(\\?[a-zA-Z0-9\\-._~%!$&'()*+,;=:@/]*)?(#[a-zA-Z0-9\\-._~%!$&'()*+,;=:@/?]*)?$" );
        
        return regex_match( value, pattern );
    }
    
    Uri Uri::parse( const string& value )
    {
        return Uri( value );
    }
    
    string Uri::decode( const Bytes& value )
    {
        return decode( string( value.begin( ), value.end( ) ) );
    }
    
    string Uri::decode( const string& value )
    {
        string result = String::empty;
        
        for ( string::size_type index = 0; index not_eq value.length( ); index++ )
        {
            if ( value[ index ] == '%' )
            {
                char hexidecimal[ 3 ] = { 0 };
                hexidecimal[ 0 ] = value[ ++index ];
                hexidecimal[ 1 ] = value[ ++index ];
                
                char byte = static_cast< char >( strtol( hexidecimal, nullptr, 16 ) );
                result.push_back( byte );
            }
            else
            {
                result.push_back( value[ index ] );
            }
        }
        
        return result;
    }
    
    string Uri::decode_parameter( const string& value )
    {
        return decode( String::replace( "+", " ", value ) );
    }
    
    string Uri::encode( const Bytes& value )
    {
        string encoded = String::empty;
        
        for ( Byte character : value )
        {
            char hexidecimal[ 4 ] = { 0 };
            
            switch ( character )
            {
                //unsafe carachters
                case ' ':
                case '\"':
                case '<':
                case '>':
                case '#':
                case '%':
                case '{':
                case '}':
                case '|':
                case '\\':
                case '^':
                case '~':
                case '[':
                case ']':
                case '`':
                
                //reserved characters
                case '$':
                case '&':
                case '+':
                case ',':
                case '/':
                case ':':
                case ';':
                case '=':
                case '?':
                case '@':
                    snprintf( hexidecimal, sizeof( hexidecimal ), "%%%02X", character );
                    encoded.append( hexidecimal );
                    break;
                    
                default:
                    hexidecimal[ 0 ] = character;
                    encoded.append( hexidecimal );
                    break;
            }
        }
        
        return encoded;
    }
    
    string Uri::encode( const string& value )
    {
        return encode( Bytes( value.begin( ), value.end( ) ) );
    }
    
    string Uri::encode_parameter( const string& value )
    {
        return encode( value );
    }
    
    uint16_t Uri::get_port( void ) const
    {
        smatch match;
        string port = String::empty;
        static const regex pattern( "^[a-zA-Z][a-zA-Z0-9+\\-.]*://(([a-zA-Z0-9\\-._~%!$&'()*+,;=]+)(:([a-zA-Z0-9\\-._~%!$&'()*+,;=]+))?@)?([a-zA-Z0-9\\-._~%]+|\\[[a-zA-Z0-9\\-._~%!$&'()*+,;=:]+\\]):([0-9]+)" );
        
        if ( regex_search( m_pimpl->m_uri, match, pattern ) )
        {
            port = match[ 6 ];
        }
        else
        {
            const auto scheme = get_scheme( );
            
            if ( not scheme.empty( ) )
            {
                const struct servent* entry = getservbyname( scheme.data( ), nullptr );
                
                if ( entry not_eq nullptr )
                {
                    port = ::to_string( ntohs( entry->s_port ) );
                }
            }
        }
        
        if ( port.empty( ) )
        {
            return 0;
        }
        
        return static_cast< uint16_t >( stoi( port ) );
    }
    
    string Uri::get_path( void ) const
    {
        static const regex pattern( "^([a-zA-Z][a-zA-Z0-9+\\-.]*://([^/?#]+)?)?([a-zA-Z0-9\\-._~%!$&'()*+,;=:@/]*)" );
        
        smatch match;
        
        if ( regex_search( m_pimpl->m_uri, match, pattern ) )
        {
            return ( is_absolute( ) ) ? match[ 3 ] : string( match[ 2 ] ) + string( match[ 3 ] );
        }
        
        return String::empty;
    }
    
    string Uri::get_query( void ) const
    {
        smatch match;
        static const regex pattern( "^[^?#]+\\?([^#]+)" );
        
        if ( regex_search( m_pimpl->m_uri, match, pattern ) )
        {
            return match[ 1 ];
        }
        
        return String::empty;
    }
    
    string Uri::get_scheme( void ) const
    {
        smatch match;
        static const regex pattern( "^([a-zA-Z][a-zA-Z0-9+\\-.]*):" );
        
        if ( regex_search( m_pimpl->m_uri, match, pattern ) )
        {
            return match[ 1 ];
        }
        
        return String::empty;
    }
    
    string Uri::get_fragment( void ) const
    {
        smatch match;
        static const regex pattern( "#(.+)" );
        
        if ( regex_search( m_pimpl->m_uri, match, pattern ) )
        {
            return match[ 1 ];
        }
        
        return String::empty;
    }
    
    string Uri::get_username( void ) const
    {
        smatch match;
        static const regex pattern( "^[a-zA-Z0-9+\\-.]+://([a-zA-Z0-9\\-._~%!$&'()*+,;=]+)(:([a-zA-Z0-9\\-._~%!$&'()*+,;=]+))?@" );
        
        if ( regex_search( m_pimpl->m_uri, match, pattern ) )
        {
            return match[ 1 ];
        }
        
        return String::empty;
    }
    
    string Uri::get_password( void ) const
    {
        smatch match;
        static const regex pattern( "^[a-zA-Z0-9+\\-.]+://([a-zA-Z0-9\\-._~%!$&'()*+,;=]+):([a-zA-Z0-9\\-._~%!$&'()*+,;=]+)@" );
        
        if ( regex_search( m_pimpl->m_uri, match, pattern ) )
        {
            return match[ 2 ];
        }
        
        return String::empty;
    }
    
    string Uri::get_authority( void ) const
    {
        if ( is_relative( ) )
        {
            return String::empty;
        }
        
        smatch match;
        static const regex pattern( "^[a-zA-Z][a-zA-Z0-9+\\-.]*://(([a-zA-Z0-9\\-._~%!$&'()*+,;=]+)(:([a-zA-Z0-9\\-._~%!$&'()*+,;=]+))?@)?([a-zA-Z0-9\\-._~%]+|\\[[a-zA-Z0-9\\-._~%!$&'()*+,;=:]+\\])" );
        
        if ( regex_search( m_pimpl->m_uri, match, pattern ) )
        {
            return match[ 5 ];
        }
        
        return String::empty;
    }
    
    multimap< string, string > Uri::get_query_parameters( void ) const
    {
        multimap< string, string > parameters;
        
        auto query = String::split( get_query( ), '&' );
        
        for ( auto parameter : query )
        {
            auto index = parameter.find_first_of( '=' );
            auto name = decode_parameter( parameter.substr( 0, index ) );
            auto value = decode_parameter( parameter.substr( index + 1, parameter.length( ) ) );
            
            parameters.insert( make_pair( name, value ) );
        }
        
        return parameters;
    }
    
    Uri& Uri::operator =( const Uri& rhs )
    {
        m_pimpl->m_uri = rhs.m_pimpl->m_uri;
        return *this;
    }
    
    bool Uri::operator <( const Uri& rhs ) const
    {
        return m_pimpl->m_uri < rhs.m_pimpl->m_uri;
    }
    
    bool Uri::operator >( const Uri& rhs ) const
    {
        return m_pimpl->m_uri > rhs.m_pimpl->m_uri;
    }
    
    bool Uri::operator ==( const Uri& rhs ) const
    {
        return m_pimpl->m_uri == rhs.m_pimpl->m_uri;
    }
    
    bool Uri::operator !=( const Uri& rhs ) const
    {
        return m_pimpl->m_uri not_eq rhs.m_pimpl->m_uri;
    }
    
    Uri::Uri( void ) : m_pimpl( new UriImpl )
    {
        return;
    }
}
