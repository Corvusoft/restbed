find_path( syslog_INCLUDE syslog.h HINTS "/usr/include" "/usr/local/include" "/opt/local/include" )

if ( syslog_INCLUDE )
    set( SYSLOG_FOUND TRUE )

    message( STATUS "Found Syslog include at: ${syslog_INCLUDE}" )
else ( )
    message( STATUS "Failed to locate Syslog, skipping example." )
endif ( )
