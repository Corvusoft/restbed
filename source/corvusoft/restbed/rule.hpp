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
            Rule( void ) = default;

            Rule( const Rule& original ) = default;
            
            virtual ~Rule( void ) = default;
            
            //Functionality
            virtual bool condition( const std::shared_ptr< Session >& session ) = 0;

            virtual void action( const std::shared_ptr< Session >& session, const std::function< void ( const std::shared_ptr< Session >& ) >& callback ) = 0;

            //Getters
            virtual int get_priority( void ) const = 0;
            
            //Setters
            virtual void set_priority( const int value ) = 0;

            //Operators
            virtual Rule& operator =( const Rule& value ) = 0;
            
            virtual bool operator >( const Rule& value ) const = 0;

            virtual bool operator <( const Rule& value ) const = 0;

            virtual bool operator ==( const Rule& value ) const = 0;

            virtual bool operator !=( const Rule& value ) const = 0;
            
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
    };
}

#endif  /* _RESTBED_RULE_H */
