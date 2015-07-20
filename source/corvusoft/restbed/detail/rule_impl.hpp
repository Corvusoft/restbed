/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_RULE_H
#define _RESTBED_DETAIL_RULE_H 1

//System Includes
#include <functional>

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/rule.hpp>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Session;

    namespace detail
    {
        class RuleImpl
        {
            public:
                //Friends
                
                //Definitions

                //Constructors
                RuleImpl( const Rule::Type type );

                RuleImpl( const RuleImpl& original );
                
                virtual ~RuleImpl( void );
                
                //Functionality
                bool is_mandatory( void ) const;

                //Getters
                Rule::Type get_type( void ) const;

                int get_priority( void ) const;
                
                //Setters
                void set_priority( const int value );

                void set_mandatory( const bool value );

                //Operators
                RuleImpl& operator =( const RuleImpl& value );
                
                bool operator >( const RuleImpl& value ) const;

                bool operator <( const RuleImpl& value ) const;

                bool operator ==( const RuleImpl& value ) const;

                bool operator !=( const RuleImpl& value ) const;
                
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
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                int m_priority;

                bool m_mandatory;

                Rule::Type m_type;
        };
    }
}

#endif  /* _RESTBED_DETAIL_RULE_H */
