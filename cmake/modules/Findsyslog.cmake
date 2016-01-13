# Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.

find_path( syslog_INCLUDE syslog.h HINTS "/usr/include" "/usr/local/include" "/opt/local/include" )

if ( syslog_INCLUDE )
    set( SYSLOG_FOUND TRUE )

    message( STATUS "${Green}Found Syslog include at: ${syslog_INCLUDE}${Reset}" )
else ( )
    message( STATUS "${Yellow}Failed to locate Syslog, skipping example.${Reset}" )
endif ( )
