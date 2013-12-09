# Copyright (c) 2013 Corvusoft

project( "Regression Test Suite" )

cmake_minimum_required( VERSION 2.8.1 )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/Modules" )

set( DEPENDENCIES GTEST )

foreach( DEPENDENCY ${DEPENDENCIES} )
    find_package( ${DEPENDENCY} )

    if ( ${DEPENDENCY}_NOTFOUND )
        message( "Failed to find dependency: " ${DEPENDENCY} )
    endif ( ${DEPENDENCY}_NOTFOUND )
endforeach( DEPENDENCY )

#
# Configuration
#
set( SOURCE_DIR "../source" )

set( CMAKE_INSTALL_PREFIX "../distribution" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_INSTALL_PREFIX}/binary"  )

set( CMAKE_CXX_COMPILER clang++ )
set( CMAKE_CXX_FLAGS "-stdlib=libc++ -std=c++11 -Wall -Wextra -Weffc++ -pedantic" )

link_directories( "../../../distribution/library" )

include_directories( "../../../distribution/include" ${GTEST_INCLUDE_DIR} )

#
# Build
#
add_executable( resource_responding_on_invalid_path ${SOURCE_DIR}/resource_responding_on_invalid_path.cpp )
add_executable( segmentation_fault_on_mismatched_path_test ${SOURCE_DIR}/segmentation_fault_on_mismatched_path_test.cpp )

target_link_libraries( resource_responding_on_invalid_path restbed curl ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )
target_link_libraries( segmentation_fault_on_mismatched_path_test restbed curl ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )
