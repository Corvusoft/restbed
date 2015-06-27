/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_SSL_SETTINGS_IMPL_H
#define _RESTBED_DETAIL_SSL_SETTINGS_IMPL_H 1

//System Includes
#include <string>

//Project Includes
#include "corvusoft/restbed/detail/settings_impl.hpp"

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    namespace detail
    {
        //Forward Declarations
        
        class SSLSettingsImpl : public SettingsImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                SSLSettingsImpl( void );
                
                virtual ~SSLSettingsImpl( void );
                
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
                SSLSettingsImpl( const SSLSettingsImpl& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                SSLSettingsImpl& operator =( const SSLSettingsImpl& value ) = delete;
                
                //Properties
        };
    }
}

#endif  /* _RESTBED_DETAIL_SSL_SETTINGS_IMPL_H */
