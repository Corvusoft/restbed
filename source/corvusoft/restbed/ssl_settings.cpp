/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/uri.hpp"
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
        return;
    }

    bool SSLSettings::has_disabled_http( void ) const
    {
        return m_pimpl->has_disabled_http( );
    }

    bool SSLSettings::has_enabled_sslv2( void ) const
    {
        return m_pimpl->has_enabled_sslv2( );
    }

    bool SSLSettings::has_enabled_sslv3( void ) const
    {
        return m_pimpl->has_enabled_sslv3( );
    }

    bool SSLSettings::has_enabled_tlsv1( void ) const
    {
        return m_pimpl->has_enabled_tlsv1( );
    }

    bool SSLSettings::has_enabled_tlsv11( void ) const
    {
        return m_pimpl->has_enabled_tlsv11( );
    }

    bool SSLSettings::has_enabled_tlsv12( void ) const
    {
        return m_pimpl->has_enabled_tlsv12( );
    }

    bool SSLSettings::has_enabled_compression( void ) const
    {
        return m_pimpl->has_enabled_compression( );
    }

    bool SSLSettings::has_enabled_default_workarounds( void ) const
    {
        return m_pimpl->has_enabled_default_workarounds( );
    }

    bool SSLSettings::has_enabled_single_diffie_hellman_use( void ) const
    {
        return m_pimpl->has_enabled_single_diffie_hellman_use( );
    }

    uint16_t SSLSettings::get_port( void ) const
    {
        return m_pimpl->get_port( );
    }

    string SSLSettings::get_certificate( void ) const
    {
        return m_pimpl->get_certificate( );
    }

    string SSLSettings::get_passphrase( void ) const
    {
        return m_pimpl->get_passphrase( );
    }

    string SSLSettings::get_private_key( void ) const
    {
        return m_pimpl->get_private_key( );
    }

    string SSLSettings::get_private_rsa_key( void ) const
    {
        return m_pimpl->get_private_rsa_key( );
    }

    string SSLSettings::get_certificate_chain( void ) const
    {
        return m_pimpl->get_certificate_chain( );
    }
            
    string SSLSettings::get_temporary_diffie_hellman( void ) const
    {
        return m_pimpl->get_temporary_diffie_hellman( );
    }

    string SSLSettings::get_certificate_authority_pool( void ) const
    {
        return m_pimpl->get_certificate_authority_pool( );
    }

    void SSLSettings::set_port( const uint16_t value )
    {
        m_pimpl->set_port( value );
    }

    void SSLSettings::set_http_disabled( const bool value )
    {
        m_pimpl->set_http_disabled( value );
    }

    void SSLSettings::set_sslv2_enabled( const bool value )
    {
        m_pimpl->set_sslv2_enabled( value );
    }

    void SSLSettings::set_sslv3_enabled( const bool value )
    {
        m_pimpl->set_sslv3_enabled( value );
    }

    void SSLSettings::set_tlsv1_enabled( const bool value )
    {
        m_pimpl->set_tlsv1_enabled( value );
    }

    void SSLSettings::set_tlsv11_enabled( const bool value )
    {
        m_pimpl->set_tlsv11_enabled( value );
    }

    void SSLSettings::set_tlsv12_enabled( const bool value )
    {
        m_pimpl->set_tlsv12_enabled( value );
    }

    void SSLSettings::set_compression_enabled( const bool value )
    {
        m_pimpl->set_compression_enabled( value );
    }

    void SSLSettings::set_default_workarounds_enabled( const bool value )
    {
        m_pimpl->set_default_workarounds_enabled( value );
    }

    void SSLSettings::set_single_diffie_hellman_use_enabled( const bool value )
    {
        m_pimpl->set_single_diffie_hellman_use_enabled( value );
    }

    void SSLSettings::set_certificate( const Uri& value )
    {
        m_pimpl->set_certificate( value );
    }

    void SSLSettings::set_certificate_chain( const Uri& value )
    {
        m_pimpl->set_certificate_chain( value );
    }
    
    void SSLSettings::set_certificate_authority_pool( const Uri& value )
    {
        m_pimpl->set_certificate_authority_pool( value );
    }

    void SSLSettings::set_passphrase( const string& value )
    {
        m_pimpl->set_passphrase( value );
    }

    void SSLSettings::set_private_key( const Uri& value )
    {
        m_pimpl->set_private_key( value );
    }

    void SSLSettings::set_private_rsa_key( const Uri& value )
    {
        m_pimpl->set_private_rsa_key( value );
    }

    void SSLSettings::set_temporary_diffie_hellman( const Uri& value )
    {
        m_pimpl->set_temporary_diffie_hellman( value );
    }
}
