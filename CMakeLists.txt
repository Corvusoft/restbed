# Copyright (c) 2013, 2014 Corvusoft

project( "Restbed" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Build Options
#
option( BUILD_TESTS "Build all test suites using CTest." OFF )
option( BUILD_EXAMPLES "Build the examples." OFF )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake" )

find_package( asio REQUIRED )
include_directories( ${ASIO_INCLUDE_DIRS} )

#
# Configuration
#
set( SOURCE_DIR "${CMAKE_SOURCE_DIR}/source" )
set( FRAMEWORK_SOURCE_DIR "${SOURCE_DIR}/corvusoft/restbed" )

set( CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/distribution" )
set( LIBRARY_OUTPUT_PATH    "${CMAKE_INSTALL_PREFIX}/library" )

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

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DASIO_STANDALONE=YES" )

#
# Build
#
include( "${CMAKE_SOURCE_DIR}/cmake/build_manifest.cmake" )

include_directories( ${SOURCE_DIR} )

add_library( restbed SHARED ${MANIFEST} )

target_link_libraries( restbed pthread )

# Build examples
if( BUILD_EXAMPLES )
	add_subdirectory( "${CMAKE_SOURCE_DIR}/example" "examples" )
endif()

#
# Install
#
file( MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/library" )
file( MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/include/corvusoft" )

include( "${CMAKE_SOURCE_DIR}/cmake/build_artifacts.cmake" )

install( FILES ${SOURCE_DIR}/restbed DESTINATION "include/" )
install( FILES ${FRAMEWORK_ARTIFACTS} DESTINATION "include/corvusoft/restbed" )

#
# Test
#
if( BUILD_TESTS )
	find_package( GTest REQUIRED )
	find_package( curl REQUIRED )

	enable_testing()
	add_subdirectory( "${CMAKE_SOURCE_DIR}/test/acceptance" "acceptance-tests" )
	add_subdirectory( "${CMAKE_SOURCE_DIR}/test/integration" "integration-tests" )
	add_subdirectory( "${CMAKE_SOURCE_DIR}/test/regression" "regression-tests" )
	add_subdirectory( "${CMAKE_SOURCE_DIR}/test/unit" "unit-tests" )
endif()
