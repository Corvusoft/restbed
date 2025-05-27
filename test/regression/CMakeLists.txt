project( "regression test suite" )

cmake_minimum_required( VERSION 3.22.0 FATAL_ERROR )

#
# Configuration
#
set( SOURCE_DIR "source" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCATCH_CONFIG_MAIN" )

include_directories( SYSTEM ${catch_INCLUDE} ${asio_INCLUDE} )

if( ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_WIN32_WINNT=0x0A00 /W4 /wd4068 /wd4702 /wd4996 /wd4265" )
endif ( )

if ( WIN32 )
	set( OPENSSL_DEPS ws2_32.lib advapi32.lib crypt32.lib gdi32.lib user32.lib )
endif ( )

#
# Build
#
add_executable( missing_regex_support_on_gcc_4.8_regression_test_suite ${SOURCE_DIR}/missing_regex_support_on_gcc_4.8.cpp )
target_link_libraries( missing_regex_support_on_gcc_4.8_regression_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( missing_regex_support_on_gcc_4.8_regression_test_suite ${EXECUTABLE_OUTPUT_PATH}/missing_regex_support_on_gcc_4.8_regression_test_suite )

add_executable( resource_error_handler_overflow_regression_test_suite ${SOURCE_DIR}/resource_error_handler_overflow.cpp )
target_link_libraries( resource_error_handler_overflow_regression_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( resource_error_handler_overflow_regression_test_suite ${EXECUTABLE_OUTPUT_PATH}/resource_error_handler_overflow_regression_test_suite )

add_executable( service_error_handler_overflow_regression_test_suite ${SOURCE_DIR}/service_error_handler_overflow.cpp )
target_link_libraries( service_error_handler_overflow_regression_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( service_error_handler_overflow_regression_test_suite ${EXECUTABLE_OUTPUT_PATH}/service_error_handler_overflow_regression_test_suite )

add_executable( ssl_settings_to_handle_windows_path_regression_test_suite ${SOURCE_DIR}/ssl_settings_to_handle_windows_paths.cpp )
target_link_libraries( ssl_settings_to_handle_windows_path_regression_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( ssl_settings_to_handle_windows_path_regression_test_suite ${EXECUTABLE_OUTPUT_PATH}/ssl_settings_to_handle_windows_path_regression_test_suite )

add_executable( uncaught_exception_when_peer_closes_connection_regression_test_suite ${SOURCE_DIR}/uncaught_exception_when_peer_closes_connection.cpp )
target_link_libraries( uncaught_exception_when_peer_closes_connection_regression_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( uncaught_exception_when_peer_closes_connection_regression_test_suite ${EXECUTABLE_OUTPUT_PATH}/uncaught_exception_when_peer_closes_connection_regression_test_suite )

add_executable( uri_fails_to_handle_file_scheme_relative_paths_regression_test_suite ${SOURCE_DIR}/uri_fails_to_handle_file_scheme_relative_paths.cpp )
target_link_libraries( uri_fails_to_handle_file_scheme_relative_paths_regression_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( uri_fails_to_handle_file_scheme_relative_paths_regression_test_suite ${EXECUTABLE_OUTPUT_PATH}/uri_fails_to_handle_file_scheme_relative_paths_regression_test_suite )

add_executable( uri_get_parameter_fails_to_handle_empty_values_regression_test_suite ${SOURCE_DIR}/uri_get_parameter_fails_to_handle_empty_values.cpp )
target_link_libraries( uri_get_parameter_fails_to_handle_empty_values_regression_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( uri_get_parameter_fails_to_handle_empty_values_regression_test_suite ${EXECUTABLE_OUTPUT_PATH}/uri_get_parameter_fails_to_handle_empty_values_regression_test_suite )
