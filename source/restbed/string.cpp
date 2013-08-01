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

//Project Includes
#include "restbed/string.h"
#include "restbed/detail/string_impl.h"

//External Includes

//System Namespaces
using std::string;
using std::vector;

//Project Namespaces
using restbed::detail::StringImpl;

//External Namespaces

namespace restbed
{
    const char* String::empty = StringImpl::empty;
    
    string String::trim( const string& value )
    {
        return StringImpl::trim( value );
    }
    
    string String::to_upper( const string& value )
    {
    	return StringImpl::to_upper( value );
    }

    vector< string > String::split(const string& text, const char delimiter )
    {
    	return StringImpl::split( text, delimiter );
    }
}
