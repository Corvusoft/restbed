# Copyright (c) 2013, 2014 Corvusoft

project( "regression test suite" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Configuration
#
set( SOURCE_DIR "source" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/distribution/binary/test"  )

include_directories( ${gtest_INCLUDE} ${curl_INCLUDE} ${asio_INCLUDE} )

#
# Build
#
add_executable( resources_are_not_overwritten_regression_test_suite ${SOURCE_DIR}/resources_are_not_overwritten.cpp )
add_executable( missing_regex_support_on_gcc_4.8_regression_test_suite ${SOURCE_DIR}/missing_regex_support_on_gcc_4.8.cpp )
add_executable( request_uris_are_not_being_decoded_regression_test_suite ${SOURCE_DIR}/request_uris_are_not_being_decoded.cpp )
add_executable( resource_responding_on_invalid_path_regression_test_suite ${SOURCE_DIR}/resource_responding_on_invalid_path.cpp )
add_executable( segmentation_fault_on_mismatched_path_regression_test_suite ${SOURCE_DIR}/segmentation_fault_on_mismatched_path.cpp )
add_executable( exception_thrown_with_space_in_resource_path_regression_test_suite ${SOURCE_DIR}/exception_thrown_with_space_in_resource_path.cpp )
add_executable( uncaught_exception_when_peer_closes_connection_regression_test_suite ${SOURCE_DIR}/uncaught_exception_when_peer_closes_connection.cpp )
add_executable( error_handler_not_overwritten_test_suite ${SOURCE_DIR}/error_handler_not_overwritten.cpp )
add_executable( large_request_bodies_being_trimmed_test_suite ${SOURCE_DIR}/large_request_bodies_being_trimmed.cpp )

target_link_libraries( resources_are_not_overwritten_regression_test_suite ${gtest_LIBRARY} ${gtest_MAIN_LIBRARY} ${CMAKE_PROJECT_NAME} ${curl_LIBRARY} pthread )
target_link_libraries( missing_regex_support_on_gcc_4.8_regression_test_suite ${gtest_LIBRARY} ${gtest_MAIN_LIBRARY} ${CMAKE_PROJECT_NAME} ${curl_LIBRARY} pthread )
target_link_libraries( request_uris_are_not_being_decoded_regression_test_suite ${gtest_LIBRARY} ${gtest_MAIN_LIBRARY} ${CMAKE_PROJECT_NAME} ${curl_LIBRARY} pthread )
target_link_libraries( resource_responding_on_invalid_path_regression_test_suite ${gtest_LIBRARY} ${gtest_MAIN_LIBRARY} ${CMAKE_PROJECT_NAME} ${curl_LIBRARY} pthread )
target_link_libraries( segmentation_fault_on_mismatched_path_regression_test_suite ${gtest_LIBRARY} ${gtest_MAIN_LIBRARY} ${CMAKE_PROJECT_NAME} ${curl_LIBRARY} pthread )
target_link_libraries( exception_thrown_with_space_in_resource_path_regression_test_suite ${gtest_LIBRARY} ${gtest_MAIN_LIBRARY} ${CMAKE_PROJECT_NAME} ${curl_LIBRARY} pthread )
target_link_libraries( uncaught_exception_when_peer_closes_connection_regression_test_suite ${gtest_LIBRARY} ${gtest_MAIN_LIBRARY} ${CMAKE_PROJECT_NAME} pthread )
target_link_libraries( error_handler_not_overwritten_test_suite ${gtest_LIBRARY} ${gtest_MAIN_LIBRARY} ${CMAKE_PROJECT_NAME} ${curl_LIBRARY} pthread )
target_link_libraries( large_request_bodies_being_trimmed_test_suite ${gtest_LIBRARY} ${gtest_MAIN_LIBRARY} ${CMAKE_PROJECT_NAME} ${curl_LIBRARY} pthread )

#
# Setup
#
enable_testing( )
add_test( resources_are_not_overwritten_regression_test_suite ${EXECUTABLE_OUTPUT_PATH}/resources_are_not_overwritten_regression_test_suite )
add_test( missing_regex_support_on_gcc_4.8_regression_test_suite ${EXECUTABLE_OUTPUT_PATH}/missing_regex_support_on_gcc_4.8_regression_test_suite )
add_test( request_uris_are_not_being_decoded_regression_test_suite ${EXECUTABLE_OUTPUT_PATH}/request_uris_are_not_being_decoded_regression_test_suite )
add_test( resource_responding_on_invalid_path_regression_test_suite ${EXECUTABLE_OUTPUT_PATH}/resource_responding_on_invalid_path_regression_test_suite )
add_test( segmentation_fault_on_mismatched_path_regression_test_suite ${EXECUTABLE_OUTPUT_PATH}/segmentation_fault_on_mismatched_path_regression_test_suite )
add_test( exception_thrown_with_space_in_resource_path_regression_test_suite ${EXECUTABLE_OUTPUT_PATH}/exception_thrown_with_space_in_resource_path_regression_test_suite )
add_test( uncaught_exception_when_peer_closes_connection_regression_test_suite ${EXECUTABLE_OUTPUT_PATH}/uncaught_exception_when_peer_closes_connection_regression_test_suite )
add_test( error_handler_not_overwritten_test_suite ${EXECUTABLE_OUTPUT_PATH}/error_handler_not_overwritten_test_suite )
add_test( large_request_bodies_being_trimmed_test_suite ${EXECUTABLE_OUTPUT_PATH}/large_request_bodies_being_trimmed_test_suite )
