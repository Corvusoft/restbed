/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/detail/string_impl.hpp"

//External Includes

//System Namespaces
using std::string;
using std::vector;
using std::multimap;

//Project Namespaces
using restbed::detail::StringImpl;

//External Namespaces

namespace restbed
{
    Bytes String::to_bytes( const string& value )
    {
        return StringImpl::to_bytes( value );
    }
    
    string String::to_string( const Bytes& value )
    {
        return StringImpl::to_string( value );
    }
    
    string String::lowercase( const string& value )
    {
        return StringImpl::lowercase( value );
    }
    
    string String::uppercase( const string& value )
    {
        return StringImpl::uppercase( value );
    }
    
    string String::format( const char* format, ... )
    {
        va_list arguments;
        va_start( arguments, format );
        
        string formatted = StringImpl::format( format, arguments );
        
        va_end( arguments );
        
        return formatted;
    }
    
    vector< string > String::split( const string& value, const char delimiter )
    {
        return StringImpl::split( value, delimiter );
    }
    
    string String::join( const multimap< string, string >& values, const string& pair_delimiter, const string& delimiter )
    {
        return StringImpl::join( values, pair_delimiter, delimiter );
    }
    
    string String::trim( const string& value, const string& delimiter )
    {
        return StringImpl::trim( value, delimiter );
    }
    
    string String::remove( const string& target, const string& value, const Option option )
    {
        return StringImpl::remove( target, value, option );
    }
    
    string String::replace( const string& target, const string& substitute, const string& value, const Option option )
    {
        return StringImpl::replace( target, substitute, value, option );
    }
}
