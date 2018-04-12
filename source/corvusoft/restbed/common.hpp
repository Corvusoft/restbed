/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <string>
#include <set>
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
            template <class T>
            class VectorSet
            {
                private:
                  std::vector<T> theVector;
                  std::set<T>    theSet;
                public:
                  using iterator                     = typename std::vector<T>::iterator;
                  using const_iterator               = typename std::vector<T>::const_iterator;
                  iterator begin()                   { return theVector.begin(); }
                  iterator end()                     { return theVector.end(); }
                  const_iterator begin() const       { return theVector.begin(); }
                  const_iterator end() const         { return theVector.end(); }
                  const T& front() const             { return theVector.front(); }
                  const T& back() const              { return theVector.back(); }
                  void insert(const T& item)         { if (theSet.insert(item).second) theVector.push_back(item); }
                  size_t count(const T& item) const  { return theSet.count(item); }
                  bool empty() const                 { return theSet.empty(); }
                  size_t size() const                { return theSet.size(); }
                  VectorSet<T> operator=(const VectorSet<T>& rho) {
                    if (this == &rho) return *this;
                    theSet = rho.theSet;
                    theVector = rho.theVector;
                    return *this;
                  }
                  VectorSet<T> operator=(std::initializer_list<T> rho) {
                    theSet.insert(rho.begin(), rho.end());
                    theVector.assign(rho.begin(), rho.end());
                    return *this;
                  }
            };

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
