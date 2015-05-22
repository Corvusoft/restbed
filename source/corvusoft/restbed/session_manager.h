/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_SESSION_MANAGER_H
#define _RESTBED_SESSION_MANAGER_H 1

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
    
    class SessionManager
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            SessionManager( const Settings& settings );
            
            virtual ~SessionManager( void );
            
            //Functionality
            virtual void create( const std::function< void ( const std::shared_ptr< Session >& ) >& callback ) = 0;

            // virtual void load( std::shared_ptr< Session >& session ) = 0;

            //Getters

            //Setters
            
            //Operators
            
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
            SessionManager( void ) = delete;

            SessionManager( const SessionManager& original ) = delete;

            //Functionality

            //Getters
            
            //Setters
            
            //Operators
            SessionManager& operator =( const SessionManager& value ) = delete;
            
            //Properties
    };
}

#endif  /* _RESTBED_SESSION_MANAGER_H */
