# Copyright (c) 2013, 2014, 2015 Corvusoft

project( "unit test suite" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Configuration
#
set( SOURCE_DIR "source" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/distribution/binary/test"  )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCATCH_CONFIG_MAIN" )

include_directories( ${catch_INCLUDE} )

#
# Build
#
#add_executable( request_unit_test_suite ${SOURCE_DIR}/request_suite.cpp )
add_executable( settings_unit_test_suite ${SOURCE_DIR}/settings_suite.cpp )
#add_executable( response_unit_test_suite ${SOURCE_DIR}/response_suite.cpp )
#add_executable( resource_unit_test_suite ${SOURCE_DIR}/resource_suite.cpp )

#target_link_libraries( request_unit_test_suite ${CMAKE_PROJECT_NAME} )
target_link_libraries( settings_unit_test_suite ${CMAKE_PROJECT_NAME} )
#target_link_libraries( response_unit_test_suite ${CMAKE_PROJECT_NAME} )
#target_link_libraries( resource_unit_test_suite ${CMAKE_PROJECT_NAME} )

#
# Setup
#
enable_testing( )
#add_test( request_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/request_unit_test_suite )
add_test( settings_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/settings_unit_test_suite )
#add_test( response_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/response_unit_test_suite )
#add_test( resource_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/resource_unit_test_suite )
