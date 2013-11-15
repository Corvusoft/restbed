/*
 * Copyright (c) 2013 Corvusoft
 */

//System Includes
#include <regex>
#include <iostream>
//Project Includes
#include "restbed/detail/helpers/regex.h"

//External Includes

//System Namespaces
using std::regex;
using std::string;
using std::regex_error;

//Project Namespaces

//External Namespaces

namespace restbed
{
	namespace detail
	{
		namespace helpers
		{
	        bool Regex::is_valid( const string& value )
	        {
	        	bool result = true;

	        	try
	        	{
	        		regex pattern( value );
	        	}
	        	catch ( regex_error const& re )
	        	{
	        		std::cout << "regex: " << re.what() << std::endl;
	        		result = false;
	        	}
	        	
	        	return result;
	        }
		}
	}
}
