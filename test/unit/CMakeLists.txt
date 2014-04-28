# Copyright (c) 2013, 2014 Corvusoft

project( "Unit Test Suite" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Configuration
#
set( SOURCE_DIR "source" )

set( CMAKE_INSTALL_PREFIX "distribution" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_INSTALL_PREFIX}/binary"  )

include_directories( ${GTest_INCLUDE_DIR} )

#
# Build
#
add_executable( unit_method_suite ${SOURCE_DIR}/method_suite.cpp )
add_executable( unit_request_suite ${SOURCE_DIR}/request_suite.cpp )
add_executable( unit_settings_suite ${SOURCE_DIR}/settings_suite.cpp )
add_executable( unit_response_suite ${SOURCE_DIR}/response_suite.cpp )
add_executable( unit_resource_suite ${SOURCE_DIR}/resource_suite.cpp )
add_executable( unit_status_code_suite ${SOURCE_DIR}/status_code_suite.cpp )

target_link_libraries( unit_method_suite restbed gtest_main )
target_link_libraries( unit_request_suite restbed gtest_main )
target_link_libraries( unit_settings_suite restbed gtest_main )
target_link_libraries( unit_response_suite restbed gtest_main )
target_link_libraries( unit_resource_suite restbed gtest_main )
target_link_libraries( unit_status_code_suite restbed gtest_main )

#
# Setup Tests
#
enable_testing()
add_test( run_unit_method_suite ${EXECUTABLE_OUTPUT_PATH}/unit_method_suite )
add_test( run_unit_request_suite ${EXECUTABLE_OUTPUT_PATH}/unit_request_suite )
add_test( run_unit_settings_suite ${EXECUTABLE_OUTPUT_PATH}/unit_settings_suite )
add_test( run_unit_response_suite ${EXECUTABLE_OUTPUT_PATH}/unit_response_suite )
add_test( run_unit_resource_suite ${EXECUTABLE_OUTPUT_PATH}/unit_resource_suite )
add_test( run_unit_status_code_suite ${EXECUTABLE_OUTPUT_PATH}/unit_status_code_suite )



