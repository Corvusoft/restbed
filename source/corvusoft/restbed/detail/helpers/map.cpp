/*
 * Copyright (c) 2013 Corvusoft
 */

//System Includes

//Project Includes
#include "restbed/detail/helpers/map.h"
#include "restbed/detail/helpers/string.h"

//External Includes

//System Namespaces
using std::map;
using std::string;

//Project Namespaces

//External Namespaces

namespace restbed
{
    namespace detail
    {
        namespace helpers
        {
		    Map::const_iterator Map::find_key_ignoring_case( const string& key, const map< string, string >& container )
		    {
		        string identifier = String::lowercase( key );

		        for ( auto value : container )
		        {
		            if ( identifier == String::lowercase( value.first ) )
		            {
		                identifier = value.first;
		                break;
		            }
		        }

		        return ( identifier not_eq String::empty ) ? container.find( identifier ) : container.end( );
		    }
        }
    }
}
