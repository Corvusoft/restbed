/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_DETAIL_METHOD_IMPL_H
#define _RESTBED_DETAIL_METHOD_IMPL_H 1

//System Includes
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
        //Forward Declarations
        
        class MethodImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                MethodImpl( const char* value );
                
                MethodImpl( const std::string& value );
                
                MethodImpl( const MethodImpl& original );
                
                virtual ~MethodImpl( void );
                
                //Functionality
                std::string to_string( void ) const;
                
                //Getters
                
                //Setters
                
                //Operators
                bool operator <( const MethodImpl& value ) const;
                
                bool operator >( const MethodImpl& value ) const;
                
                bool operator ==( const MethodImpl& value ) const;
                
                bool operator !=( const MethodImpl& value ) const;
                
                MethodImpl& operator =( const MethodImpl& value );
                
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
                void setup( const std::string& value );
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                std::string m_value;
        };
    }
}

#endif  /* _RESTBED_DETAIL_METHOD_IMPL_H */
