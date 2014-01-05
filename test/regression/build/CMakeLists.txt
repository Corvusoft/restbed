# Copyright (c) 2013 Corvusoft

project( "Regression Test Suite" )

cmake_minimum_required( VERSION 2.8.1 )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/Modules" )

set( DEPENDENCIES gtest )

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
add_executable( resources_are_not_overwritten ${SOURCE_DIR}/resources_are_not_overwritten.cpp )
add_executable( resource_responding_on_invalid_path ${SOURCE_DIR}/resource_responding_on_invalid_path.cpp )
add_executable( segmentation_fault_on_mismatched_path ${SOURCE_DIR}/segmentation_fault_on_mismatched_path.cpp )

target_link_libraries( resources_are_not_overwritten restbed curl ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )
target_link_libraries( resource_responding_on_invalid_path restbed curl ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )
target_link_libraries( segmentation_fault_on_mismatched_path restbed curl ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )
