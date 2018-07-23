/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <memory>
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
    
    namespace detail
    {
        struct RuleImpl;
    }
    
    class Rule
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            
            //Functionality
            virtual bool condition( const std::shared_ptr< Session > session );
            
            virtual void action( const std::shared_ptr< Session > session, const std::function< void ( const std::shared_ptr< Session > ) >& callback ) = 0;
            
            //Getters
            int get_priority( void ) const;
            
            //Setters
            void set_priority( const int value );
            
            //Operators
            
            //Properties
            
        protected:
            //Friends
            
            //Definitions
            
            //Constructors
            Rule( void );
            
            virtual ~Rule( void );
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            
            //Properties
            
        private:
            //Friends
            
            //Definitions
            
            //Constructors
            explicit Rule( const Rule& ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            Rule& operator =( const Rule& ) = delete;
            
            //Properties
            std::unique_ptr< detail::RuleImpl > m_pimpl;
    };
}
