/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_SSL_SETTINGS_IMPL_H
#define _RESTBED_DETAIL_SSL_SETTINGS_IMPL_H 1

//System Includes
#include <string>
#include <functional>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces
namespace framework
{
    class Uri;
}

namespace restbed
{
    //Forward Declarations
    
    namespace detail
    {
        //Forward Declarations
        
        class SSLSettingsImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                SSLSettingsImpl( void );
                
                virtual ~SSLSettingsImpl( void );
                
                //Functionality
                bool has_enabled_sslv2( void ) const;

                bool has_enabled_sslv3( void ) const;

                bool has_enabled_tlsv1( void ) const;

                bool has_enabled_tlsv11( void ) const;

                bool has_enabled_tlsv12( void ) const;

                bool has_enabled_compression( void ) const;

                bool has_enabled_default_workarounds( void ) const;

                bool has_enabled_single_diffie_hellman_use( void ) const;
                
                //Getters
                std::string get_certificate( void ) const;

                std::string get_private_key( void ) const;

                std::string get_private_rsa_key( void ) const;

                std::string get_certificate_chain( void ) const;
                
                std::string get_temporary_diffie_hellman( void ) const;

                std::string get_certificate_authority_pool( void ) const;

                //Setters
                void set_sslv2_enabled( const bool value );

                void set_sslv3_enabled( const bool value );

                void set_tlsv1_enabled( const bool value );

                void set_tlsv11_enabled( const bool value );

                void set_tlsv12_enabled( const bool value );

                void set_compression_enabled( const bool value );

                void set_default_workarounds_enabled( const bool value );

                void set_single_diffie_hellman_use_enabled( const bool value );

                void set_certificate( const framework::Uri& value );

                void set_certificate_chain( const framework::Uri& value );
                
                void set_certificate_authority_pool( const framework::Uri& value );

                void set_private_key( const framework::Uri& value );

                void set_private_rsa_key( const framework::Uri& value );

                void set_temporary_diffie_hellman( const framework::Uri& value );

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
                bool m_sslv2_enabled;

                bool m_sslv3_enabled;

                bool m_tlsv1_enabled;

                bool m_tlsv11_enabled;

                bool m_tlsv12_enabled;

                bool m_compression_enabled;

                bool m_default_workarounds_enabled;

                bool m_single_diffie_hellman_use_enabled;

                std::string m_private_key;

                std::string m_private_rsa_key;

                std::string m_certificate;

                std::string m_certificate_chain;

                std::string m_certificate_authority_pool;

                std::string m_temporary_diffie_hellman;
        };
    }
}

#endif  /* _RESTBED_DETAIL_SSL_SETTINGS_IMPL_H */
