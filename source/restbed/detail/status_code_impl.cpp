/*
 * Site: restbed.corvusoft.co.uk
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
#include <stdexcept>

//Project Includes
#include "restbed/string.h"
#include "restbed/detail/status_code_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::string;
using std::invalid_argument;

//Project Namespaces

//External Namespaces

namespace restbed
{
    namespace detail
    {
        int StatusCodeImpl::parse( const string& value )
        {
            int result = -1;
            
            const string original = String::to_lower( value );
            
            for ( auto pair : m_mappings )
            {
                string text = String::to_lower( pair.second );
                
                if ( original == text )
                {
                    result = pair.first;
                    break;
                }
            }
            
            if ( result == -1 )
            {
                throw invalid_argument( String::empty );
            }
            
            return result;
        }
        
        string StatusCodeImpl::to_string( const int code )
        {
            string value = String::empty;

            const auto& iterator = m_mappings.find( code );

            if ( iterator not_eq m_mappings.end( ) )
            {
                value = m_mappings.at( code );
            }
            else
            {
                throw invalid_argument( String::empty );
            }

            return value;
        }
        
        map< int, string > StatusCodeImpl::get_mappings( void )
        {
            return m_mappings;
        }
        
        void StatusCodeImpl::set_mappings( const map< int, string >& values )
        {
            m_mappings = values;
        }

        map< int, string > StatusCodeImpl::m_mappings = {
            { 100, "Continue" },
            { 101, "Switching Protocols" },
            { 102, "Processing" },
            { 200, "OK" },
            { 201, "Created" },
            { 202, "Accepted" },
            { 203, "Non-Authoritative Information" },
            { 204, "No Content" },
            { 205, "Reset Content" },
            { 206, "Partial Content" },
            { 207, "Multi-Status" },
            { 208, "Already Reported" },
            { 226, "IM Used" },
            { 300, "Multiple Choices" },
            { 301, "Moved Permanently" },
            { 302, "Found" },
            { 303, "See Other" },
            { 304, "Not Modified" },
            { 305, "Use Proxy" },
            { 306, "Reserved" },
            { 307, "Temporary Redirect" },
            { 308, "Permanent Redirect" },
            { 400, "Bad Request" },
            { 401, "Unauthorized" },
            { 402, "Payment Required" },
            { 403, "Forbidden" },
            { 404, "Not Found" },
            { 405, "Method Not Allowed" },
            { 406, "Not Acceptable" },
            { 407, "Proxy Authentication Required" },
            { 408, "Request Timeout" },
            { 409, "Conflict" },
            { 410, "Gone" },
            { 411, "Length Required" },
            { 412, "Precondition Failed" },
            { 413, "Request Entity Too Large" },
            { 414, "Request-URI Too Long" },
            { 415, "Unsupported Media Type" },
            { 416, "Requested Range Not Satisfiable" },
            { 417, "Expectation Failed" },
            { 422, "Unprocessable Entity" },
            { 423, "Locked" },
            { 424, "Failed Dependency" },
            { 426, "Upgrade Required" },
            { 428, "Precondition Required" },
            { 429, "Too Many Requests" },
            { 431, "Request Header Fields Too Large" },
            { 500, "Internal Server Error" },
            { 501, "Not Implemented" },
            { 502, "Bad Gateway" },
            { 503, "Service Unavailable" },
            { 504, "Gateway Timeout" },
            { 505, "HTTP Version Not Supported" },
            { 506, "Variant Also Negotiates (Experimental)  " },
            { 507, "Insufficient Storage" },
            { 508, "Loop Detected" },
            { 510, "Not Extended" },
            { 511, "Network Authentication Required" }
        };
    }
}
