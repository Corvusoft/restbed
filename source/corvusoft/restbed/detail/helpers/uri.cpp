/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <cstdio>
#include <cstdlib>

//Project Includes
#include "corvusoft/restbed/detail/helpers/uri.h"
#include "corvusoft/restbed/detail/helpers/string.h"

//External Includes

//System Namespaces
using std::strtol;
using std::string;
using std::snprintf;

//Project Namespaces

//External Namespaces

namespace restbed
{
	namespace detail
	{
		namespace helpers
		{
			string Uri::encode( const string& value )
			{
                string encoded = String::empty;
                
            	for ( const char& character : value )
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

        	string Uri::decode( const string& value )
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
		}
	}
}
