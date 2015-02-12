/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <cstdarg>

//Project Includes
#include "corvusoft/restbed/logger.h"
#include "corvusoft/restbed/detail/logger_impl.h"

//External Includes

//System Namespaces
using std::string;

//Project Namespaces
using restbed::detail::LoggerImpl;

//External Namespaces

namespace restbed
{
    Logger::Logger( void ) : m_pimpl( new LoggerImpl )
    {
        return;
    }
    
    Logger::Logger( const Logger& original ) : m_pimpl( new LoggerImpl( *original.m_pimpl ) )
    {
        return;
    }
    
    Logger::Logger( const LoggerImpl& implementation ) : m_pimpl( new LoggerImpl( implementation ) )
    {
        return;
    }
    
    Logger::~Logger( void )
    {
        return;
    }
    
    void Logger::log( const LogLevel level, const string format, ... ) noexcept
    {
        va_list arguments;
        
        va_start( arguments, format );
        
        m_pimpl->log( level, format, arguments );
        
        va_end( arguments );
    }
    
    void Logger::log_if( bool expression, const LogLevel level, const string format, ... ) noexcept
    {
        va_list arguments;
        
        va_start( arguments, format );
        
        m_pimpl->log_if( expression, level, format, arguments );
        
        va_end( arguments );
    }
    
    Logger& Logger::operator =( const Logger& value )
    {
        *m_pimpl = *value.m_pimpl;
        
        return *this;
    }
}
