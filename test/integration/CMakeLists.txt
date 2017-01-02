# Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.

project( "integration test suite" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Configuration
#
set( SOURCE_DIR "source" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCATCH_CONFIG_MAIN" )

include_directories( SYSTEM ${catch_INCLUDE} )

#
# Build
#
add_executable( request_integration_test_suite ${SOURCE_DIR}/request_suite.cpp )
target_link_libraries( request_integration_test_suite ${CMAKE_PROJECT_NAME} )
add_test( request_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/request_integration_test_suite )

add_executable( string_integration_test_suite ${SOURCE_DIR}/string_suite.cpp )
target_link_libraries( string_integration_test_suite ${CMAKE_PROJECT_NAME} )
add_test( string_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/string_integration_test_suite )

add_executable( session_integration_test_suite ${SOURCE_DIR}/session_suite.cpp )
target_link_libraries( session_integration_test_suite ${CMAKE_PROJECT_NAME} )
add_test( session_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_integration_test_suite )

add_executable( resource_integration_test_suite ${SOURCE_DIR}/resource_suite.cpp )
target_link_libraries( resource_integration_test_suite ${CMAKE_PROJECT_NAME} )
add_test( resource_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/resource_integration_test_suite )

add_executable( response_integration_test_suite ${SOURCE_DIR}/response_suite.cpp )
target_link_libraries( response_integration_test_suite ${CMAKE_PROJECT_NAME} )
add_test( response_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/response_integration_test_suite )

add_executable( ssl_settings_integration_test_suite ${SOURCE_DIR}/ssl_settings_suite.cpp )
target_link_libraries( ssl_settings_integration_test_suite ${CMAKE_PROJECT_NAME} )
add_test( ssl_settings_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/ssl_settings_integration_test_suite )

add_executable( settings_integration_test_suite ${SOURCE_DIR}/settings_suite.cpp )
target_link_libraries( settings_integration_test_suite ${CMAKE_PROJECT_NAME} )
add_test( settings_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/settings_integration_test_suite )

add_executable( service_integration_test_suite ${SOURCE_DIR}/service_suite.cpp )
target_link_libraries( service_integration_test_suite ${CMAKE_PROJECT_NAME} )
add_test( service_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/service_integration_test_suite )

add_executable( http_integration_test_suite ${SOURCE_DIR}/http_suite.cpp )
target_link_libraries( http_integration_test_suite ${CMAKE_PROJECT_NAME} )
add_test( http_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_integration_test_suite )

add_executable( web_socket_message_integration_test_suite ${SOURCE_DIR}/web_socket_message_suite.cpp )
target_link_libraries( web_socket_message_integration_test_suite ${CMAKE_PROJECT_NAME} )
add_test( web_socket_message_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/web_socket_message_integration_test_suite )
