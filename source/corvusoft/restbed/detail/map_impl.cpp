/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <utility>
#include <algorithm>

//Project Includes
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/detail/map_impl.hpp"

//External Includes

//System Namespaces
using std::map;
using std::pair;
using std::string;
using std::find_if;
using std::multimap;

//Project Namespaces

//External Namespaces

namespace restbed
{
    namespace detail
    {        
        MapImpl::iterator MapImpl::find_ignoring_case( const string& key, map< string, string >& container )
        {
            auto identifier = String::lowercase( key );
            
            auto iterator = find_if( container.begin( ), container.end( ), [ &identifier ]( const pair< string, string >& value )
            {
                return ( identifier == String::lowercase( value.first ) );
            } );
            
            return iterator;
        }
        
        MapImpl::const_iterator MapImpl::find_ignoring_case( const string& key, const map< string, string >& container )
        {
            return find_ignoring_case( key, const_cast< map< string, string >& >( container ) );
        }
        
        MapImpl::iterator MapImpl::find_ignoring_case( const string& key, multimap< string, string >& container )
        {
            auto identifier = String::lowercase( key );
            
            auto iterator = find_if( container.begin( ), container.end( ), [ &identifier ]( const pair< string, string >& value )
            {
                return ( identifier == String::lowercase( value.first ) );
            } );
            
            return iterator;
        }
        
        MapImpl::const_iterator MapImpl::find_ignoring_case( const string& key, const multimap< string, string >& container )
        {
            return find_ignoring_case( key, const_cast< multimap< string, string >& >( container ) );
        }
    }
}
