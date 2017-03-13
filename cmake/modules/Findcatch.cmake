# Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.

find_path( catch_INCLUDE catch.hpp HINTS "${PROJECT_SOURCE_DIR}/dependency/catch/include" "/usr/include" "/usr/local/include" "/opt/local/include" )

if ( catch_INCLUDE )
    set( CATCH_FOUND TRUE )

    message( STATUS "${Green}Found Catch include at: ${catch_INCLUDE}${Reset}" )
else ( )
    message( FATAL_ERROR "${Red}Failed to locate Catch dependency.${Reset}" )
endif ( )
