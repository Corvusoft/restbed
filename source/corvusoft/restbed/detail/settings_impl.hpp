/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_SETTINGS_IMPL_H
#define _RESTBED_DETAIL_SETTINGS_IMPL_H 1

//System Includes
#include <map>
#include <string>
#include <memory>
#include <chrono>
#include <cstdint>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class SSLSettings;

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
                
                std::string get_status_message( const int code ) const;
                
                std::map< int, std::string > get_status_messages( void ) const;
                
                std::string get_property( const std::string& name ) const;
                
                std::map< std::string, std::string > get_properties( void ) const;

                std::shared_ptr< const SSLSettings > get_ssl_settings( void ) const;
                
                std::multimap< std::string, std::string > get_default_headers( void ) const;
                
                //Setters
                void set_port( const uint16_t value );
                
                void set_root( const std::string& value );
                
                void set_connection_limit( const int32_t value );
                
                void set_connection_timeout( const std::chrono::seconds& value );
                
                void set_status_message( const int code, const std::string& message );
                
                void set_status_messages( const std::map< int, std::string >& values );
                
                void set_property( const std::string& name, const std::string& value );
                
                void set_properties( const std::map< std::string, std::string >& values );

                void set_ssl_settings( const std::shared_ptr< const SSLSettings >& value );
                
                void set_default_header( const std::string& name, const std::string& value );
                
                void set_default_headers( const std::multimap< std::string, std::string >& values );
                
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
                uint16_t m_port;
                
                std::string m_root;
                
                uint32_t m_connection_limit;
                
                std::chrono::seconds m_connection_timeout;
                
                std::map< int, std::string > m_status_messages;
                
                std::map< std::string, std::string > m_properties;

                std::shared_ptr< const SSLSettings > m_ssl_settings;
                
                std::multimap< std::string, std::string > m_default_headers;
        };
    }
}

#endif  /* _RESTBED_DETAIL_SETTINGS_IMPL_H */
