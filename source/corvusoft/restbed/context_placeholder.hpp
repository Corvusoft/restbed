/*
 * Copyright 2013-2025, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <typeinfo>

//Project Includes
#include <corvusoft/restbed/context_placeholder_base.hpp>

//External Includes

//Windows DLL Exports
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#ifdef WIN_DLL_EXPORT
		#define CONTEXT_PLACEHOLDER_EXPORT __declspec(dllexport)
	#else
		#define CONTEXT_PLACEHOLDER_EXPORT __declspec(dllimport)
	#endif
#else
	#define CONTEXT_PLACEHOLDER_EXPORT __attribute__((visibility ("default")))
#endif

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    template< typename Type  >
    class ContextPlaceholder : public ContextPlaceholderBase
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructor
            CONTEXT_PLACEHOLDER_EXPORT ContextPlaceholder( const Type& value ) : ContextPlaceholderBase( ),
                m_value( value )
            {
                return;
            }
            
            CONTEXT_PLACEHOLDER_EXPORT virtual ~ContextPlaceholder( void )
            {
                return;
            }
            
            //Functionality
            
            //Getters
            CONTEXT_PLACEHOLDER_EXPORT const std::type_info& type( void ) const
            {
                return typeid( Type );
            }
            
            //Setters
            
            //Operators
            CONTEXT_PLACEHOLDER_EXPORT operator Type( void )
            {
                return m_value;
            }
            
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
            ContextPlaceholder( void ) = delete;
            
            ContextPlaceholder( const ContextPlaceholder& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            ContextPlaceholder& operator =( const ContextPlaceholder& value ) = delete;
            
            //Properties
            const Type m_value;
    };
}
