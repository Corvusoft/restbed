/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
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
