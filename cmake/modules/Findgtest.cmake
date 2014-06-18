# Copyright (c) 2013, 2014 Corvusoft

find_path( gtest_INCLUDE gtest/gtest.h HINTS "/usr/include" "/usr/local/include" "/opt/local/include" "${CMAKE_SOURCE_DIR}/dependency/gtest/include" )
find_library( gtest_LIBRARY NAMES gtest HINTS "/usr/lib" "/usr/local/lib" "/opt/local/lib" "${CMAKE_SOURCE_DIR}/dependency/gtest" )
find_library( gtest_MAIN_LIBRARY NAMES gtest_main HINTS "/usr/lib" "/usr/local/lib" "/opt/local/lib" "${CMAKE_SOURCE_DIR}/dependency/gtest" ) 

if ( gtest_INCLUDE AND gtest_LIBRARY AND gtest_MAIN_LIBRARY )
    set( GTEST_FOUND TRUE )

    if ( NOT GTEST_FIND_QUIETLY )
        message( STATUS "Found gtest header: ${gtest_INCLUDE}" )
        message( STATUS "Found gtest library: ${gtest_LIBRARY}" )
        message( STATUS "Found gtest main library: ${gtest_MAIN_LIBRARY}" )
    endif ( )
else ( )
    if ( GTEST_FIND_REQUIRED )
        message( FATAL_ERROR "Failed to locate gtest!" )
    endif ( )
endif ( )
