/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_BASE_RULE_H
#define _RESTBED_BASE_RULE_H 1

//System Includes
#include <string>
#include <memory>
#include <functional>

//Project Includes
#include <restbed>

//External Includes

//System Namespaces
using std::string;
using std::function;
using std::shared_ptr;

//Project Namespaces
using namespace restbed;

//External Namespaces

class BaseRule : public Rule
{
    public:
        BaseRule( void ) : Rule( ),
            m_priority( 0 )
        {
            return;
        }

        BaseRule( const BaseRule& original ) : m_priority( original.m_priority )
        {
            return;
        }
        
        virtual ~BaseRule( void )
        {
            return;
        }
        
        virtual bool condition( const shared_ptr< Session >& session ) = 0;

        virtual void action( const shared_ptr< Session >& session, const function< void ( const shared_ptr< Session >& ) >& callback ) = 0;

        int get_priority( void ) const
        {
        	return m_priority;
        }
        
        void set_priority( const int value )
        {
        	m_priority = value;
        }

    private:
    	int m_priority;
};

#endif  /* _RESTBED_BASE_RULE_H */
