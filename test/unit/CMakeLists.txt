project( "unit test suite" )

cmake_minimum_required( VERSION 3.1.0 FATAL_ERROR )

#
# Configuration
#
set( SOURCE_DIR "source" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCATCH_CONFIG_MAIN" )

include_directories( SYSTEM ${catch_INCLUDE} )

#
# Build
#
add_executable( uri_unit_test_suite ${SOURCE_DIR}/uri_suite.cpp )
target_link_libraries( uri_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( uri_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/uri_unit_test_suite )

add_executable( string_unit_test_suite ${SOURCE_DIR}/string_suite.cpp )
target_link_libraries( string_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( string_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/string_unit_test_suite )

add_executable( session_unit_test_suite ${SOURCE_DIR}/session_suite.cpp )
target_link_libraries( session_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( session_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/session_unit_test_suite )

add_executable( service_unit_test_suite ${SOURCE_DIR}/service_suite.cpp )
target_link_libraries( service_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( service_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/service_unit_test_suite )

add_executable( request_unit_test_suite ${SOURCE_DIR}/request_suite.cpp )
target_link_libraries( request_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( request_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/request_unit_test_suite )

add_executable( settings_unit_test_suite ${SOURCE_DIR}/settings_suite.cpp )
target_link_libraries( settings_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( settings_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/settings_unit_test_suite )

add_executable( response_unit_test_suite ${SOURCE_DIR}/response_suite.cpp )
target_link_libraries( response_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( response_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/response_unit_test_suite )

add_executable( resource_unit_test_suite ${SOURCE_DIR}/resource_suite.cpp )
target_link_libraries( resource_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( resource_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/resource_unit_test_suite )

add_executable( ssl_settings_unit_test_suite ${SOURCE_DIR}/ssl_settings_suite.cpp )
target_link_libraries( ssl_settings_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( ssl_settings_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/ssl_settings_unit_test_suite )

add_executable( web_socket_message_unit_test_suite ${SOURCE_DIR}/web_socket_message_suite.cpp )
target_link_libraries( web_socket_message_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( web_socket_message_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/web_socket_message_unit_test_suite )
