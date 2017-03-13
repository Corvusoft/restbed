# Copyright 2014-2016, Corvusoft Ltd, All Rights Reserved.

find_path( kashmir_INCLUDE kashmir HINTS "${PROJECT_SOURCE_DIR}/dependency/kashmir" "/usr/include" "/usr/local/include" "/opt/local/include" )

if ( kashmir_INCLUDE )
    set( KASHMIR_FOUND TRUE )

    message( STATUS "${Green}Found Kashmir include at: ${kashmir_INCLUDE}${Reset}" )
else ( )
    message( FATAL_ERROR "${Red}Failed to locate Kashmir dependency.${Reset}" )
endif ( )
