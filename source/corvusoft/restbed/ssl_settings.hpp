/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <string>
#include <memory>
#include <cstdint>

//Project Includes

//External Includes

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
            SSLSettings( void );
            
            virtual ~SSLSettings( void );
            
            //Functionality
            bool has_disabled_http( void ) const;
            
            bool has_enabled_sslv2( void ) const;
            
            bool has_enabled_sslv3( void ) const;
            
            bool has_enabled_tlsv1( void ) const;
            
            bool has_enabled_tlsv11( void ) const;
            
            bool has_enabled_tlsv12( void ) const;
            
            bool has_enabled_compression( void ) const;
            
            bool has_enabled_default_workarounds( void ) const;
            
            bool has_enabled_single_diffie_hellman_use( void ) const;
            
            //Getters
            uint16_t get_port( void ) const;
            
            std::string get_bind_address( void ) const;
            
            std::string get_certificate( void ) const;
            
            std::string get_passphrase( void ) const;
            
            std::string get_private_key( void ) const;
            
            std::string get_private_rsa_key( void ) const;
            
            std::string get_certificate_chain( void ) const;
            
            std::string get_temporary_diffie_hellman( void ) const;
            
            std::string get_certificate_authority_pool( void ) const;
            
            //Setters
            void set_port( const uint16_t value );
            
            void set_bind_address( const std::string& value );
            
            void set_http_disabled( const bool value );
            
            void set_sslv2_enabled( const bool value );
            
            void set_sslv3_enabled( const bool value );
            
            void set_tlsv1_enabled( const bool value );
            
            void set_tlsv11_enabled( const bool value );
            
            void set_tlsv12_enabled( const bool value );
            
            void set_compression_enabled( const bool value );
            
            void set_default_workarounds_enabled( const bool value );
            
            void set_single_diffie_hellman_use_enabled( const bool value );
            
            void set_certificate( const Uri& value );
            
            void set_certificate_chain( const Uri& value );
            
            void set_certificate_authority_pool( const Uri& value );
            
            void set_passphrase( const std::string& value );
            
            void set_private_key( const Uri& value );
            
            void set_private_rsa_key( const Uri& value );
            
            void set_temporary_diffie_hellman( const Uri& value );
            
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
