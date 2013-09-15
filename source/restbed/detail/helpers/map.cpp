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
