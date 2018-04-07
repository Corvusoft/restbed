find_path( kashmir_INCLUDE kashmir HINTS "${PROJECT_SOURCE_DIR}/dependency/kashmir" "/usr/include" "/usr/local/include" "/opt/local/include" )

if ( kashmir_INCLUDE )
    set( KASHMIR_FOUND TRUE )

    message( STATUS "Found Kashmir include at: ${kashmir_INCLUDE}" )
else ( )
    message( FATAL_ERROR "Failed to locate Kashmir dependency." )
endif ( )
