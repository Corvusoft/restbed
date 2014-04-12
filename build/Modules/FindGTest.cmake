# Copyright (c) 2013, 2014 Corvusoft

find_path( GTest_SOURCE_DIR "CMakeLists.txt" "../dependency/gtest" )
find_path( GTest_INCLUDE_DIR "gtest.h" "${GTest_SOURCE_DIR}/include/gtest")
find_path( GTest_CC_FILE "gtest.cc" "${GTest_SOURCE_DIR}/src")

if ( NOT GTest_INCLUDE_DIR OR NOT GTest_SOURCE_DIR OR NOT GTest_CC_FILE )

    if ( GTest_FIND_REQUIRED )
        message( FATAL_ERROR "Could not find gtest source directory or the directory has missing files." )
    endif ( GTest_FIND_REQUIRED )

else( )

    if ( NOT GTest_FIND_QUIETLY )
        message( STATUS "Found gtest: ${GTest_SOURCE_DIR}" )
    endif ( NOT  GTest_FIND_QUIETLY )

    set( GTest_FOUND TRUE )
    set( GTest_INCLUDE_DIR "${GTest_SOURCE_DIR}/include" )

endif ( )

