/*
 * Copyright 2013-2025, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <regex>
#include <ranges>
#include <memory>
#include <ciso646>
#include <algorithm>

//Project Includes
#include "corvusoft/restbed/string.hpp"

//External Includes

//System Namespaces
using std::regex;
using std::string;
using std::vector;
using std::smatch;
using std::multimap;
using std::transform;
using std::unique_ptr;
using std::regex_match;
using std::regex_replace;
using std::regex_constants::icase;

//Project Namespaces

//External Namespaces

namespace restbed
{
    Bytes String::to_bytes( const string& value )
    {
        return value | std::views::transform([](auto c){
            return static_cast<std::byte>(c);
        }) | std::ranges::to<Bytes>();
    }
    
    string String::lowercase( const string& value )
    {
        string result = "";
        transform( value.begin( ), value.end( ), back_inserter( result ), [ ]( const char value ) { return static_cast< char >( tolower( value ) ); } );
        return result;
    }
    
    string String::uppercase( const string& value )
    {
        string result = "";
        transform( value.begin( ), value.end( ), back_inserter( result ), [ ]( const char value ) { return static_cast< char >( toupper( value ) ); } );
        return result;
    }
    
    vector< string > String::split( const string& value, const char delimiter )
    {
        vector< string > tokens;
        string::size_type start = 0;
        string::size_type end = 0;
        
        while ( ( end = value.find( delimiter, start ) ) not_eq string::npos )
        {
            const auto text = value.substr( start, end - start );
            
            if ( not text.empty( ) )
            {
                tokens.push_back( text );
            }
            
            start = end + 1;
        }
        
        const auto token = value.substr( start );
        
        if ( not token.empty( ) )
        {
            tokens.push_back( token );
        }
        
        return tokens;
    }
    
    string String::join( const multimap< string, string >& values, const string& pair_delimiter, const string& delimiter )
    {
        string result = "";
        
        for ( auto value : values )
        {
            result += value.first + pair_delimiter + value.second + delimiter;
        }
        
        if ( not result.empty( ) )
        {
            const size_t position = result.find_last_not_of( delimiter );
            
            if ( string::npos not_eq position )
            {
                result = result.substr( 0, position + 1 );
            }
        }
        
        return result;
    }
    
    string String::remove( const string& target, const string& value, const Option option )
    {
        return replace( target, "", value, option );
    }
    
    string String::replace( const string& target, const string& substitute, const string& value, const Option option )
    {
        if ( target.empty( ) )
        {
            return value;
        }
        
        static const regex escape( "([.^$|()\\[\\]{}*+?\\\\])" );
        const auto expression = regex_replace( target, escape, "\\$1" );
        auto pattern = regex( expression );
        
        if ( option & String::Option::CASE_INSENSITIVE )
        {
            pattern.assign( expression, icase );
        }
        
        smatch match;
        string result = value;
        
        while ( regex_search( result, match, pattern ) )
        {
            result = regex_replace( result, pattern, substitute );
        }
        
        return result;
    }
}
