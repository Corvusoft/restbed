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
    
    class SETTINGS_EXPORT Settings
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            Settings( void );
            
            virtual ~Settings( void );
            
            //Functionality
            
            //Getters
            uint16_t get_port( void ) const;
            
            std::string get_root( void ) const;
#ifdef BUILD_IPC
            std::string get_ipc_path( void ) const;
#endif
            bool get_reuse_address( void ) const;
            
            unsigned int get_worker_limit( void ) const;
            
            unsigned int get_connection_limit( void ) const;
            
            std::string get_bind_address( void ) const;
            
            bool get_case_insensitive_uris( void ) const;
            
            std::chrono::milliseconds get_connection_timeout( void ) const;

            bool get_keep_alive( void ) const;

            uint32_t get_keep_alive_start( void ) const;

            uint32_t get_keep_alive_interval( void ) const;

            uint32_t get_keep_alive_cnt( void ) const;
            
            std::string get_status_message( const int code ) const;
            
            std::map< int, std::string > get_status_messages( void ) const;
            
            std::string get_property( const std::string& name ) const;
            
            std::map< std::string, std::string > get_properties( void ) const;
            
            std::shared_ptr< const SSLSettings > get_ssl_settings( void ) const;
            
            std::multimap< std::string, std::string > get_default_headers( void ) const;
            
            //Setters
            void set_port( const uint16_t value );
            
            void set_root( const std::string& value );
#ifdef BUILD_IPC
            void set_ipc_path( const std::string& value );
#endif
            void set_reuse_address( const bool value );
            
            void set_worker_limit( const unsigned int value );
            
            void set_connection_limit( const unsigned int value );
            
            void set_bind_address( const std::string& value );
            
            void set_case_insensitive_uris( const bool value );
            
            void set_connection_timeout( const std::chrono::seconds& value );
            
            void set_connection_timeout( const std::chrono::milliseconds& value );

            void set_keep_alive( bool value );

            void set_keep_alive_start( const uint32_t value );

            void set_keep_alive_interval( const uint32_t value );

            void set_keep_alive_cnt( const uint32_t value );
            
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
