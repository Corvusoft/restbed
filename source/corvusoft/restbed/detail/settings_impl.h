/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_SETTINGS_IMPL_H
#define _RESTBED_DETAIL_SETTINGS_IMPL_H 1

//System Includes
#include <map>
#include <string>
#include <chrono>

//Project Includes

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
        
        class SettingsImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                SettingsImpl( void );

                virtual ~SettingsImpl( void );
                
                //Functionality
                
                //Getters
                uint16_t get_port( void ) const;
                
                std::string get_root( void ) const;
                
                int32_t get_connection_limit( void ) const;

                std::chrono::seconds get_connection_timeout( void ) const;
                
                std::string get_property( const std::string& name ) const;
                
                std::map< std::string, std::string > get_properties( void ) const;
                
                //Setters
                void set_port( const uint16_t value );
                
                void set_root( const std::string& value );
                
                void set_connection_limit( const int32_t value );

                void set_connection_timeout( const std::chrono::seconds& value );
                
                void set_property( const std::string& name, const std::string& value );
                
                void set_properties( const std::map< std::string, std::string >& values );
                
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
                SettingsImpl( const SettingsImpl& original ) = delete;

                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                SettingsImpl& operator =( const SettingsImpl& value ) = delete;
                
                //Properties
                std::map< std::string, std::string > m_properties;
        };
    }
}

#endif  /* _RESTBED_DETAIL_SETTINGS_IMPL_H */
