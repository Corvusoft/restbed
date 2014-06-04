# Copyright (c) 2013, 2014 Corvusoft

project( "Integration Test Suite" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Configuration
#
set( SOURCE_DIR "source" )

set( CMAKE_INSTALL_PREFIX "distribution" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_INSTALL_PREFIX}/binary" )

include_directories( ${GTest_INCLUDE_DIR} )

#
# Build
#
add_executable( integration_request_suite ${SOURCE_DIR}/request_suite.cpp )
add_executable( integration_service_suite ${SOURCE_DIR}/service_suite.cpp )
add_executable( integration_resource_suite ${SOURCE_DIR}/resource_suite.cpp )
add_executable( integration_settings_suite ${SOURCE_DIR}/settings_suite.cpp )

target_link_libraries( integration_request_suite restbed ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} )
target_link_libraries( integration_service_suite restbed ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} )
target_link_libraries( integration_resource_suite restbed ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} )
target_link_libraries( integration_settings_suite restbed ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} )

#
# Setup Tests
#
enable_testing()
add_test( run_integration_request_suite ${EXECUTABLE_OUTPUT_PATH}/integration_request_suite )
add_test( run_integration_service_suite ${EXECUTABLE_OUTPUT_PATH}/integration_service_suite )
add_test( run_integration_resource_suite ${EXECUTABLE_OUTPUT_PATH}/integration_resource_suite )
add_test( run_integration_settings_suite ${EXECUTABLE_OUTPUT_PATH}/integration_settings_suite )

