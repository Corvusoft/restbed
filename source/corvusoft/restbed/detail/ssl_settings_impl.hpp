/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
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
            uint16_t port = 443;
            
            bool http_disabled = false;
            
            bool sslv2_enabled = true;
            
            bool sslv3_enabled = true;
            
            bool tlsv1_enabled = true;
            
            bool tlsv11_enabled = true;
            
            bool tlsv12_enabled = true;
            
            bool compression_enabled = true;
            
            bool default_workarounds_enabled = true;
            
            bool single_diffie_hellman_use_enabled = true;
            
            std::string bind_address = "";
            
            std::string passphrase = "";
            
            std::string private_key = "";
            
            std::string private_rsa_key = "";
            
            std::string certificate = "";
            
            std::string certificate_chain = "";
            
            std::string certificate_authority_pool = "";
            
            std::string temporary_diffie_hellman = "";
        };
    }
}

#endif  /* _RESTBED_DETAIL_SSL_SETTINGS_IMPL_H */
