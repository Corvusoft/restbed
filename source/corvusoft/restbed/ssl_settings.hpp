/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_SSL_SETTINGS_H
#define _RESTBED_SSL_SETTINGS_H 1

//System Includes
#include <map>
#include <chrono>
#include <memory>
#include <string>

//Project Includes
#include <corvusoft/restbed/settings>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    namespace detail
    {
        class SSLSettingsImpl;
    }
    
    class SSLSettings : public Settings
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            SSLSettings( void );
            
            virtual ~SSLSettings( void );
            
            //Functionality
            
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
            SSLSettings( const SSLSettings& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            SSLSettings& operator =( const SSLSettings& value ) = delete;
            
            //Properties
            std::unique_ptr< detail::SSLSettingsImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_SSL_SETTINGS_H */
