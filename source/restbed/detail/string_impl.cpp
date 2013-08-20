/*
 * Site: restbed.net
 * Author: Ben Crowhurst
 *
 * Copyright (c) 2013 Restbed Core Development Team and Community Contributors
 *
 * This file is part of Restbed.
 *
 * AppOn is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AppOn is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with AppOn.  If not, see <http://www.gnu.org/licenses/>.
 */

//System Includes
#include <cctype>
#include <iterator>
#include <algorithm>

//Project Includes
#include "restbed/detail/string_impl.h"

//External Includes

//System Namespaces
using std::string;
using std::vector;
using std::tolower;
using std::toupper;
using std::transform;
using std::back_inserter;

//Project Namespaces

//External Namespaces

namespace restbed
{
    namespace detail
    {
        const char* StringImpl::empty = "";
        
        string StringImpl::trim( const string& value )
        {
            static const char* whitespace = " \t";
            
            string result = value;
            
            string::size_type index = result.find_first_not_of( whitespace );
            
            result.erase( 0, index );
            
            index = result.find_last_not_of( whitespace );
            
            if ( index not_eq string::npos )
            {
                result.erase( index + 1 );
            }
            
            return result;
        }

        string StringImpl::to_lower( const string& value )
        {
            string result = empty;
            
            transform( value.begin( ), value.end( ), back_inserter( result ), (int (*)(int))tolower );
            
            return result;
        }
        
        string StringImpl::to_upper( const string& value )
        {
            string result = empty;
            
            transform( value.begin( ), value.end( ), back_inserter( result ), (int (*)(int))toupper );
            
            return result;
        }

        vector< string > StringImpl::split(const string& text, const char delimiter )
        {
            vector< string > tokens;
            
            string::size_type start = 0;
            string::size_type end = 0;
            
            while ( ( end = text.find( delimiter, start ) ) not_eq string::npos )
            {
                string value = text.substr( start, end - start );
                
                if ( not value.empty( ) )
                {
                    tokens.push_back( value );
                }
                
                start = end + 1;
            }
            
            string token = text.substr( start );
            
            if ( not token.empty( ) && token not_eq text )
            {
                tokens.push_back( token );
            }
            
            return tokens;
        }
    }
}
