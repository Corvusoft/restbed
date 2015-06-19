# Copyright (c) 2013, 2014, 2015 Corvusoft

find_path( catch_INCLUDE catch.hpp HINTS "${CMAKE_SOURCE_DIR}/dependency/catch/include" "/usr/include" "/usr/local/include" "/opt/local/include" )

if ( catch_INCLUDE )
    set( CATCH_FOUND TRUE )

    if ( NOT catch_FIND_QUIETLY )
        message( STATUS "Found catch source: ${catch_INCLUDE}" )
    endif ( )
else ( )
    if ( catch_FIND_REQUIRED )
        message( FATAL_ERROR "Failed to locate catch!" )
    endif ( )
endif ( )
