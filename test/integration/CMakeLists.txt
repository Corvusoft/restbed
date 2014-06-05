# Copyright (c) 2013, 2014 Corvusoft

project( "Integration Test Suite" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Configuration
#
set( SOURCE_DIR "source" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/distribution/binary/test" )

include_directories( ${GTest_INCLUDE_DIR} )

#
# Build
#
add_executable( request_integration_test_suite ${SOURCE_DIR}/request_suite.cpp )
add_executable( service_integration_test_suite ${SOURCE_DIR}/service_suite.cpp )
add_executable( resource_integration_test_suite ${SOURCE_DIR}/resource_suite.cpp )
add_executable( settings_integration_test_suite ${SOURCE_DIR}/settings_suite.cpp )

target_link_libraries( request_integration_test_suite restbed ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} )
target_link_libraries( service_integration_test_suite restbed ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} )
target_link_libraries( resource_integration_test_suite restbed ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} )
target_link_libraries( settings_integration_test_suite restbed ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} )

#
# Setup Tests
#
enable_testing( )
add_test( request_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/request_integration_test_suite )
add_test( service_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/service_integration_test_suite )
add_test( resource_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/resource_integration_test_suite )
add_test( settings_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/settings_integration_test_suite )

