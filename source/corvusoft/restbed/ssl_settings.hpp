/*
 * Copyright 2013-2020, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <string>
#include <memory>
#include <cstdint>

//Project Includes

//External Includes

//Windows DLL Exports
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#ifdef WIN_DLL_EXPORT
		#define SSL_SETTINGS_EXPORT __declspec(dllexport)
	#else
		#define SSL_SETTINGS_EXPORT __declspec(dllimport)
	#endif
#else
	#define SSL_SETTINGS_EXPORT __attribute__((visibility ("default")))
#endif

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Uri;
    
    namespace detail
    {
        struct SSLSettingsImpl;
    }
    
    class SSLSettings
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            SSL_SETTINGS_EXPORT SSLSettings( void );
            
            SSL_SETTINGS_EXPORT virtual ~SSLSettings( void );
            
            //Functionality
            SSL_SETTINGS_EXPORT bool has_disabled_http( void ) const;
            
            SSL_SETTINGS_EXPORT bool has_enabled_sslv2( void ) const;
            
            SSL_SETTINGS_EXPORT bool has_enabled_sslv3( void ) const;
            
            SSL_SETTINGS_EXPORT bool has_enabled_tlsv1( void ) const;
            
            SSL_SETTINGS_EXPORT bool has_enabled_tlsv11( void ) const;
            
            SSL_SETTINGS_EXPORT bool has_enabled_tlsv12( void ) const;
            
            SSL_SETTINGS_EXPORT bool has_enabled_compression( void ) const;
            
            SSL_SETTINGS_EXPORT bool has_enabled_default_workarounds( void ) const;
            
            SSL_SETTINGS_EXPORT bool has_enabled_single_diffie_hellman_use( void ) const;
            
            //Getters
            SSL_SETTINGS_EXPORT uint16_t get_port( void ) const;
            
            SSL_SETTINGS_EXPORT std::string get_bind_address( void ) const;
            
            SSL_SETTINGS_EXPORT std::string get_certificate( void ) const;
            
            SSL_SETTINGS_EXPORT std::string get_passphrase( void ) const;
            
            SSL_SETTINGS_EXPORT std::string get_private_key( void ) const;
            
            SSL_SETTINGS_EXPORT std::string get_private_rsa_key( void ) const;
            
            SSL_SETTINGS_EXPORT std::string get_certificate_chain( void ) const;
            
            SSL_SETTINGS_EXPORT std::string get_temporary_diffie_hellman( void ) const;
            
            SSL_SETTINGS_EXPORT std::string get_certificate_authority_pool( void ) const;
            
            //Setters
            SSL_SETTINGS_EXPORT void set_port( const uint16_t value );
            
            SSL_SETTINGS_EXPORT void set_bind_address( const std::string& value );
            
            SSL_SETTINGS_EXPORT void set_http_disabled( const bool value );
            
            SSL_SETTINGS_EXPORT void set_sslv2_enabled( const bool value );
            
            SSL_SETTINGS_EXPORT void set_sslv3_enabled( const bool value );
            
            SSL_SETTINGS_EXPORT void set_tlsv1_enabled( const bool value );
            
            SSL_SETTINGS_EXPORT void set_tlsv11_enabled( const bool value );
            
            SSL_SETTINGS_EXPORT void set_tlsv12_enabled( const bool value );
            
            SSL_SETTINGS_EXPORT void set_compression_enabled( const bool value );
            
            SSL_SETTINGS_EXPORT void set_default_workarounds_enabled( const bool value );
            
            SSL_SETTINGS_EXPORT void set_single_diffie_hellman_use_enabled( const bool value );
            
            SSL_SETTINGS_EXPORT void set_certificate( const Uri& value );
            
            SSL_SETTINGS_EXPORT void set_certificate_chain( const Uri& value );
            
            SSL_SETTINGS_EXPORT void set_certificate_authority_pool( const Uri& value );
            
            SSL_SETTINGS_EXPORT void set_passphrase( const std::string& value );
            
            SSL_SETTINGS_EXPORT void set_private_key( const Uri& value );
            
            SSL_SETTINGS_EXPORT void set_private_rsa_key( const Uri& value );
            
            SSL_SETTINGS_EXPORT void set_temporary_diffie_hellman( const Uri& value );
            
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
