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

#ifndef _RESTBED_DETAIL_HELPERS_STRING_H
#define _RESTBED_DETAIL_HELPERS_STRING_H 1

//System Includes
#include <string>
#include <vector>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations

    namespace detail
    {
        //Forward Declarations

        namespace helpers
        {
            //Forward Declarations

            class String
            {
                public:
                    //Friends
                    
                    //Definitions

                    //Constructors
                    
                    //Functionality
                    static std::string lowercase( const std::string& value );

                    static std::string uppercase( const std::string& value );

                    static std::string format( const std::string& format, ... );

                    static std::string deduplicate( const std::string& value, const char target );

                    static std::vector< std::string > split( const std::string& text, const char delimiter );

                    static std::string trim( const std::string& value, const std::string& delimiter = " \t" );

                    static std::string trim_leading( const std::string& value, const std::string& delimiter = " \t" );

                    static std::string trim_lagging( const std::string& value, const std::string& delimiter = " \t" );

                    static std::string remove( const std::string& needle, const std::string& haystack, bool case_insensitive = false );

                    //Getters
                    
                    //Setters
                    
                    //Operators
                    
                    //Properties
                    static const char* empty;
                
                protected:
                    //Friends
                    
                    //Definitions
                    
                    //Constructors
                    
                    //Functionality
                    
                    //Getters
                    
                    //Setters
                    
                    //Operators
                    
                    //Properties
                    
                private:
                    //Friends
                    
                    //Definitions
                    
                    //Constructors
                    String( void ) = delete;
                    
                    String( const String& original ) = delete;
                    
                    virtual ~String( void ) = delete;

                    //Functionality
                    
                    //Getters
                    
                    //Setters
                    
                    //Operators
                    String& operator =( const String& rhs ) = delete;

                    //Properties
            };
        }
    }
}

#endif  /* _RESTBED_DETAIL_HELPERS_STRING_H */
