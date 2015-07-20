/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_RULE_H
#define _RESTBED_RULE_H 1

//System Includes
#include <functional>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Session;
    
    class Rule
    {
        public:
            //Friends
            
            //Definitions

            //Constructors
            
            //Functionality
            virtual bool condition( const std::shared_ptr< Session >& session ) = 0;

            virtual void action( const std::shared_ptr< Session >& session, const std::function< void ( const std::shared_ptr< Session >& ) >& callback ) = 0;

            //Getters
            virtual int get_priority( void ) const = 0;
            
            //Setters
            virtual void set_priority( const int value ) = 0;

            //Operators
            
            //Properties
            
        protected:
            //Friends
            
            //Definitions
            
            //Constructors
            Rule( void ) = default;
            
            Rule( const Rule& ) = default;

            virtual ~Rule( void ) = default;

            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            Rule& operator =( const Rule& ) = default;
            
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
    };
}

#endif  /* _RESTBED_RULE_H */
