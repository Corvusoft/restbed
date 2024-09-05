/*
 * Copyright 2013-2020, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <chrono>
#include <memory>
#include <string>
#include <cstdint>

//Project Includes

//External Includes

//Windows DLL Exports
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#ifdef WIN_DLL_EXPORT
		#define SETTINGS_EXPORT __declspec(dllexport)
	#else
		#define SETTINGS_EXPORT __declspec(dllimport)
	#endif
#else
	#define SETTINGS_EXPORT __attribute__((visibility ("default")))
#endif

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class SSLSettings;
    
    namespace detail
    {
        struct SettingsImpl;
    }
    
    class Settings
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            SETTINGS_EXPORT Settings( void );
            
            SETTINGS_EXPORT virtual ~Settings( void );
            
            //Functionality
            
            //Getters
            SETTINGS_EXPORT uint16_t get_port( void ) const;
            
            SETTINGS_EXPORT std::string get_root( void ) const;
#ifdef BUILD_IPC
            SETTINGS_EXPORT std::string get_ipc_path( void ) const;
#endif
            SETTINGS_EXPORT bool get_reuse_address( void ) const;
            
            SETTINGS_EXPORT unsigned int get_worker_limit( void ) const;
            
            SETTINGS_EXPORT unsigned int get_connection_limit( void ) const;
            
            SETTINGS_EXPORT std::string get_bind_address( void ) const;
            
            SETTINGS_EXPORT bool get_case_insensitive_uris( void ) const;
            
            SETTINGS_EXPORT std::chrono::milliseconds get_connection_timeout( void ) const;

            SETTINGS_EXPORT bool get_keep_alive( void ) const;

            SETTINGS_EXPORT uint32_t get_keep_alive_start( void ) const;

            SETTINGS_EXPORT uint32_t get_keep_alive_interval( void ) const;

            SETTINGS_EXPORT uint32_t get_keep_alive_cnt( void ) const;
            
            SETTINGS_EXPORT std::string get_status_message( const int code ) const;
            
            SETTINGS_EXPORT std::map< int, std::string > get_status_messages( void ) const;
            
            SETTINGS_EXPORT std::string get_property( const std::string& name ) const;
            
            SETTINGS_EXPORT std::map< std::string, std::string > get_properties( void ) const;
            
            SETTINGS_EXPORT std::shared_ptr< const SSLSettings > get_ssl_settings( void ) const;
            
            SETTINGS_EXPORT std::multimap< std::string, std::string > get_default_headers( void ) const;
            
            //Setters
            SETTINGS_EXPORT void set_port( const uint16_t value );
            
            SETTINGS_EXPORT void set_root( const std::string& value );
#ifdef BUILD_IPC
            SETTINGS_EXPORT void set_ipc_path( const std::string& value );
#endif
            SETTINGS_EXPORT void set_reuse_address( const bool value );
            
            SETTINGS_EXPORT void set_worker_limit( const unsigned int value );
            
            SETTINGS_EXPORT void set_connection_limit( const unsigned int value );
            
            SETTINGS_EXPORT void set_bind_address( const std::string& value );
            
            SETTINGS_EXPORT void set_case_insensitive_uris( const bool value );
            
            SETTINGS_EXPORT void set_connection_timeout( const std::chrono::seconds& value );
            
            SETTINGS_EXPORT void set_connection_timeout( const std::chrono::milliseconds& value );

            SETTINGS_EXPORT void set_keep_alive( bool value );

            SETTINGS_EXPORT void set_keep_alive_start( const uint32_t value );

            SETTINGS_EXPORT void set_keep_alive_interval( const uint32_t value );

            SETTINGS_EXPORT void set_keep_alive_cnt( const uint32_t value );
            
            SETTINGS_EXPORT void set_status_message( const int code, const std::string& message );
            
            SETTINGS_EXPORT void set_status_messages( const std::map< int, std::string >& values );
            
            SETTINGS_EXPORT void set_property( const std::string& name, const std::string& value );
            
            SETTINGS_EXPORT void set_properties( const std::map< std::string, std::string >& values );
            
            SETTINGS_EXPORT void set_ssl_settings( const std::shared_ptr< const SSLSettings >& value );
            
            SETTINGS_EXPORT void set_default_header( const std::string& name, const std::string& value );
            
            SETTINGS_EXPORT void set_default_headers( const std::multimap< std::string, std::string >& values );
            
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
            Settings( const Settings& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            Settings& operator =( const Settings& value ) = delete;
            
            //Properties
            std::unique_ptr< detail::SettingsImpl > m_pimpl;
    };
}
