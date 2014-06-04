# Copyright (c) 2013, 2014 Corvusoft

set( GTest_SOURCE_DIR "${CMAKE_SOURCE_DIR}/dependency/gtest" )

find_path( GTest_INCLUDE_DIR "gtest.h" "${GTest_SOURCE_DIR}/include/gtest" )
find_path( GTest_LIBRARY "libgtest.a" "${GTest_SOURCE_DIR}" )
find_path( GTest_MAIN_LIBRARY "libgtest_main.a" "${GTest_SOURCE_DIR}" )

if ( NOT GTest_INCLUDE_DIR OR NOT GTest_LIBRARY OR NOT GTest_MAIN_LIBRARY )
    if ( GTest_FIND_REQUIRED )
        message( FATAL_ERROR "Could not find gtest source directory or the directory has missing files." )
    endif ( GTest_FIND_REQUIRED )

else ( )
    if ( NOT GTest_FIND_QUIETLY )
        message( STATUS "Found gtest: ${GTest_SOURCE_DIR}" )
    endif ( NOT GTest_FIND_QUIETLY )

    set( GTest_FOUND TRUE )
    set( GTest_INCLUDE_DIR "${GTest_SOURCE_DIR}/include" )
    set( GTest_LIBRARY "${GTest_SOURCE_DIR}/libgtest.a" )
    set( GTest_MAIN_LIBRARY "${GTest_SOURCE_DIR}/libgtest_main.a" )
endif ( )
