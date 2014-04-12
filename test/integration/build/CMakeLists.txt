# Copyright (c) 2013, 2014 Corvusoft

project( "Integration Test Suite" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/Modules" )

find_package( GTest REQUIRED )
include_directories( ${GTEST_INCLUDE_DIRS} )

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
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -Wextra -Weffc++ -pedantic" )
else( )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Weffc++ -pedantic" )
endif( CMAKE_BUILD_TYPE MATCHES Debug )

include_directories( ${RESTBED_INCLUDE_DIR} ${GTest_INCLUDE_DIR} )

add_subdirectory( ${GTest_SOURCE_DIR} "${CMAKE_BINARY_DIR}/gtest-build" )

add_subdirectory( "../../../build" "${CMAKE_BINARY_DIR}/restbed-build" )

#
# Build
#
add_executable( request_suite ${SOURCE_DIR}/request_suite.cpp )
add_executable( service_suite ${SOURCE_DIR}/service_suite.cpp )
add_executable( resource_suite ${SOURCE_DIR}/resource_suite.cpp )
add_executable( settings_suite ${SOURCE_DIR}/settings_suite.cpp )

target_link_libraries( request_suite restbed gtest_main )
target_link_libraries( service_suite restbed gtest_main )
target_link_libraries( resource_suite restbed gtest_main )
target_link_libraries( settings_suite restbed gtest_main )

#
# Setup Tests
#
enable_testing()

add_test( run_request_suite ${EXECUTABLE_OUTPUT_PATH}/request_suite )
add_test( run_service_suite ${EXECUTABLE_OUTPUT_PATH}/service_suite )
add_test( run_resource_suite ${EXECUTABLE_OUTPUT_PATH}/resource_suite )
add_test( run_settings_suite ${EXECUTABLE_OUTPUT_PATH}/settings_suite )

