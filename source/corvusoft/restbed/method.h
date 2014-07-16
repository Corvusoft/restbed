/*
 * Copyright (c) 2013, 2014 Corvusoft
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
        
            Method( const detail::MethodImpl& implementation );
            
            virtual ~Method( void );
            
            //Functionality
            std::string to_string( void ) const;
            
            static Method parse( const std::string& value );
            
            //Getters
            
            //Setters
            
            //Operators
            Method& operator =( const Method& value );
            
            bool operator <( const Method& value ) const;
            
            bool operator >( const Method& value ) const;
            
            bool operator ==( const Method& value ) const;
            
            bool operator !=( const Method& value ) const;
            
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
