
#ifndef _EXAMPLE_BASE_RULE_H
#define _EXAMPLE_BASE_RULE_H 1

#include <string>
#include <memory>
#include <functional>
#include <restbed>

using namespace std;
using namespace restbed;

class ExampleBaseRule : public Rule
{
    public:
        ExampleBaseRule( void ) : Rule( ),
            m_priority( 0 )
        {
            return;
        }

        ExampleBaseRule( const ExampleBaseRule& original ) : m_priority( original.m_priority )
        {
            return;
        }
        
        virtual ~ExampleBaseRule( void )
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

#endif  /* _EXAMPLE_BASE_RULE_H */
