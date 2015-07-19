/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_RULE_H
#define _RESTBED_RULE_H 1

//System Includes
#include <memory>
#include <functional>

//Project Includes
#include <corvusoft/restbed/byte.hpp>

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
    	class RuleImpl;
    }
    
    class Rule
    {
        public:
            //Friends
            
            //Definitions
            enum Type : int
		    {
		    	ALL = 000,
		        BODY = 100,
		        PATH = 200,
		        QUERY = 300,
		        METHOD = 400,
		        HEADER = 500,
		        VERSION = 600,
		        PROTOCOL = 700
		    };

            //Constructors
            Rule( const Type type = ALL );

            Rule( const Rule& original );
            
            virtual ~Rule( void );
            
            //Functionality
            bool is_mandatory( void ) const;

            virtual bool condition( const Bytes& value ) = 0;

            virtual void action( const std::shared_ptr< Session >& session, std::function< void ( const std::shared_ptr< Session >& ) >& callback ) = 0;

            //Getters
            Type get_type( void ) const;

            int get_priority( void ) const;
            
            //Setters
            void set_priority( const int value );

            void set_mandatory( const bool value );

            //Operators
            Rule& operator =( const Rule& value );
            
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
            std::unique_ptr< detail::RuleImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_RULE_H */
