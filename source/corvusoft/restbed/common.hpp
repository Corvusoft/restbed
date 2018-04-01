/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <type_traits>
#include <regex>
#include <functional>

//Project Includes
#include <corvusoft/restbed/string.hpp>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    class Common
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            
            //Functionality
            template< typename Type >
            static Type parse_parameter( const std::string& value, const Type default_value )
            {
                std::istringstream stream( value );
                
                Type parameter;
                stream >> parameter;
                
                if ( stream.fail( ) )
                {
                    return default_value;
                }
                
                return parameter;
            }
            
            template< typename Type >
            static bool has_parameter( const std::string& name, const Type& parameters )
            {
                const auto key = String::lowercase( name );
                const auto iterator = std::find_if( parameters.begin( ), parameters.end( ), [ &key ]( const std::pair< std::string, std::string >& value )
                {
                    return ( key == String::lowercase( value.first ) );
                } );
                
                return iterator not_eq parameters.end( );
            }
            
            static std::string transform( const std::string& value, const std::function< std::string ( const std::string& ) >& transform )
            {
                return ( transform == nullptr ) ? value : transform( value );
            }

            static bool is_an_ipv6_address(const std::string& address) {
                std::string ipv6 =
                    "(?:"
                    // For the first 6 fields, match addresses with no jump (::)...
                    "  (?:                                              (?:[0-9a-f]{1,4}:){6}"
                    // ...or a jump.
                    "  |                                             :: (?:[0-9a-f]{1,4}:){5}"
                    "  | (?:                         [0-9a-f]{1,4})? :: (?:[0-9a-f]{1,4}:){4}"
                    "  | (?: (?:[0-9a-f]{1,4}:){0,1} [0-9a-f]{1,4})? :: (?:[0-9a-f]{1,4}:){3}"
                    "  | (?: (?:[0-9a-f]{1,4}:){0,2} [0-9a-f]{1,4})? :: (?:[0-9a-f]{1,4}:){2}"
                    "  | (?: (?:[0-9a-f]{1,4}:){0,3} [0-9a-f]{1,4})? :: (?:[0-9a-f]{1,4}:)   "
                    "  | (?: (?:[0-9a-f]{1,4}:){0,4} [0-9a-f]{1,4})? ::                      "
                    "  )                                                                     "
                    // Match the base10/16 addresses with no jump (suffix of above).
                    "  (?: [0-9a-f]{1,4} : [0-9a-f]{1,4}                                     "
                    "      | (?: (?: 25[0-5] | 2[0-4][0-9] | [01]?[0-9]?[0-9])\\.){3}        "
                    "        (?: (?: 25[0-5] | 2[0-4][0-9] | [01]?[0-9]?[0-9]))              "
                    "  )                                                                     "
                    // Not any above. Check to see if jump is between last 2 fields of addr.
                    "  | (?: (?:[0-9a-f]{1,4}:){0,5} [0-9a-f]{1,4})? :: [0-9a-f]{1,4}        "
                    "  | (?: (?:[0-9a-f]{1,4}:){0,6} [0-9a-f]{1,4})? ::                      "
                    ")";
                    // End of ipv6 string pattern.

                // Convert readable pattern above into the applicable regex pattern.
                ipv6.erase( remove_if ( ipv6.begin(), ipv6.end(), ::isspace ) , ipv6.end() );
                std::regex ipv6_pattern( ipv6 );
                return regex_search( address, ipv6_pattern );
            }
            
            //Getters
            template< typename Type >
            static Type get_parameters( const std::string& name, const Type& parameters )
            {
                if ( name.empty( ) )
                {
                    return parameters;
                }
                
                const auto key = String::lowercase( name );
                Type results;
                
                for ( const auto& parameter : parameters )
                {
                    if ( key == String::lowercase( parameter.first ) )
                    {
                        results.insert( parameter );
                    }
                }
                
                return results;
            }
            
            //Setters
            
            //Operators
            
            //Properties
            
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
            Common( void ) = delete;
            
            Common( const Common& original ) = delete;
            
            virtual ~Common( void ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            Common& operator =( const Common& value ) = delete;
            
            //Properties
    };
}
