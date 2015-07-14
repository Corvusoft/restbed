/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <regex>
#include <cstdio>
#include <cstdlib>
#include <netdb.h>
#include <unistd.h>
#include <stdexcept>
#include <arpa/inet.h>

//Project Includes
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
using std::runtime_error;
using std::invalid_argument;

//Project Namespaces

//External Namespaces

namespace restbed
{
    namespace detail
    {
        UriImpl::UriImpl( void ) : m_uri( "" )
        {
            return;
        }
        
        UriImpl::UriImpl( const UriImpl& original ) : m_uri( original.m_uri )
        {
            return;
        }
        
        UriImpl::~UriImpl( void )
        {
            return;
        }
        
        string UriImpl::to_string( void ) const
        {
            return m_uri;
        }

        bool UriImpl::is_valid( const string& value )
        {
            try
            {
                UriImpl pimpl;
                pimpl.set_uri( value );
            }
            catch ( const invalid_argument& ia )
            {
                return false;
            }

            return true;
        }

        string UriImpl::decode( const Bytes& value )
        {
            return UriImpl::decode( string( value.begin( ), value.end( ) ) );
        }
        
        string UriImpl::decode( const string& value )
        {
            static const string::size_type BASE16 = 16;
            
            string result = "";
            
            for ( string::size_type index = 0; index not_eq value.length( ); index++ )
            {
                if ( value[ index ] == '%' )
                {
                    char hexidecimal[ 3 ] = { 0 };
                    hexidecimal[ 0 ] = value[ ++index ];
                    hexidecimal[ 1 ] = value[ ++index ];
                    
                    char byte = static_cast< char >( strtol( hexidecimal, nullptr, BASE16 ) );
                    result.push_back( byte );
                }
                else
                {
                    result.push_back( value[ index ] );
                }
            }
            
            return result;
        }
        
        string UriImpl::decode_parameter( const string& value )
        {
            return UriImpl::decode( String::replace( "+", " ", value ) );
        }
        
