/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <mutex>
#include <ctime>
#include <cstdio>
#include <chrono>

//Project Includes
#include "corvusoft/restbed/log_level.h"
#include "corvusoft/restbed/detail/logger_impl.h"

//External Includes
#include <corvusoft/framework/date>
#include <corvusoft/framework/string>

//System Namespaces
using std::mutex;
using std::string;
using std::chrono::system_clock;

//Project Namespaces

//External Namespaces
using framework::Date;
using framework::String;

namespace restbed
{
    namespace detail
    {
        LoggerImpl::LoggerImpl( void )
        {
            //n/a
        }
        
        LoggerImpl::LoggerImpl( const LoggerImpl& )
        {
            //n/a
        }
        
        LoggerImpl::~LoggerImpl( void )
        {
            //n/a
        }
        
        void LoggerImpl::log( const LogLevel level, const string format, va_list arguments ) const
        {
            string label = build_log_label( level );
            
            FILE* descriptor = nullptr;
            
            switch ( level )
            {
                case INFO:
                case DEBUG:
                    descriptor = stdout;
                    break;
                    
                case FATAL:
                case ERROR:
                case WARNING:
                case SECURITY:
                default:
                    descriptor = stderr;
            }
            
            static mutex mtx;
            
            mtx.lock( );
            
            fprintf( descriptor, "%s", label.data( ) );
            
            vfprintf( descriptor, format.data( ), arguments );
            
            if ( level == INFO or level == DEBUG )
            {
                fprintf( descriptor, "\n" );
                
                fflush( descriptor );
            }
            
            mtx.unlock( );
        }
        
        void LoggerImpl::log_if( bool expression, const LogLevel level, const string format, va_list arguments ) const
        {
            if ( expression == true )
            {
                log( level, format, arguments );
            }
        }
        
        LoggerImpl& LoggerImpl::operator =( const LoggerImpl& )
        {
            return *this;
        }
        
        string LoggerImpl::build_log_label( const LogLevel level ) const
        {
            string tag = String::empty;
            
            switch ( level )
            {
                case INFO:
                    tag = "INFO    ";
                    break;
                    
                case DEBUG:
                    tag = "DEBUG   ";
                    break;
                    
                case FATAL:
                    tag = "FATAL   ";
                    break;
                    
                case ERROR:
                    tag = "ERROR   ";
                    break;
                    
                case WARNING:
                    tag = "WARNING ";
                    break;
                    
                case SECURITY:
                    tag = "SECURITY";
                    break;
                    
                default:
                    tag = String::format( "LOG LEVEL (%i)", level );
            }
            
            string timestamp = Date::format( system_clock::now( ) );
            
            string label = String::format( "[%s %s] ", tag.data( ), timestamp.data( ) );
            
            return label;
        }
    }
}
