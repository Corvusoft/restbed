# Copyright (c) 2013, 2014 Corvusoft

project( "Unit Test Suite" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Configuration
#
set( SOURCE_DIR "source" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/distribution/binary/test"  )

include_directories( ${GTest_INCLUDE_DIR} )

#
# Build
#
add_executable( method_unit_test_suite ${SOURCE_DIR}/method_suite.cpp )
add_executable( request_unit_test_suite ${SOURCE_DIR}/request_suite.cpp )
add_executable( settings_unit_test_suite ${SOURCE_DIR}/settings_suite.cpp )
add_executable( response_unit_test_suite ${SOURCE_DIR}/response_suite.cpp )
add_executable( resource_unit_test_suite ${SOURCE_DIR}/resource_suite.cpp )
add_executable( status_code_unit_test_suite ${SOURCE_DIR}/status_code_suite.cpp )

target_link_libraries( method_unit_test_suite restbed ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} )
target_link_libraries( request_unit_test_suite restbed ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} )
target_link_libraries( settings_unit_test_suite restbed ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} )
target_link_libraries( response_unit_test_suite restbed ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} )
target_link_libraries( resource_unit_test_suite restbed ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} )
target_link_libraries( status_code_unit_test_suite restbed ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} )

#
# Setup Tests
#
enable_testing()
add_test( method_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/method_unit_test_suite )
add_test( request_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/request_unit_test_suite )
add_test( settings_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/settings_unit_test_suite )
add_test( response_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/response_unit_test_suite )
add_test( resource_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/resource_unit_test_suite )
add_test( status_code_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/status_code_unit_test_suite )

