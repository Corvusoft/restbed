/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_CONTEXT_PLACEHOLDER_BASE_H
#define _RESTBED_CONTEXT_PLACEHOLDER_BASE_H 1

//System Includes
#include <typeinfo>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    class ContextPlaceholderBase
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructor
            
            //Functionality
            
            //Getters
            virtual const std::type_info& type( void ) const = 0;
            
            //Setters
            
            //Operators
            
            //Properties
            
        protected:
            //Friends
            
            //Definitions
            
            //Constructors
            ContextPlaceholderBase( void ) = default;
            
            virtual ~ContextPlaceholderBase( void ) = default;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            
            //Properties
            
        private:
            //Friends
            
            //Definitions
            
            //Constructors
            ContextPlaceholderBase( const ContextPlaceholderBase& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            ContextPlaceholderBase& operator =( const ContextPlaceholderBase& value ) = delete;
            
            //Properties
    };
}

#endif  /* _RESTBED_CONTEXT_PLACEHOLDER_BASE_H */
