# Copyright (c) 2013, 2014 Corvusoft

project( "Unit Test Suite" )

cmake_minimum_required( VERSION 2.8.1 )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/Modules" )

set( DEPENDENCIES GTEST )

foreach( DEPENDENCY ${DEPENDENCIES} )
    find_package( ${DEPENDENCY} REQUIRED )

    if ( ${DEPENDENCY}_NOTFOUND )
        message( "Failed to find dependency: " ${DEPENDENCY} )
    else( )
    	include_directories( ${ASIO_INCLUDE_DIR} )
    endif ( ${DEPENDENCY}_NOTFOUND )
endforeach( DEPENDENCY )

#
# Configuration
#
set( SOURCE_DIR "../source" )

set( CMAKE_INSTALL_PREFIX "../distribution" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_INSTALL_PREFIX}/binary"  )

set( CMAKE_CXX_COMPILER clang++ )

if( CMAKE_BUILD_TYPE MATCHES Debug )
	set( CMAKE_CXX_FLAGS "-stdlib=libc++ -std=c++11 -ggdb -O0 -Wall -Wextra -Weffc++ -pedantic" )
else( )
	set( CMAKE_CXX_FLAGS "-stdlib=libc++ -std=c++11 -Wall -Wextra -Weffc++ -pedantic" )
endif( CMAKE_BUILD_TYPE MATCHES Debug )

link_directories( "../../../distribution/library" )

include_directories( "../../../distribution/include" ${GTEST_INCLUDE_DIR} )

#
# Build
#
add_executable( method_suite ${SOURCE_DIR}/method_suite.cpp )
add_executable( request_suite ${SOURCE_DIR}/request_suite.cpp )
add_executable( settings_suite ${SOURCE_DIR}/settings_suite.cpp )
add_executable( response_suite ${SOURCE_DIR}/response_suite.cpp )
add_executable( resource_suite ${SOURCE_DIR}/resource_suite.cpp )
add_executable( status_code_suite ${SOURCE_DIR}/status_code_suite.cpp )

target_link_libraries( method_suite restbed ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )
target_link_libraries( request_suite restbed ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )
target_link_libraries( settings_suite restbed ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )
target_link_libraries( response_suite restbed ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )
target_link_libraries( resource_suite restbed ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )
target_link_libraries( status_code_suite restbed ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )
