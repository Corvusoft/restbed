/*
 * Copyright 2013-2020, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <type_traits>

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
            static int inline parse_number( const std::string& value, const int default_value )
            {
                try
                {
                    return std::stoi( value );
                }
                catch ( ... )
                {
                    return default_value;
                }
            }

            static long inline parse_number( const std::string& value, const long default_value )
            {
                try
                {
                    return std::stol( value );
                }
                catch ( ... )
                {
                    return default_value;
                }
            }

            static long long inline parse_number( const std::string& value, const long long default_value )
            {
                try
                {
                    return std::stoll( value );
                }
                catch ( ... )
                {
                    return default_value;
                }
            }

            static unsigned long inline parse_number( const std::string& value, const unsigned long default_value )
            {
                try
                {
                    return std::stoul( value );
                }
                catch ( ... )
                {
                    return default_value;
                }
            }

            static unsigned long long inline parse_number( const std::string& value, const unsigned long long default_value )
            {
                try
                {
                    return std::stoull( value );
                }
                catch ( ... )
                {
                    return default_value;
                }
            }

            static float inline parse_number( const std::string& value, const float default_value )
            {
                try
                {
                    return std::stof( value );
                }
                catch ( ... )
                {
                    return default_value;
                }
            }

            static double inline parse_number( const std::string& value, const double default_value )
            {
                try
                {
                    return std::stod( value );
                }
                catch ( ... )
                {
                    return default_value;
                }
            }

            static long double inline parse_number( const std::string& value, const long double default_value )
            {
                try
                {
                    return std::stold( value );
                }
                catch ( ... )
                {
                    return default_value;
                }
            }

            template< typename Type >
            static inline Type parse_parameter( const std::string& value, const Type default_value )
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


    template<>
    inline std::string Common::parse_parameter( const std::string& value, const std::string )
    {
        return value;
    }

    template<>
    inline bool Common::parse_parameter( const std::string& value, const bool default_value )
    {
        // true / false
        //  yes / no
        //   1 /  0
        if ( value == "false" || value == "FALSE" || value == "0" || value == "no" || value == "NO" )
        {
            return false;
        }
        if ( value == "true" || value == "TRUE" || value == "1" || value == "yes" || value == "YES" )
        {
            return true;
        }
        return default_value;
    }

    template<>
    inline int Common::parse_parameter( const std::string& value, const int default_value )
    {
        return Common::parse_number( value, default_value );
    }

    template<>
    inline long Common::parse_parameter( const std::string& value, const long default_value )
    {
        return Common::parse_number( value, default_value );
    }

    template<>
    inline long long Common::parse_parameter( const std::string& value, const long long default_value )
    {
        return Common::parse_number( value, default_value );
    }

    template<>
    inline unsigned long Common::parse_parameter( const std::string& value, const unsigned long default_value )
    {
        return Common::parse_number( value, default_value );
    }

    template<>
    inline unsigned long long Common::parse_parameter( const std::string& value, const unsigned long long default_value )
    {
        return Common::parse_number( value, default_value );
    }

    template<>
    inline float Common::parse_parameter( const std::string& value, const float default_value )
    {
        return Common::parse_number( value, default_value );
    }

    template<>
    inline double Common::parse_parameter( const std::string& value, const double default_value )
    {
        return Common::parse_number( value, default_value );
    }
    
    template<>
    inline long double Common::parse_parameter( const std::string& value, const long double default_value )
    {
        return Common::parse_number( value, default_value );
    }

}
