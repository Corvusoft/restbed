/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_DETAIL_SSL_SETTINGS_IMPL_H
#define _RESTBED_DETAIL_SSL_SETTINGS_IMPL_H 1

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
    
    namespace detail
    {
        //Forward Declarations
        
        struct SSLSettingsImpl
        {
            uint16_t m_port = 443;
            
            bool m_http_disabled = false;
            
            bool m_sslv2_enabled = true;
            
            bool m_sslv3_enabled = true;
            
            bool m_tlsv1_enabled = true;
            
            bool m_tlsv11_enabled = true;
            
            bool m_tlsv12_enabled = true;
            
            bool m_compression_enabled = true;
            
            bool m_default_workarounds_enabled = true;
            
            bool m_single_diffie_hellman_use_enabled = true;
            
            std::string m_bind_address = "";
            
            std::string m_passphrase = "";
            
            std::string m_private_key = "";
            
            std::string m_private_rsa_key = "";
            
            std::string m_certificate = "";
            
            std::string m_certificate_chain = "";
            
            std::string m_certificate_authority_pool = "";
            
            std::string m_temporary_diffie_hellman = "";
        };
    }
}

#endif  /* _RESTBED_DETAIL_SSL_SETTINGS_IMPL_H */
