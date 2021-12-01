/*
 * Copyright 2013-2020, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <memory>
#include <functional>

//Project Includes

//External Includes

//Windows DLL Exports
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#ifdef WIN_DLL_EXPORT
		#define RULE_EXPORT __declspec(dllexport)
	#else
		#define RULE_EXPORT __declspec(dllimport)
	#endif
#else
	#define RULE_EXPORT __attribute__((visibility ("default")))
#endif

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
    
    class RULE_EXPORT Rule
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
