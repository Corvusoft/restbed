/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_CONTEXT_PLACEHOLDER_H
#define _RESTBED_CONTEXT_PLACEHOLDER_H 1

//System Includes
#include <typeinfo>

//Project Includes
#include <corvusoft/restbed/context_placeholder_base.hpp>

//External Includes

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
            ContextPlaceholder( const Type& value ) : ContextPlaceholderBase( ),
                m_value( value )
            {
                return;
            }
            
            virtual ~ContextPlaceholder( void )
            {
                return;
            }
            
            //Functionality
            
            //Getters
            const std::type_info& type( void ) const
            {
                return typeid( Type );
            }
            
            //Setters
            
            //Operators
            operator Type( void )
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

#endif  /* _RESTBED_CONTEXT_PLACEHOLDER_H */
