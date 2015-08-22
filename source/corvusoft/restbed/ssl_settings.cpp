/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
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
        delete m_pimpl;
    }
    
    bool SSLSettings::has_disabled_http( void ) const
    {
        return m_pimpl->http_disabled;
    }
    
    bool SSLSettings::has_enabled_sslv2( void ) const
    {
        return m_pimpl->sslv2_enabled;
    }
    
    bool SSLSettings::has_enabled_sslv3( void ) const
    {
        return m_pimpl->sslv3_enabled;
    }
    
    bool SSLSettings::has_enabled_tlsv1( void ) const
    {
        return m_pimpl->tlsv1_enabled;
    }
    
    bool SSLSettings::has_enabled_tlsv11( void ) const
    {
        return m_pimpl->tlsv11_enabled;
    }
    
    bool SSLSettings::has_enabled_tlsv12( void ) const
    {
        return m_pimpl->tlsv12_enabled;
    }
    
    bool SSLSettings::has_enabled_compression( void ) const
    {
        return m_pimpl->compression_enabled;
    }
    
    bool SSLSettings::has_enabled_default_workarounds( void ) const
    {
        return m_pimpl->default_workarounds_enabled;
    }
    
    bool SSLSettings::has_enabled_single_diffie_hellman_use( void ) const
    {
        return m_pimpl->single_diffie_hellman_use_enabled;
    }
    
    uint16_t SSLSettings::get_port( void ) const
    {
        return m_pimpl->port;
    }
    
    string SSLSettings::get_bind_address( void ) const
    {
        return m_pimpl->bind_address;
    }
    
    string SSLSettings::get_certificate( void ) const
    {
        return m_pimpl->certificate;
    }
    
    string SSLSettings::get_passphrase( void ) const
    {
        return m_pimpl->passphrase;
    }
    
    string SSLSettings::get_private_key( void ) const
    {
        return m_pimpl->private_key;
    }
    
    string SSLSettings::get_private_rsa_key( void ) const
    {
        return m_pimpl->private_rsa_key;
    }
    
    string SSLSettings::get_certificate_chain( void ) const
    {
        return m_pimpl->certificate_chain;
    }
    
    string SSLSettings::get_temporary_diffie_hellman( void ) const
    {
        return m_pimpl->temporary_diffie_hellman;
    }
    
    string SSLSettings::get_certificate_authority_pool( void ) const
    {
        return m_pimpl->certificate_authority_pool;
    }
    
    void SSLSettings::set_port( const uint16_t value )
    {
        m_pimpl->port = value;
    }
    
    void SSLSettings::set_bind_address( const string& value )
    {
        m_pimpl->bind_address = value;
    }
    
    void SSLSettings::set_http_disabled( const bool value )
    {
        m_pimpl->http_disabled = value;
    }
    
    void SSLSettings::set_sslv2_enabled( const bool value )
    {
        m_pimpl->sslv2_enabled = value;
    }
    
    void SSLSettings::set_sslv3_enabled( const bool value )
    {
        m_pimpl->sslv3_enabled = value;
    }
    
    void SSLSettings::set_tlsv1_enabled( const bool value )
    {
        m_pimpl->tlsv1_enabled = value;
    }
    
    void SSLSettings::set_tlsv11_enabled( const bool value )
    {
        m_pimpl->tlsv11_enabled = value;
    }
    
    void SSLSettings::set_tlsv12_enabled( const bool value )
    {
        m_pimpl->tlsv12_enabled = value;
    }
    
    void SSLSettings::set_compression_enabled( const bool value )
    {
        m_pimpl->compression_enabled = value;
    }
    
    void SSLSettings::set_default_workarounds_enabled( const bool value )
    {
        m_pimpl->default_workarounds_enabled = value;
    }
    
    void SSLSettings::set_single_diffie_hellman_use_enabled( const bool value )
    {
        m_pimpl->single_diffie_hellman_use_enabled = value;
    }
    
    void SSLSettings::set_certificate( const Uri& value )
    {
        m_pimpl->certificate = String::remove( "file://", value.to_string( ), String::CASE_INSENSITIVE );
    }
    
    void SSLSettings::set_certificate_chain( const Uri& value )
    {
        m_pimpl->certificate_chain = String::remove( "file://", value.to_string( ), String::CASE_INSENSITIVE );
    }
    
    void SSLSettings::set_certificate_authority_pool( const Uri& value )
    {
        m_pimpl->certificate_authority_pool = String::remove( "file://", value.to_string( ), String::CASE_INSENSITIVE );
    }
    
    void SSLSettings::set_passphrase( const string& value )
    {
        m_pimpl->passphrase = value;
    }
    
    void SSLSettings::set_private_key( const Uri& value )
    {
        m_pimpl->private_key = String::remove( "file://", value.to_string( ), String::CASE_INSENSITIVE );
    }
    
    void SSLSettings::set_private_rsa_key( const Uri& value )
    {
        m_pimpl->private_rsa_key = String::remove( "file://", value.to_string( ), String::CASE_INSENSITIVE );
    }
    
    void SSLSettings::set_temporary_diffie_hellman( const Uri& value )
    {
        m_pimpl->temporary_diffie_hellman = String::remove( "file://", value.to_string( ), String::CASE_INSENSITIVE );
    }
}