        string UriImpl::encode( const Bytes& value )
        {
            string encoded = "";
            
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
        
        string UriImpl::encode( const string& value )
        {
            return UriImpl::encode( Bytes( value.begin( ), value.end( ) ) );
        }
        
        int UriImpl::get_port( void ) const
        {
            smatch match;
            string port = "";
            static const regex pattern( "^[a-zA-Z][a-zA-Z0-9+\\-.]*://(([a-zA-Z0-9\\-._~%!$&'()*+,;=]+)(:([a-zA-Z0-9\\-._~%!$&'()*+,;=]+))?@)?([a-zA-Z0-9\\-._~%]+|\\[[a-zA-Z0-9\\-._~%!$&'()*+,;=:]+\\]):([0-9]+)" );
            
            if ( regex_search( m_uri, match, pattern ) )
            {
                port = match[ 6 ];
            }
            else
            {
                const auto scheme = get_scheme( );
                
                if ( not scheme.empty( ) )
                {
                    struct servent* entry = getservbyname( scheme.data( ), nullptr );
                    port = ::to_string( ntohs( entry->s_port ) );
                }
            }
            
            if ( port.empty( ) )
            {
                return 0;
            }
            
            return stoi( port );
        }
        
        string UriImpl::get_path( void ) const
        {
            smatch match;
            static const regex pattern( "^([a-zA-Z][a-zA-Z0-9+\\-.]*://([^/?#]+)?)?([a-zA-Z0-9\\-._~%!$&'()*+,;=:@/]*)" );
            
            if ( regex_search( m_uri, match, pattern ) )
            {
                return match[ 3 ];
            }
            
            return "";
        }
        
        string UriImpl::get_query( void ) const
        {
            smatch match;
            static const regex pattern( "^[^?#]+\\?([^#]+)" );

            if ( regex_search( m_uri, match, pattern ) )
            {
                return match[ 1 ];
            }
            
            return "";
        }
        
        string UriImpl::get_scheme( void ) const
        {
            smatch match;
            static const regex pattern( "^([a-zA-Z][a-zA-Z0-9+\\-.]*):" );
            
            if ( regex_search( m_uri, match, pattern ) )
            {
                return match[ 1 ];
            }
            
            return "";
        }
        
        string UriImpl::get_fragment( void ) const
        {
            smatch match;
            static const regex pattern( "#(.+)" );

            if ( regex_search( m_uri, match, pattern ) )
            {
                return match[ 1 ];
            }
            
            return "";
        }
        
        string UriImpl::get_username( void ) const
        {
            smatch match;
            static const regex pattern( "^[a-zA-Z0-9+\\-.]+://([a-zA-Z0-9\\-._~%!$&'()*+,;=]+)(:([a-zA-Z0-9\\-._~%!$&'()*+,;=]+))?@" );

            if ( regex_search( m_uri, match, pattern ) )
            {
                return match[ 1 ];
            }
            
            return "";
        }
        
        string UriImpl::get_password( void ) const
        {
            smatch match;
            static const regex pattern( "^[a-zA-Z0-9+\\-.]+://([a-zA-Z0-9\\-._~%!$&'()*+,;=]+):([a-zA-Z0-9\\-._~%!$&'()*+,;=]+)@" );

            if ( regex_search( m_uri, match, pattern ) )
            {
                return match[ 2 ];
            }
            
            return "";
        }
        
        string UriImpl::get_authority( void ) const
        {
            smatch match;
            static const regex pattern( "^[a-zA-Z][a-zA-Z0-9+\\-.]*://(([a-zA-Z0-9\\-._~%!$&'()*+,;=]+)(:([a-zA-Z0-9\\-._~%!$&'()*+,;=]+))?@)?([a-zA-Z0-9\\-._~%]+|\\[[a-zA-Z0-9\\-._~%!$&'()*+,;=:]+\\])" );

            if ( regex_search( m_uri, match, pattern ) )
            {
                return match[ 5 ];
            }
            
            return "";
        }

        multimap< string, string > UriImpl::get_query_parameters( void ) const
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
        
        void UriImpl::set_uri( const string& value )
        {
            static const regex pattern( "^([a-zA-Z][a-zA-Z0-9+-.]*):((\\/\\/(((([a-zA-Z0-9\\-._~!$&'()*+,;=':]|(%[0-9a-fA-F]{2}))*)@)?((\\[((((([0-9a-fA-F]{1,4}:){6}|(::([0-9a-fA-F]{1,4}:){5})|(([0-9a-fA-F]{1,4})?::([0-9a-fA-F]{1,4}:){4})|((([0-9a-fA-F]{1,4}:)?[0-9a-fA-F]{1,4})?::([0-9a-fA-F]{1,4}:){3})|((([0-9a-fA-F]{1,4}:){0,2}[0-9a-fA-F]{1,4})?::([0-9a-fA-F]{1,4}:){2})|((([0-9a-fA-F]{1,4}:){0,3}[0-9a-fA-F]{1,4})?::[0-9a-fA-F]{1,4}:)|((([0-9a-fA-F]{1,4}:){0,4}[0-9a-fA-F]{1,4})?::))((([0-9a-fA-F]{1,4}):([0-9a-fA-F]{1,4}))|(([0-9]|(1[0-9]{2})|(2[0-4][0-9])|(25[0-5]))\\.([0-9]|(1[0-9]{2})|(2[0-4][0-9])|(25[0-5]))\\.([0-9]|(1[0-9]{2})|(2[0-4][0-9])|(25[0-5]))\\.([0-9]|(1[0-9]{2})|(2[0-4][0-9])|(25[0-5])))))|((([0-9a-fA-F]{1,4}:){0,5}[0-9a-fA-F]{1,4})?::[0-9a-fA-F]{1,4})|((([0-9a-fA-F]{1,4}:){0,5}[0-9a-fA-F]{1,4})?::))|(v[0-9a-fA-F]+\\.[a-zA-Z0-9\\-._~!$&'()*+,;=':]+))\\])|(([0-9]|(1[0-9]{2})|(2[0-4][0-9])|(25[0-5]))\\.([0-9]|(1[0-9]{2})|(2[0-4][0-9])|(25[0-5]))\\.([0-9]|(1[0-9]{2})|(2[0-4][0-9])|(25[0-5]))\\.([0-9]|(1[0-9]{2})|(2[0-4][0-9])|(25[0-5])))|(([a-zA-Z0-9\\-._~!$&'()*+,;=']|(%[0-9a-fA-F]{2}))*))(:[0-9]*)?)((\\/([a-zA-Z0-9\\-._~!$&'()*+,;=':@]|(%[0-9a-fA-F]{2}))*)*))|(\\/?(([a-zA-Z0-9\\-._~!$&'()*+,;=':@]|(%[0-9a-fA-F]{2}))+(\\/([a-zA-Z0-9\\-._~!$&'()*+,;=':@]|(%[0-9a-fA-F]{2}))*)*)?))(\\?(([a-zA-Z0-9\\-._~!$&'()*+,;=':@\\/?]|(%[0-9a-fA-F]{2}))*))?((#(([a-zA-Z0-9\\-._~!$&'()*+,;=':@\\/?]|(%[0-9a-fA-F]{2}))*)))?$" );

            if ( not regex_match( value, pattern ) )
            {
                throw invalid_argument( "Argument is not a valid URI: " + value );
            }
            
            m_uri = value;
        }
        
        UriImpl& UriImpl::operator =( const UriImpl& rhs )
        {
            set_uri( rhs.m_uri );
            
            return *this;
        }
        
        bool UriImpl::operator <( const UriImpl& rhs ) const
        {
            return m_uri < rhs.m_uri;
        }
        
        bool UriImpl::operator >( const UriImpl& rhs ) const
        {
            return m_uri > rhs.m_uri;
        }
        
        bool UriImpl::operator ==( const UriImpl& rhs ) const
        {
            return m_uri == rhs.m_uri;
        }
        
        bool UriImpl::operator !=( const UriImpl& rhs ) const
        {
            return m_uri not_eq rhs.m_uri;
        }
    }
}
