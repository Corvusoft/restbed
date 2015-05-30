# Copyright (c) 2013, 2014, 2015 Corvusoft

project( "integration test suite" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Configuration
#
set( SOURCE_DIR "source" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/distribution/binary/test" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCATCH_CONFIG_MAIN" )

include_directories( ${catch_INCLUDE} )

#
# Build
#
add_executable( session_integration_test_suite ${SOURCE_DIR}/session_suite.cpp )

target_link_libraries( session_integration_test_suite ${CMAKE_PROJECT_NAME} )

#
# Setup
#
enable_testing( )
add_test( session_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_integration_test_suite )
