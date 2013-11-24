/*
 * Copyright (c) 2013 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/detail/helpers/string.h"

//External Includes

//System Namespaces
using std::string;
using std::vector;

//Project Namespaces

//External Namespaces

namespace restbed
{
	namespace detail
	{
		namespace helpers
		{
		    const char* String::empty = "";

	        string String::lowercase( const string& value )
	        {
	            string result = empty;
	            
	            transform( value.begin( ), value.end( ), back_inserter( result ), (int (*)(int))tolower );
	            
	            return result;
	        }
	        
	        string String::uppercase( const string& value )
	        {
	            string result = empty;
	            
	            transform( value.begin( ), value.end( ), back_inserter( result ), (int (*)(int))toupper );
	            
	            return result;
	        }

	        string String::format( const string& format, ... )
			{
			    va_list arguments;

			    va_start( arguments, format );

			    string formatted = empty;

			    string::size_type length = 1024;

			    string::size_type required_length = String::format( formatted, length + 1, format, arguments );

			    va_end( arguments );

			    if ( required_length > length )
			    {
			    	va_start( arguments, format );

			    	String::format( formatted, required_length + 1, format, arguments );

			    	va_end( arguments );
			    }

			    return formatted;
			}

	        vector< string > String::split(const string& value, const char delimiter )
	        {
	            vector< string > tokens;
	            
	            string::size_type start = 0;
	            string::size_type end = 0;
	            
	            while ( ( end = value.find( delimiter, start ) ) not_eq string::npos )
	            {
	                string text = value.substr( start, end - start );
	                
	                if ( not text.empty( ) )
	                {
	                    tokens.push_back( text );
	                }
	                
	                start = end + 1;
	            }
	            
	            string token = value.substr( start );
	            
	            if ( not token.empty( ) and token not_eq value )
	            {
	                tokens.push_back( token );
	            }
	            
	            return tokens;
	        }

	        string String::trim( const string& value, const string& delimiter )
	        {
	            string result = empty;

	            result = trim_leading( value, delimiter );

	            result = trim_lagging( result, delimiter );

	            return result;
	        }

	        string String::trim_leading( const string& value, const string& delimiter )
	        {
	            string result = value;

	            size_t position = result.find_first_not_of( delimiter );

	            if( string::npos not_eq position )
	            {
	                result = result.substr( position );
	            }

	            return result;
	        }

	        string String::trim_lagging( const string& value, const string& delimiter )
	        {
	            string result = value;

	            size_t position = result.find_last_not_of( delimiter );

	            if( string::npos not_eq position )
	            {
	                result = result.substr( 0, position + 1 );
	            }

	            return result;
	        }

	        string String::remove( const string& needle, const string& haystack, bool case_insensitive )
	        {
	            string target = case_insensitive ? String::lowercase( needle ) : needle;
	            string source = case_insensitive ? String::lowercase( haystack ) : haystack;

	            string::size_type index = source.find( target );

	            if ( index not_eq string::npos )
	            {
	                source.replace( index, target.length( ), empty );
	            }

	            return source;
	        }

			string::size_type String::format( string& output, const string::size_type length, const string& format, va_list arguments )
			{
				char* formatted = new char[ length + 1 ];

				string::size_type required_length = vsnprintf( formatted, length + 1, format.data( ), arguments );

				output = formatted;

				delete[ ] formatted;

				return required_length;
			}
		}
	}
}
