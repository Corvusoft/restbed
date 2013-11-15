/*
 * Copyright (c) 2013 Corvusoft
 */

#ifndef _RESTBED_METHOD_H
#define _RESTBED_METHOD_H 1

//System Includes
#include <memory>
#include <string>
 
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
        class MethodImpl;
    }

    class Method
    {
        public:
            //Friends
            
            //Definitions

            //Constructors
            Method( const char* value );
            
            Method( const std::string& value );
            
            Method( const Method& original );

            virtual ~Method( void );

            //Functionality
            std::string to_string( void ) const;
        
            static Method parse( const std::string& value );

            //Getters

            //Setters

            //Operators
            Method& operator =( const Method& rhs );

            bool operator <( const Method& rhs ) const;
            
            bool operator >( const Method& rhs ) const;
            
            bool operator ==( const Method& rhs ) const;
            
            bool operator !=( const Method& rhs ) const;

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
            
            //Functionality
            Method( void );
        
            //Getters
            
            //Setters
            
            //Operators

            //Properties
            std::unique_ptr< detail::MethodImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_METHOD_H */
