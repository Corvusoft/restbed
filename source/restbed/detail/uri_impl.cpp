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
#include <string>
#include <cstdlib>
#include <netdb.h>
#include <stdexcept>

//Project Includes
#include "restbed/string.h"
#include "restbed/detail/uri_impl.h"

//External Includes

//System Namespaces
using std::stoi;
using std::regex;
using std::smatch;
using std::string;
using std::to_string;
using std::invalid_argument;

//Project Namespaces

//External Namespaces

namespace restbed
{
    namespace detail
    {
        UriImpl::UriImpl( void ) : m_uri( String::empty )
        {
            //n/a
        }
        
        UriImpl::UriImpl( const UriImpl& original ) : m_uri( original.m_uri )
        {
            //n/a
        }
        
        UriImpl::~UriImpl( void )
        {
            //n/a
        }
        
        string UriImpl::to_string( void ) const
        {
            return m_uri;
        }
        
        string UriImpl::to_native_path( void ) const
        {
            return get_path( );
        }
        
        string UriImpl::decode( const Bytes& value )
        {
            return UriImpl::decode( string( value.begin( ), value.end( ) ) );
        }
        
        string UriImpl::decode( const string& value )
        {
            const int BASE16 = 16;
            
            string result = String::empty;
            
            for ( string::size_type index = 0; index not_eq value.length( ); index++ )
            {
                if ( value[ index ] == '%' )
                {
                    char hexidecimal[ 3 ] = { 0 };
                    
                    hexidecimal[ 0 ] = value[ ++index ];
                    
                    hexidecimal[ 1 ] = value[ ++index ];
                    
                    Byte byte = static_cast< Byte >( strtol( hexidecimal, nullptr, BASE16 ) );
                    
                    result.push_back( byte );
                }
                else
                {
                    result.push_back( value[ index ] );
                }
            }
            
            return result;
        }
        
        string UriImpl::encode( const Bytes& value )
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
        
        string UriImpl::encode( const string& value )
        {
            return UriImpl::encode( Bytes( value.begin( ), value.end( ) ) );
        }
        
        int UriImpl::get_port( void ) const
        {
            regex pattern( "^[a-zA-Z][a-zA-Z0-9+\\-.]*://(([a-zA-Z0-9\\-._~%!$&'()*+,;=]+)(:([a-zA-Z0-9\\-._~%!$&'()*+,;=]+))?@)?([a-zA-Z0-9\\-._~%]+|\\[[a-zA-Z0-9\\-._~%!$&'()*+,;=:]+\\]):([0-9]+)" );
            
            smatch match;
            
            string port = String::empty;
            
            bool found = regex_search( m_uri, match, pattern );
            
            if ( found )
            {
                port = match[ 6 ];
            }
            else //best guess.
            {
                string scheme = get_scheme( );
                
                if ( not scheme.empty( ) )
                {
                    struct servent* entry = getservbyname( scheme.data( ), nullptr );
                    
                    port = ::to_string( ntohs( entry->s_port ) );
                }
            }
            
            int number = 0;
            
            if ( not port.empty( ) )
            {
                number = stoi( port );
            }
            
            return number;
        }
        
        string UriImpl::get_path( void ) const
        {
            regex pattern( "^([a-zA-Z][a-zA-Z0-9+\\-.]*://([^/?#]+)?)?([a-zA-Z0-9\\-._~%!$&'()*+,;=:@/]*)" );
            
            smatch match;
            
            string domain = String::empty;
            
            bool found = regex_search( m_uri, match, pattern );
            
            if ( found )
            {
                domain = match[ 3 ];
            }
            
            return domain;
        }
        
        string UriImpl::get_query( void ) const
        {
            regex pattern( "^[^?#]+\\?([^#]+)" );
            
            smatch match;
            
            string query = String::empty;
            
            bool found = regex_search( m_uri, match, pattern );
            
            if ( found )
            {
                query = match[ 1 ];
            }
            
            return query;
        }
        
        string UriImpl::get_scheme( void ) const
        {
            regex pattern( "^([a-zA-Z][a-zA-Z0-9+\\-.]*):" );
            
            smatch match;
            
            string scheme = String::empty;
            
            bool found = regex_search( m_uri, match, pattern );
            
            if ( found )
            {
                scheme = match[ 1 ];
            }
            
            return scheme;
        }
        
        string UriImpl::get_fragment( void ) const
        {
            regex pattern( "#(.+)" );
            
            smatch match;
            
            string fragment = String::empty;
            
            bool found = regex_search( m_uri, match, pattern );
            
            if ( found )
            {
                fragment = match[ 1 ];
            }
            
            return fragment;
        }
        
        string UriImpl::get_username( void ) const
        {
            regex pattern( "^[a-zA-Z0-9+\\-.]+://([a-zA-Z0-9\\-._~%!$&'()*+,;=]+)(:([a-zA-Z0-9\\-._~%!$&'()*+,;=]+))?@" );
            
            smatch match;
            
            string username = String::empty;
            
            bool found = regex_search( m_uri, match, pattern );
            
            if ( found )
            {
                username = match[ 1 ];
            }
            
            return username;
        }
        
