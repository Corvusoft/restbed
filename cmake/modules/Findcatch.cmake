find_path( catch_INCLUDE catch.hpp HINTS "${PROJECT_SOURCE_DIR}/dependency/catch/include" "/usr/include" "/usr/include/catch" "/usr/include/catch2" "/usr/local/include" "/usr/local/include/catch" "/usr/local/include/catch2" "/opt/local/include" "/opt/local/include/catch" "/opt/local/include/catch2" )

if ( catch_INCLUDE )
    set( CATCH_FOUND TRUE )

    message( STATUS "${Green}Found Catch include at: ${catch_INCLUDE}${Reset}" )
else ( )
    message( FATAL_ERROR "${Red}Failed to locate Catch dependency.${Reset}" )
endif ( )
