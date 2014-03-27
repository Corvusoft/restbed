# Copyright (c) 2013, 2014 Corvusoft

project( "Regression Test Suite" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/Modules" )

find_package( gtest REQUIRED )
include_directories( ${GTEST_INCLUDE_DIRS} )

#
# Configuration
#
set( SOURCE_DIR "../source" )

set( CMAKE_INSTALL_PREFIX "../distribution" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_INSTALL_PREFIX}/binary"  )

if( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" )
	if( ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 4.9 )
		message( FATAL_ERROR "\nGCC version < 4.9\nYour systems default compiler is GCC. This project makes use of c++11 features present only in versions of gcc >= 4.9. You can use a different compiler by re-running cmake with the command switch \"-D CMAKE_CXX_COMPILER=<compiler>\" " )
	else()
		set( CMAKE_CXX_FLAGS "" )
	endif()
elseif( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )
	if( ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 3.3 )
		message( FATAL_ERROR "\nClang version < 3.3\nYour systems default compiler is clang. This project makes use of c++11 features present only in versions of clang >= 3.3. You can use a different compiler by re-running cmake with the command switch \"-D CMAKE_CXX_COMPILER=<compiler>\" " )
	else()
		set( CMAKE_CXX_FLAGS "-stdlib=libc++" )
	endif()
else()
	message( FATAL_ERROR "Compiler not supported")
endif()

if( CMAKE_BUILD_TYPE MATCHES Debug )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -Wextra -Weffc++ -pedantic" )
else( )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Weffc++ -pedantic" )
endif( CMAKE_BUILD_TYPE MATCHES Debug )

link_directories( "../../../distribution/library" )

include_directories( "../../../distribution/include" ${GTEST_INCLUDE_DIR} )

#
# Build
#
add_executable( resources_are_not_overwritten ${SOURCE_DIR}/resources_are_not_overwritten.cpp )
add_executable( request_uris_are_not_being_decoded ${SOURCE_DIR}/request_uris_are_not_being_decoded.cpp )
add_executable( resource_responding_on_invalid_path ${SOURCE_DIR}/resource_responding_on_invalid_path.cpp )
add_executable( segmentation_fault_on_mismatched_path ${SOURCE_DIR}/segmentation_fault_on_mismatched_path.cpp )

target_link_libraries( request_uris_are_not_being_decoded restbed curl ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )
target_link_libraries( resources_are_not_overwritten restbed curl ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )
target_link_libraries( resource_responding_on_invalid_path restbed curl ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )
target_link_libraries( segmentation_fault_on_mismatched_path restbed curl ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )
