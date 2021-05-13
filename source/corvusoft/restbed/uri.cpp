/*
 * Copyright 2013-2020, Corvusoft Ltd, All Rights Reserved.
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
        static const char hex_to_dec[256] = 
        {
            /*       0  1  2  3   4  5  6  7   8  9  A  B   C  D  E  F */
            /* 0 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
            /* 1 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
            /* 2 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
            /* 3 */  0, 1, 2, 3,  4, 5, 6, 7,  8, 9,-1,-1, -1,-1,-1,-1,
            
            /* 4 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
            /* 5 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
            /* 6 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
            /* 7 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
            
            /* 8 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
            /* 9 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
            /* A */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
            /* B */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
            
            /* C */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
            /* D */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
            /* E */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
            /* F */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1
        };

        if( value.size( ) < 3 ) {
            return value;
        }

        string::size_type valuesize = value.size( );
        
        string result;
        result.reserve( valuesize );

        char c1 = 0;
        char c2 = 0;
        unsigned char cindex = 0;
        
        string::size_type index = 0;
        for ( ; index < ( valuesize - 2 ); index++ )
        {
            if ( value[index] == '%' )
            {
                cindex = value[ index + 1 ];
                c1 = hex_to_dec[ cindex ];

                cindex = value[ index + 2 ];
                c2 = hex_to_dec[ cindex ];
                if ( c1 != -1 && c2 != -1 )
                {
                    result.push_back( ( c1 << 4 ) + c2 );
                    index += 2;
                    continue;
                }
            }
            result.push_back( value[ index ] );
        }

        for ( ; index < valuesize; index++ )
        {
            result.push_back( value[ index ] );
        }
        
        return result;
    }
    
    string Uri::decode_parameter( const string& value )
    {
        return decode( String::replace( "+", " ", value ) );
    }
    
    string Uri::encode( const Bytes& value )
    {
        const bool unsafe_carachters[256] =
        {
            /*      0 1 2 3  4 5 6 7  8 9 A B  C D E F */
            /* 0 */ 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 
            /* 1 */ 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 
            /* 2 */ 1,0,1,1, 1,1,1,0, 0,0,0,1, 1,0,0,1, 
            /* 3 */ 0,0,0,0, 0,0,0,0, 0,0,1,1, 1,1,1,1, 
            /* 4 */ 1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
            /* 5 */ 0,0,0,0, 0,0,0,0, 0,0,0,1, 1,1,1,0, 
            /* 6 */ 1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
            /* 7 */ 0,0,0,0, 0,0,0,0, 0,0,0,1, 1,1,0,1, 
            /* 8 */ 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 
            /* 9 */ 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 
            /* A */ 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 
            /* B */ 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 
            /* C */ 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 
            /* D */ 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 
            /* E */ 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 
            /* F */ 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1
        };
        static const char dec_to_hex[] = "0123456789ABCDEF";

        string encoded;
        encoded.reserve( value.size() );

        for ( Byte character : value )
        {
            if ( unsafe_carachters[ character ] )
            {
                encoded.push_back( '%' );
                encoded.push_back( dec_to_hex[ character >> 4 ] );
                encoded.push_back( dec_to_hex[ character & 0x0F ]);
            }
            else
            {
                encoded.push_back( character );
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
        string authority = String::empty;
        if ( is_relative( ) ) return authority;
        
        smatch match;
        static const regex pattern( "^[a-zA-Z][a-zA-Z0-9+\\-.]*://(([a-zA-Z0-9\\-._~%!$&'()*+,;=]+)(:([a-zA-Z0-9\\-._~%!$&'()*+,;=]+))?@)?([a-zA-Z0-9\\-._~%]+|\\[[a-zA-Z0-9\\-._~%!$&'()*+,;=:]+\\])" );
        if ( regex_search( m_pimpl->m_uri, match, pattern ) ) authority = match[ 5 ];
        else return authority;

        if ( authority.front( ) == '[' ) authority.erase( 0, 1 );
        if ( authority.back( ) == ']' ) authority.erase( authority.length( ) - 1, 1 );
        return authority;
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
