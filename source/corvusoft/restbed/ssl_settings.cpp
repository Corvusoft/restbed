/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/uri.hpp"
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/ssl_settings.hpp"
#include "corvusoft/restbed/detail/ssl_settings_impl.hpp"

//External Includes

//System Namespaces
using std::string;
using std::unique_ptr;

//Project Namespaces
using restbed::detail::SSLSettingsImpl;

//External Namespaces

namespace restbed
{
    SSLSettings::SSLSettings( void ) : m_pimpl( new SSLSettingsImpl )
    {
        return;
    }
    
    SSLSettings::~SSLSettings( void )
    {
        return;
    }
    
    bool SSLSettings::has_disabled_http( void ) const
    {
        return m_pimpl->m_http_disabled;
    }
    
    bool SSLSettings::has_enabled_sslv2( void ) const
    {
        return m_pimpl->m_sslv2_enabled;
    }
    
    bool SSLSettings::has_enabled_sslv3( void ) const
    {
        return m_pimpl->m_sslv3_enabled;
    }
    
    bool SSLSettings::has_enabled_tlsv1( void ) const
    {
        return m_pimpl->m_tlsv1_enabled;
    }
    
    bool SSLSettings::has_enabled_tlsv11( void ) const
    {
        return m_pimpl->m_tlsv11_enabled;
    }
    
    bool SSLSettings::has_enabled_tlsv12( void ) const
    {
        return m_pimpl->m_tlsv12_enabled;
    }
    
    bool SSLSettings::has_enabled_compression( void ) const
    {
        return m_pimpl->m_compression_enabled;
    }
    
    bool SSLSettings::has_enabled_default_workarounds( void ) const
    {
        return m_pimpl->m_default_workarounds_enabled;
    }
    
    bool SSLSettings::has_enabled_single_diffie_hellman_use( void ) const
    {
        return m_pimpl->m_single_diffie_hellman_use_enabled;
    }
    
    uint16_t SSLSettings::get_port( void ) const
    {
        return m_pimpl->m_port;
    }
    
    string SSLSettings::get_bind_address( void ) const
    {
        return m_pimpl->m_bind_address;
    }
    
    string SSLSettings::get_certificate( void ) const
    {
        return m_pimpl->m_certificate;
    }
    
    string SSLSettings::get_passphrase( void ) const
    {
        return m_pimpl->m_passphrase;
    }
    
    string SSLSettings::get_private_key( void ) const
    {
        return m_pimpl->m_private_key;
    }
    
    string SSLSettings::get_private_rsa_key( void ) const
    {
        return m_pimpl->m_private_rsa_key;
    }
    
    string SSLSettings::get_certificate_chain( void ) const
    {
        return m_pimpl->m_certificate_chain;
    }
    
    string SSLSettings::get_temporary_diffie_hellman( void ) const
    {
        return m_pimpl->m_temporary_diffie_hellman;
    }
    
    string SSLSettings::get_certificate_authority_pool( void ) const
    {
        return m_pimpl->m_certificate_authority_pool;
    }
    
    void SSLSettings::set_port( const uint16_t value )
    {
        m_pimpl->m_port = value;
    }
    
    void SSLSettings::set_bind_address( const string& value )
    {
        m_pimpl->m_bind_address = value;
    }
    
    void SSLSettings::set_http_disabled( const bool value )
    {
        m_pimpl->m_http_disabled = value;
    }
    
    void SSLSettings::set_sslv2_enabled( const bool value )
    {
        m_pimpl->m_sslv2_enabled = value;
    }
    
    void SSLSettings::set_sslv3_enabled( const bool value )
    {
        m_pimpl->m_sslv3_enabled = value;
    }
    
    void SSLSettings::set_tlsv1_enabled( const bool value )
    {
        m_pimpl->m_tlsv1_enabled = value;
    }
    
    void SSLSettings::set_tlsv11_enabled( const bool value )
    {
        m_pimpl->m_tlsv11_enabled = value;
    }
    
    void SSLSettings::set_tlsv12_enabled( const bool value )
    {
        m_pimpl->m_tlsv12_enabled = value;
    }
    
    void SSLSettings::set_compression_enabled( const bool value )
    {
        m_pimpl->m_compression_enabled = value;
    }
    
    void SSLSettings::set_default_workarounds_enabled( const bool value )
    {
        m_pimpl->m_default_workarounds_enabled = value;
    }
    
    void SSLSettings::set_single_diffie_hellman_use_enabled( const bool value )
    {
        m_pimpl->m_single_diffie_hellman_use_enabled = value;
    }
    
    void SSLSettings::set_certificate( const Uri& value )
    {
        m_pimpl->m_certificate = String::remove( "file://", value.to_string( ), String::CASE_INSENSITIVE );
    }
    
    void SSLSettings::set_certificate_chain( const Uri& value )
    {
        m_pimpl->m_certificate_chain = String::remove( "file://", value.to_string( ), String::CASE_INSENSITIVE );
    }
    
    void SSLSettings::set_certificate_authority_pool( const Uri& value )
    {
        m_pimpl->m_certificate_authority_pool = String::remove( "file://", value.to_string( ), String::CASE_INSENSITIVE );
    }
    
    void SSLSettings::set_passphrase( const string& value )
    {
        m_pimpl->m_passphrase = value;
    }
    
    void SSLSettings::set_private_key( const Uri& value )
    {
        m_pimpl->m_private_key = String::remove( "file://", value.to_string( ), String::CASE_INSENSITIVE );
    }
    
    void SSLSettings::set_private_rsa_key( const Uri& value )
    {
        m_pimpl->m_private_rsa_key = String::remove( "file://", value.to_string( ), String::CASE_INSENSITIVE );
    }
    
    void SSLSettings::set_temporary_diffie_hellman( const Uri& value )
    {
        m_pimpl->m_temporary_diffie_hellman = String::remove( "file://", value.to_string( ), String::CASE_INSENSITIVE );
    }
}
