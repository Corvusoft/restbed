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
            SessionManager( void );
            
            virtual ~SessionManager( void );
            
            //Functionality
            virtual void stop( void );
            
            virtual void start( const std::shared_ptr< const Settings >& settings );
            
            virtual void create( const std::function< void ( const std::shared_ptr< Session > ) >& callback );
            
            virtual void load( const std::shared_ptr< Session > session, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
            
            virtual void save( const std::shared_ptr< Session > session, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
            
            //Getters
            
            //Setters
            
            //Operators
            
            //Properties
            
        protected:
            //Friends
            
            //Definitions
            
            //Constructors
            SessionManager( const SessionManager& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            SessionManager& operator =( const SessionManager& value ) = delete;
            
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
