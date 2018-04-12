/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

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
