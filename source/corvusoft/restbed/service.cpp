/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <cstdarg>

//Project Includes
#include "corvusoft/restbed/service.h"
#include "corvusoft/restbed/response.h"
#include "corvusoft/restbed/settings.h"
#include "corvusoft/restbed/log_level.h"
#include "corvusoft/restbed/detail/service_impl.h"

//External Includes

//System Namespaces
using std::string;

//Project Namespaces
using restbed::detail::ServiceImpl;

//External Namespaces

namespace restbed
{
    Service::Service( const Settings& settings ) : m_pimpl( new ServiceImpl( settings ) )
    {
        //n/a
    }
    
    Service::Service( const Service& original ) : m_pimpl( new ServiceImpl( *original.m_pimpl ) )
    {
        //n/a
    }
    
    Service::~Service( void )
    {
        //n/a
    }

    void Service::start( void )
    {
        m_pimpl->start( );
    }

    void Service::stop( void )
    {
        m_pimpl->stop( );
    }

    void Service::publish( const Resource& value )
    {
        m_pimpl->publish( value );
    }

    void Service::suppress( const Resource& value )
    {
        m_pimpl->suppress( value );
    }

    Service& Service::operator =( const Service& rhs )
    {
        *m_pimpl = *rhs.m_pimpl;

        return *this;
    }

    bool Service::operator <( const Service& rhs ) const
    {
        return *m_pimpl < *rhs.m_pimpl;
    }
    
    bool Service::operator >( const Service& rhs ) const
    {
        return *m_pimpl > *rhs.m_pimpl;
    }
    
    bool Service::operator ==( const Service& rhs ) const
    {
        return *m_pimpl == *rhs.m_pimpl;
    }
    
    bool Service::operator !=( const Service& rhs ) const
    {
        return *m_pimpl != *rhs.m_pimpl;
    }

    void Service::error_handler( const Request& request, Response& response )
    {
        m_pimpl->error_handler( request, response );
    }
    
    void Service::authentication_handler( const Request& request, Response& response )
    {
        m_pimpl->authentication_handler( request, response );
    }

    void Service::log_handler( const LogLevel level, const string& format, ... )
    {
        va_list arguments;
            
        va_start( arguments, format );
            
        m_pimpl->log_handler( level, format, arguments );
            
        va_end( arguments );
    }
}
