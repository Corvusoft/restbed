/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
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
    SSLSettings::SSLSettings( void ) : Settings( ),
        m_pimpl( new SSLSettingsImpl )
    {
        set_port( 443 );
    }
    
    SSLSettings::~SSLSettings( void )
    {
        return;
    }
}
