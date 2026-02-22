find_path( catch_INCLUDE catch2 HINTS "/usr/include/" "/usr/local/include/" "/opt/local/include/" "${PROJECT_SOURCE_DIR}/vcpkg_installed/x64-windows/include" )

if ( catch_INCLUDE )
    set( CATCH_FOUND TRUE )

    message( STATUS "Found Catch2 include at: ${catch_INCLUDE}" )

    find_library( catch_LIBRARY_STATIC libCatch2.a Catch2.lib HINTS "/usr/lib" "/usr/local/lib" "/opt/local/lib" "${PROJECT_SOURCE_DIR}/vcpkg_installed/x64-windows/lib" )

    if ( catch_LIBRARY_STATIC )
        message( STATUS "Found Catch2 libraries at: ${catch_LIBRARY_STATIC}" )
    else ( )
        message( FATAL_ERROR "Failed to locate Catch2 dependency." )
    endif ( )
else ( )
    message( FATAL_ERROR "Failed to locate Catch2 dependency." )
endif ( )