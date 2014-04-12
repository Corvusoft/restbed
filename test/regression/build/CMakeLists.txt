# Copyright (c) 2013, 2014 Corvusoft

project( "Regression Test Suite" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/Modules" )

include( ${CMAKE_MODULE_PATH}/build_curl.cmake )

find_package( GTest REQUIRED )
find_package( curl  REQUIRED )

if( NOT curl_FOUND )
	build_curl( ${curl_DEPENDENCY_DIR} )
endif()

#
# Configuration
#
set( SOURCE_DIR "../source" )

set( CMAKE_INSTALL_PREFIX "../distribution" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_INSTALL_PREFIX}/binary"  )

set( RESTBED_INCLUDE_DIR "../../../source" )

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

include_directories( ${RESTBED_INCLUDE_DIR} ${GTest_INCLUDE_DIR} ${curl_INCLUDE_DIR} )

# Prevent circular dependencies when building tests from elsewhere.
if( "${CMAKE_PROJECT_NAME}" STREQUAL "Regression Test Suite" )
	add_subdirectory( ${GTest_SOURCE_DIR} "${CMAKE_BINARY_DIR}/gtest-build" )
	add_subdirectory( "../../../build" "${CMAKE_BINARY_DIR}/restbed-build" )
endif()

link_directories( ${curl_LIBRARY_DIR} )

#
# Build
#
add_executable( resources_are_not_overwritten ${SOURCE_DIR}/resources_are_not_overwritten.cpp )
add_executable( missing_regex_support_on_gcc_4.8 ${SOURCE_DIR}/missing_regex_support_on_gcc_4.8.cpp )
add_executable( request_uris_are_not_being_decoded ${SOURCE_DIR}/request_uris_are_not_being_decoded.cpp )
add_executable( resource_responding_on_invalid_path ${SOURCE_DIR}/resource_responding_on_invalid_path.cpp )
add_executable( segmentation_fault_on_mismatched_path ${SOURCE_DIR}/segmentation_fault_on_mismatched_path.cpp )

if( BUILD_CURL_FROM_SCRATCH MATCHES TRUE )
	add_dependencies( resources_are_not_overwritten curl )
	add_dependencies( missing_regex_support_on_gcc_4.8 curl )
	add_dependencies( request_uris_are_not_being_decoded curl )
	add_dependencies( resource_responding_on_invalid_path curl )
	add_dependencies( segmentation_fault_on_mismatched_path curl )
endif()

target_link_libraries( resources_are_not_overwritten gtest_main restbed ${curl_LIBRARY} pthread )
target_link_libraries( missing_regex_support_on_gcc_4.8 gtest_main restbed ${curl_LIBRARY} pthread )
target_link_libraries( request_uris_are_not_being_decoded gtest_main restbed ${curl_LIBRARY} pthread )
target_link_libraries( resource_responding_on_invalid_path gtest_main restbed ${curl_LIBRARY} pthread )
target_link_libraries( segmentation_fault_on_mismatched_path gtest_main restbed ${curl_LIBRARY} pthread )

#
# Setup tests
#
enable_testing()
add_test( run_resources_are_not_overwritten ${EXECUTABLE_OUTPUT_PATH}/resources_are_not_overwritten )
add_test( run_missing_regex_support_on_gcc_4.8 ${EXECUTABLE_OUTPUT_PATH}/missing_regex_support_on_gcc_4.8 )
add_test( run_request_uris_are_not_being_decoded ${EXECUTABLE_OUTPUT_PATH}/request_uris_are_not_being_decoded )
add_test( run_resource_responding_on_invalid_path ${EXECUTABLE_OUTPUT_PATH}/resource_responding_on_invalid_path )
add_test( run_segmentation_fault_on_mismatched_path ${EXECUTABLE_OUTPUT_PATH}/segmentation_fault_on_mismatched_path )