        string UriImpl::get_password( void ) const
        {
            regex pattern( "^[a-zA-Z0-9+\\-.]+://([a-zA-Z0-9\\-._~%!$&'()*+,;=]+):([a-zA-Z0-9\\-._~%!$&'()*+,;=]+)@" );
            
            smatch match;
            
            string password = String::empty;
            
            bool found = regex_search( m_uri, match, pattern );
            
            if ( found )
            {
                password = match[ 2 ];
            }
            
            return password;
        }
        
        string UriImpl::get_authority( void ) const
        {
            regex pattern( "^[a-zA-Z][a-zA-Z0-9+\\-.]*://(([a-zA-Z0-9\\-._~%!$&'()*+,;=]+)(:([a-zA-Z0-9\\-._~%!$&'()*+,;=]+))?@)?([a-zA-Z0-9\\-._~%]+|\\[[a-zA-Z0-9\\-._~%!$&'()*+,;=:]+\\])" );
            
            smatch match;
            
            string authority = String::empty;
            
            bool found = regex_search( m_uri, match, pattern );
            
            if ( found )
            {
                authority = match[ 5 ];
            }
            
            return authority;
        }
        
        void UriImpl::set_uri( const string& value )
        {
            bool valid = regex_match( value, regex( "^([a-zA-Z][a-zA-Z0-9+-.]*):((\\/\\/(((([a-zA-Z0-9\\-._~!$&'()*+,;=':]|(%[0-9a-fA-F]{2}))*)@)?((\\[((((([0-9a-fA-F]{1,4}:){6}|(::([0-9a-fA-F]{1,4}:){5})|(([0-9a-fA-F]{1,4})?::([0-9a-fA-F]{1,4}:){4})|((([0-9a-fA-F]{1,4}:)?[0-9a-fA-F]{1,4})?::([0-9a-fA-F]{1,4}:){3})|((([0-9a-fA-F]{1,4}:){0,2}[0-9a-fA-F]{1,4})?::([0-9a-fA-F]{1,4}:){2})|((([0-9a-fA-F]{1,4}:){0,3}[0-9a-fA-F]{1,4})?::[0-9a-fA-F]{1,4}:)|((([0-9a-fA-F]{1,4}:){0,4}[0-9a-fA-F]{1,4})?::))((([0-9a-fA-F]{1,4}):([0-9a-fA-F]{1,4}))|(([0-9]|(1[0-9]{2})|(2[0-4][0-9])|(25[0-5]))\\.([0-9]|(1[0-9]{2})|(2[0-4][0-9])|(25[0-5]))\\.([0-9]|(1[0-9]{2})|(2[0-4][0-9])|(25[0-5]))\\.([0-9]|(1[0-9]{2})|(2[0-4][0-9])|(25[0-5])))))|((([0-9a-fA-F]{1,4}:){0,5}[0-9a-fA-F]{1,4})?::[0-9a-fA-F]{1,4})|((([0-9a-fA-F]{1,4}:){0,5}[0-9a-fA-F]{1,4})?::))|(v[0-9a-fA-F]+\\.[a-zA-Z0-9\\-._~!$&'()*+,;=':]+))\\])|(([0-9]|(1[0-9]{2})|(2[0-4][0-9])|(25[0-5]))\\.([0-9]|(1[0-9]{2})|(2[0-4][0-9])|(25[0-5]))\\.([0-9]|(1[0-9]{2})|(2[0-4][0-9])|(25[0-5]))\\.([0-9]|(1[0-9]{2})|(2[0-4][0-9])|(25[0-5])))|(([a-zA-Z0-9\\-._~!$&'()*+,;=']|(%[0-9a-fA-F]{2}))*))(:[0-9]*)?)((\\/([a-zA-Z0-9\\-._~!$&'()*+,;=':@]|(%[0-9a-fA-F]{2}))*)*))|(\\/?(([a-zA-Z0-9\\-._~!$&'()*+,;=':@]|(%[0-9a-fA-F]{2}))+(\\/([a-zA-Z0-9\\-._~!$&'()*+,;=':@]|(%[0-9a-fA-F]{2}))*)*)?))(\\?(([a-zA-Z0-9\\-._~!$&'()*+,;=':@\\/?]|(%[0-9a-fA-F]{2}))*))?((#(([a-zA-Z0-9\\-._~!$&'()*+,;=':@\\/?]|(%[0-9a-fA-F]{2}))*)))?$" ) );
            
            if ( not valid )
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
            return ( m_uri < rhs.m_uri );
        }
        
        bool UriImpl::operator >( const UriImpl& rhs ) const
        {
            return ( m_uri > rhs.m_uri );
        }
        
        bool UriImpl::operator ==( const UriImpl& rhs ) const
        {
            return ( m_uri == rhs.m_uri );
        }
        
        bool UriImpl::operator !=( const UriImpl& rhs ) const
        {
            return ( m_uri not_eq rhs.m_uri );
        }
    }
}
