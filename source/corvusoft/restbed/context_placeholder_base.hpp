/*
 * Copyright 2013-2025, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <typeinfo>

//Project Includes

//External Includes

//Windows DLL Exports
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#ifdef WIN_DLL_EXPORT
		#define CONTEXT_PLACEHOLDER_BASE_EXPORT __declspec(dllexport)
	#else
		#define CONTEXT_PLACEHOLDER_BASE_EXPORT __declspec(dllimport)
	#endif
#else
	#define CONTEXT_PLACEHOLDER_BASE_EXPORT __attribute__((visibility ("default")))
#endif

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
            CONTEXT_PLACEHOLDER_BASE_EXPORT virtual const std::type_info& type( void ) const = 0;
            
            //Setters
            
            //Operators
            
            //Properties
            
        protected:
            //Friends
            
            //Definitions
            
            //Constructors
            CONTEXT_PLACEHOLDER_BASE_EXPORT ContextPlaceholderBase( void ) = default;
            
            CONTEXT_PLACEHOLDER_BASE_EXPORT virtual ~ContextPlaceholderBase( void ) = default;
            
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
