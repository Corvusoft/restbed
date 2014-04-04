# Copyright (c) 2013, 2014 Corvusoft

project( "Regression Test Suite" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/Modules" )

find_package( GTest REQUIRED )

#
# Configuration
#
set( SOURCE_DIR "../source" )

set( CMAKE_INSTALL_PREFIX "../distribution" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_INSTALL_PREFIX}/binary"  )

set( RESTBED_INCLUDE_DIR "../../../distribution/include" )
set( RESTBED_LIBRARY_DIR "../../../distribution/library" )

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
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -Wextra -Weffc++ -pedantic -D GTest_USE_OWN_TR1_TUPLE=1" )
else( )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Weffc++ -pedantic -D GTest_USE_OWN_TR1_TUPLE=1" )
endif( CMAKE_BUILD_TYPE MATCHES Debug )

link_directories( ${RESTBED_LIBRARY_DIR} )

include_directories( ${RESTBED_INCLUDE_DIR} ${GTest_INCLUDE_DIR} )

add_subdirectory( ${GTest_SOURCE_DIR} "${CMAKE_BINARY_DIR}/gtest-build" )
#add_subdirectory( "../../../build" "${CMAKE_BINARY_DIR}/restbed-build")

#
# Build
#
add_executable( resources_are_not_overwritten ${SOURCE_DIR}/resources_are_not_overwritten.cpp )
add_executable( missing_regex_support_on_gcc_4.8 ${SOURCE_DIR}/missing_regex_support_on_gcc_4.8.cpp )
add_executable( request_uris_are_not_being_decoded ${SOURCE_DIR}/request_uris_are_not_being_decoded.cpp )
add_executable( resource_responding_on_invalid_path ${SOURCE_DIR}/resource_responding_on_invalid_path.cpp )
add_executable( segmentation_fault_on_mismatched_path ${SOURCE_DIR}/segmentation_fault_on_mismatched_path.cpp )

target_link_libraries( resources_are_not_overwritten gtest_main restbed curl pthread )
target_link_libraries( missing_regex_support_on_gcc_4.8 gtest_main restbed curl pthread )
target_link_libraries( request_uris_are_not_being_decoded gtest_main restbed curl pthread )
target_link_libraries( resource_responding_on_invalid_path gtest_main restbed curl pthread )
target_link_libraries( segmentation_fault_on_mismatched_path gtest_main restbed curl pthread )