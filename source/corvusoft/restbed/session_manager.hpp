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
		#define SESSION_MANAGER_EXPORT __declspec(dllexport)
	#else
		#define SESSION_MANAGER_EXPORT __declspec(dllimport)
	#endif
#else
	#define SESSION_MANAGER_EXPORT __attribute__((visibility ("default")))
#endif

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Session;
    class Settings;
    
    namespace detail
    {
        struct SessionManagerImpl;
    }
    
    class SessionManager
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            SESSION_MANAGER_EXPORT SessionManager( void );
            
            SESSION_MANAGER_EXPORT virtual ~SessionManager( void );
            
            //Functionality
            SESSION_MANAGER_EXPORT virtual void stop( void );
            
            SESSION_MANAGER_EXPORT virtual void start( const std::shared_ptr< const Settings >& settings );
            
            SESSION_MANAGER_EXPORT virtual void create( const std::function< void ( const std::shared_ptr< Session > ) >& callback );
            
            SESSION_MANAGER_EXPORT virtual void load( const std::shared_ptr< Session > session, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
            
            SESSION_MANAGER_EXPORT virtual void save( const std::shared_ptr< Session > session, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
            
            //Getters
            
            //Setters
            
            //Operators
            
            //Properties
            
        protected:
            //Friends
            
            //Definitions
            
            //Constructors
            SESSION_MANAGER_EXPORT SessionManager( const SessionManager& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            SESSION_MANAGER_EXPORT SessionManager& operator =( const SessionManager& value ) = delete;
            
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
