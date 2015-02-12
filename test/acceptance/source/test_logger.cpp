/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <cstdlib>

//Project Includes
#include "test_logger.h"

//External Includes

//System Namespaces
using std::string;
using std::vector;

//Project Namespaces
using restbed::Logger;
using restbed::LogLevel;

//External Namespaces

TestLogger::TestLogger( void ) : Logger( ),
    m_log_entries( )
{
    return;
}

TestLogger::~TestLogger( void )
{
    return;
}

void TestLogger::log( const LogLevel, const string format, ... ) noexcept
{
    va_list arguments;
    
    va_start( arguments, format );
    
    char* entry = nullptr;
    
    int status = vasprintf( &entry, format.data( ), arguments );
    
    if ( status == -1 )
    {
        throw "Failed to copy log entry!";
    }
    
    m_log_entries.push_back( entry );
    
    free( entry );
    
    va_end( arguments );
}

const char* TestLogger::get_log_entry( void ) const
{
    string entry = "";
    
    auto size = m_log_entries.size( );
    
    if ( size not_eq 0 )
    {
        entry = m_log_entries.at( size - 1 );
    }
    
    return entry.data( );
}
