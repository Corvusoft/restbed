/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/detail/ssl_settings_impl.hpp"

//External Includes
#include <corvusoft/framework/uri>
#include <corvusoft/framework/string>

//System Namespaces
using std::string;
using std::function;

//Project Namespaces

//External Namespaces
using framework::Uri;
using framework::String;

namespace restbed
{
    namespace detail
    {
        SSLSettingsImpl::SSLSettingsImpl( void ) : m_sslv2_enabled( true ),
            m_sslv3_enabled( true ),
            m_tlsv1_enabled( true ),
            m_tlsv11_enabled( true ),
            m_tlsv12_enabled( true ),
            m_compression_enabled( true ),
            m_default_workarounds_enabled( true ),
            m_single_diffie_hellman_use_enabled( true ),
            m_private_key( String::empty ),
            m_private_rsa_key( String::empty ),
            m_certificate( String::empty ),
            m_certificate_chain( String::empty ),
            m_certificate_authority_pool( String::empty ),
            m_temporary_diffie_hellman( String::empty )
        {
            return;
        }
        
        SSLSettingsImpl::~SSLSettingsImpl( void )
        {
            return;
        }

        bool SSLSettingsImpl::has_enabled_sslv2( void ) const
        {
            return m_sslv2_enabled;
        }

        bool SSLSettingsImpl::has_enabled_sslv3( void ) const
        {
            return m_sslv3_enabled;
        }

        bool SSLSettingsImpl::has_enabled_tlsv1( void ) const
        {
            return m_tlsv1_enabled;
        }

        bool SSLSettingsImpl::has_enabled_tlsv11( void ) const
        {
            return m_tlsv11_enabled;
        }

        bool SSLSettingsImpl::has_enabled_tlsv12( void ) const
        {
            return m_tlsv12_enabled;
        }

        bool SSLSettingsImpl::has_enabled_compression( void ) const
        {
            return m_compression_enabled;
        }

        bool SSLSettingsImpl::has_enabled_default_workarounds( void ) const
        {
            return m_default_workarounds_enabled;
        }

        bool SSLSettingsImpl::has_enabled_single_diffie_hellman_use( void ) const
        {
            return m_single_diffie_hellman_use_enabled;
        }

        string SSLSettingsImpl::get_certificate( void ) const
        {
            return m_certificate;
        }

        string SSLSettingsImpl::get_private_key( void ) const
        {
            return m_private_key;
        }

        string SSLSettingsImpl::get_private_rsa_key( void ) const
        {
            return m_private_rsa_key;
        }

        string SSLSettingsImpl::get_certificate_chain( void ) const
        {
            return m_certificate_chain;
        }
                
        string SSLSettingsImpl::get_temporary_diffie_hellman( void ) const
        {
            return m_temporary_diffie_hellman;
        }

        string SSLSettingsImpl::get_certificate_authority_pool( void ) const
        {
            return m_certificate_authority_pool;
        }

        void SSLSettingsImpl::set_sslv2_enabled( const bool value )
        {
            m_sslv2_enabled = value;
        }

        void SSLSettingsImpl::set_sslv3_enabled( const bool value )
        {
            m_sslv3_enabled = value;
        }

        void SSLSettingsImpl::set_tlsv1_enabled( const bool value )
        {
            m_tlsv1_enabled = value;
        }

        void SSLSettingsImpl::set_tlsv11_enabled( const bool value )
        {
            m_tlsv11_enabled = value ;
        }

        void SSLSettingsImpl::set_tlsv12_enabled( const bool value )
        {
            m_tlsv12_enabled = value;
        }

        void SSLSettingsImpl::set_compression_enabled( const bool value )
        {
            m_compression_enabled = value;
        }

        void SSLSettingsImpl::set_default_workarounds_enabled( const bool value )
        {
            m_default_workarounds_enabled = value;
        }

        void SSLSettingsImpl::set_single_diffie_hellman_use_enabled( const bool value )
        {
            m_single_diffie_hellman_use_enabled = value;
        }

        void SSLSettingsImpl::set_certificate( const Uri& value )
        {
            m_certificate = String::remove( "file://", value.to_string( ) );
        }

        void SSLSettingsImpl::set_certificate_chain( const Uri& value )
        {
            m_certificate_chain = String::remove( "file://", value.to_string( ) );
        }
        
        void SSLSettingsImpl::set_certificate_authority_pool( const Uri& value )
        {
            m_certificate_authority_pool = String::remove( "file://", value.to_string( ) );
        }

        void SSLSettingsImpl::set_private_key( const Uri& value )
        {
            m_private_key = String::remove( "file://", value.to_string( ) );
        }

        void SSLSettingsImpl::set_private_rsa_key( const Uri& value )
        {
            m_private_rsa_key = String::remove( "file://", value.to_string( ) );
        }

        void SSLSettingsImpl::set_temporary_diffie_hellman( const Uri& value )
        {
            m_temporary_diffie_hellman = String::remove( "file://", value.to_string( ) );
        }
    }
}
