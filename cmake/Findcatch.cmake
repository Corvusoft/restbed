find_path( catch_INCLUDE catch2 HINTS "/usr/include/" "/usr/local/include/" "/opt/local/include/" )

if ( catch_INCLUDE )
    set( CATCH_FOUND TRUE )

    message( STATUS "Found Catch2 include at: ${catch_INCLUDE}" )

    find_library( catch_LIBRARY_STATIC      libCatch2.a     HINTS "/usr/lib" "/usr/local/lib" "/opt/local/lib" )
    find_library( catch_main_LIBRARY_STATIC libCatch2Main.a HINTS "/usr/lib" "/usr/local/lib" "/opt/local/lib" )
    
    if ( catch_LIBRARY_STATIC AND catch_main_LIBRARY_STATIC )
        message( STATUS "Found Catch2 libraries at: ${catch_LIBRARY_STATIC}" )
        message( STATUS "Found Catch2 libraries at: ${catch_main_LIBRARY_STATIC}" )
    else ( )
        message( FATAL_ERROR "Failed to locate Catch2 dependency." )
    endif ( )
else ( )
    message( FATAL_ERROR "Failed to locate Catch2 dependency." )
endif ( )