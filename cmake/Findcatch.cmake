find_path( catch_INCLUDE catch.hpp HINTS "${PROJECT_SOURCE_DIR}/dependency/catch/single_include/catch2" "/usr/include/catch2/single_include" "/usr/include/catch2" "/usr/local/include/catch2/single_include" "/usr/local/include/catch2" "/opt/local/include/catch2/single_include" "/opt/local/include/catch2" )

if ( catch_INCLUDE )
    set( CATCH_FOUND TRUE )

    message( STATUS "Found Catch include at: ${catch_INCLUDE}" )
else ( )
    message( FATAL_ERROR "Failed to locate Catch dependency." )
endif ( )
