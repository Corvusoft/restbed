project( "test suite" )

cmake_minimum_required( VERSION 3.22.0 FATAL_ERROR )

#
# Configuration
#
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCATCH_CONFIG_MAIN" )

include_directories( SYSTEM ${catch_INCLUDE} )

if( ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_WIN32_WINNT=0x0A00 /W4 /wd4068 /wd4702 /wd4996 /wd4265" )
endif ( )

if ( WIN32 )
	set( OPENSSL_DEPS ws2_32.lib advapi32.lib crypt32.lib gdi32.lib user32.lib )
endif ( )

# Unit Tests
add_executable( uri_unit_suite uri_unit_suite.cpp )
target_link_libraries( uri_unit_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS} ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( uri_unit_suite ${EXECUTABLE_OUTPUT_PATH}/uri_unit_suite )

add_executable( string_unit_suite string_unit_suite.cpp )
target_link_libraries( string_unit_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS} ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( string_unit_suite ${EXECUTABLE_OUTPUT_PATH}/string_unit_suite )

add_executable( session_unit_suite session_unit_suite.cpp )
target_link_libraries( session_unit_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS} ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( session_unit_suite ${EXECUTABLE_OUTPUT_PATH}/session_unit_suite )

add_executable( service_unit_suite service_unit_suite.cpp )
target_link_libraries( service_unit_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS} ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( service_unit_suite ${EXECUTABLE_OUTPUT_PATH}/service_unit_suite )

add_executable( request_unit_suite request_unit_suite.cpp )
target_link_libraries( request_unit_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS} ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( request_unit_suite ${EXECUTABLE_OUTPUT_PATH}/request_unit_suite )

add_executable( settings_unit_suite settings_unit_suite.cpp )
target_link_libraries( settings_unit_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS} ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( settings_unit_suite ${EXECUTABLE_OUTPUT_PATH}/settings_unit_suite )

add_executable( response_unit_suite response_unit_suite.cpp )
target_link_libraries( response_unit_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS} ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( response_unit_suite ${EXECUTABLE_OUTPUT_PATH}/response_unit_suite )

add_executable( resource_unit_suite resource_unit_suite.cpp )
target_link_libraries( resource_unit_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS} ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( resource_unit_suite ${EXECUTABLE_OUTPUT_PATH}/resource_unit_suite )

add_executable( ssl_settings_unit_suite ssl_settings_unit_suite.cpp )
target_link_libraries( ssl_settings_unit_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS} ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( ssl_settings_unit_suite ${EXECUTABLE_OUTPUT_PATH}/ssl_settings_unit_suite )

add_executable( web_socket_message_unit_suite web_socket_message_unit_suite.cpp )
target_link_libraries( web_socket_message_unit_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS} ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( web_socket_message_unit_suite ${EXECUTABLE_OUTPUT_PATH}/web_socket_message_unit_suite )

# Integration Tests
add_executable( request_integration_suite request_integration_suite.cpp )
target_link_libraries( request_integration_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( request_integration_suite ${EXECUTABLE_OUTPUT_PATH}/request_integration_suite )

add_executable( string_integration_suite string_integration_suite.cpp )
target_link_libraries( string_integration_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( string_integration_suite ${EXECUTABLE_OUTPUT_PATH}/string_integration_suite )

add_executable( session_integration_suite session_integration_suite.cpp )
target_link_libraries( session_integration_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( session_integration_suite ${EXECUTABLE_OUTPUT_PATH}/session_integration_suite )

add_executable( resource_integration_suite resource_integration_suite.cpp )
target_link_libraries( resource_integration_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( resource_integration_suite ${EXECUTABLE_OUTPUT_PATH}/resource_integration_suite )

add_executable( response_integration_suite response_integration_suite.cpp )
target_link_libraries( response_integration_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( response_integration_suite ${EXECUTABLE_OUTPUT_PATH}/response_integration_suite )

add_executable( ssl_settings_integration_suite ssl_settings_integration_suite.cpp )
target_link_libraries( ssl_settings_integration_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( ssl_settings_integration_suite ${EXECUTABLE_OUTPUT_PATH}/ssl_settings_integration_suite )

add_executable( settings_integration_suite settings_integration_suite.cpp )
target_link_libraries( settings_integration_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( settings_integration_suite ${EXECUTABLE_OUTPUT_PATH}/settings_integration_suite )

add_executable( service_integration_suite service_integration_suite.cpp )
target_link_libraries( service_integration_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( service_integration_suite ${EXECUTABLE_OUTPUT_PATH}/service_integration_suite )

add_executable( web_socket_message_integration_suite web_socket_message_integration_suite.cpp )
target_link_libraries( web_socket_message_integration_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( web_socket_message_integration_suite ${EXECUTABLE_OUTPUT_PATH}/web_socket_message_integration_suite )

# Regresssion Tests
add_executable( missing_regex_support_on_gcc_4.8_regression_suite missing_regex_support_on_gcc_4.8_regression_suite.cpp )
target_link_libraries( missing_regex_support_on_gcc_4.8_regression_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( missing_regex_support_on_gcc_4.8_regression_suite ${EXECUTABLE_OUTPUT_PATH}/missing_regex_support_on_gcc_4.8_regression_suite )

add_executable( resource_error_handler_overflow_regression_suite resource_error_handler_overflow_regression_suite.cpp )
target_link_libraries( resource_error_handler_overflow_regression_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( resource_error_handler_overflow_regression_suite ${EXECUTABLE_OUTPUT_PATH}/resource_error_handler_overflow_regression_suite )

add_executable( service_error_handler_overflow_regression_suite service_error_handler_overflow_regression_suite.cpp )
target_link_libraries( service_error_handler_overflow_regression_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( service_error_handler_overflow_regression_suite ${EXECUTABLE_OUTPUT_PATH}/service_error_handler_overflow_regression_suite )

add_executable( ssl_settings_to_handle_windows_path_regression_suite ssl_settings_to_handle_windows_paths_regression_suite.cpp )
target_link_libraries( ssl_settings_to_handle_windows_path_regression_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( ssl_settings_to_handle_windows_path_regression_suite ${EXECUTABLE_OUTPUT_PATH}/ssl_settings_to_handle_windows_path_regression_suite )

add_executable( uncaught_exception_when_peer_closes_connection_regression_suite uncaught_exception_when_peer_closes_connection_regression_suite.cpp )
target_link_libraries( uncaught_exception_when_peer_closes_connection_regression_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( uncaught_exception_when_peer_closes_connection_regression_suite ${EXECUTABLE_OUTPUT_PATH}/uncaught_exception_when_peer_closes_connection_regression_suite )

add_executable( uri_fails_to_handle_file_scheme_relative_paths_regression_suite uri_fails_to_handle_file_scheme_relative_paths_regression_suite.cpp )
target_link_libraries( uri_fails_to_handle_file_scheme_relative_paths_regression_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( uri_fails_to_handle_file_scheme_relative_paths_regression_suite ${EXECUTABLE_OUTPUT_PATH}/uri_fails_to_handle_file_scheme_relative_paths_regression_suite )

add_executable( uri_get_parameter_fails_to_handle_empty_values_regression_suite uri_get_parameter_fails_to_handle_empty_values_regression_suite.cpp )
target_link_libraries( uri_get_parameter_fails_to_handle_empty_values_regression_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( uri_get_parameter_fails_to_handle_empty_values_regression_suite ${EXECUTABLE_OUTPUT_PATH}/uri_get_parameter_fails_to_handle_empty_values_regression_suite )
