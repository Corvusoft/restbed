# Copyright (c) 2013, 2014 Corvusoft

project( "Regression Test Suite" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Configuration
#
set( SOURCE_DIR "source" )

set( CMAKE_INSTALL_PREFIX "distribution" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_INSTALL_PREFIX}/binary"  )

include_directories( ${GTest_INCLUDE_DIR} ${curl_INCLUDE_DIR} ${ASIO_INCLUDE_DIRS} )

#
# Build
#
add_executable( resources_are_not_overwritten ${SOURCE_DIR}/resources_are_not_overwritten.cpp )
add_executable( missing_regex_support_on_gcc_4.8 ${SOURCE_DIR}/missing_regex_support_on_gcc_4.8.cpp )
add_executable( request_uris_are_not_being_decoded ${SOURCE_DIR}/request_uris_are_not_being_decoded.cpp )
add_executable( resource_responding_on_invalid_path ${SOURCE_DIR}/resource_responding_on_invalid_path.cpp )
add_executable( segmentation_fault_on_mismatched_path ${SOURCE_DIR}/segmentation_fault_on_mismatched_path.cpp )
add_executable( uncaught_exception_when_peer_closes_connection ${SOURCE_DIR}/uncaught_exception_when_peer_closes_connection.cpp )

target_link_libraries( resources_are_not_overwritten ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} restbed ${curl_LIBRARY} pthread )
target_link_libraries( missing_regex_support_on_gcc_4.8 ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} restbed ${curl_LIBRARY} pthread )
target_link_libraries( request_uris_are_not_being_decoded ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} restbed ${curl_LIBRARY} pthread )
target_link_libraries( resource_responding_on_invalid_path ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} restbed ${curl_LIBRARY} pthread )
target_link_libraries( segmentation_fault_on_mismatched_path ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} restbed ${curl_LIBRARY} pthread )
target_link_libraries( uncaught_exception_when_peer_closes_connection ${GTest_LIBRARY} ${GTest_MAIN_LIBRARY} restbed pthread )

#
# Setup tests
#
enable_testing()
add_test( run_resources_are_not_overwritten ${EXECUTABLE_OUTPUT_PATH}/resources_are_not_overwritten )
add_test( run_missing_regex_support_on_gcc_4.8 ${EXECUTABLE_OUTPUT_PATH}/missing_regex_support_on_gcc_4.8 )
add_test( run_request_uris_are_not_being_decoded ${EXECUTABLE_OUTPUT_PATH}/request_uris_are_not_being_decoded )
add_test( run_resource_responding_on_invalid_path ${EXECUTABLE_OUTPUT_PATH}/resource_responding_on_invalid_path )
add_test( run_segmentation_fault_on_mismatched_path ${EXECUTABLE_OUTPUT_PATH}/segmentation_fault_on_mismatched_path )
add_test( uncaught_exception_when_peer_closes_connection ${EXECUTABLE_OUTPUT_PATH}/uncaught_exception_when_peer_closes_connection )

