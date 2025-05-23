project( "feature test suite" )

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
add_executable( publishing_single_path_resources_http_get_feature_test_suite ${SOURCE_DIR}/publishing_single_path_resources/http_get.cpp )
target_link_libraries( publishing_single_path_resources_http_get_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_single_path_resources_http_get_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_single_path_resources_http_get_feature_test_suite )

add_executable( publishing_single_path_resources_http_put_feature_test_suite ${SOURCE_DIR}/publishing_single_path_resources/http_put.cpp )
target_link_libraries( publishing_single_path_resources_http_put_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_single_path_resources_http_put_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_single_path_resources_http_put_feature_test_suite )

add_executable( publishing_single_path_resources_http_head_feature_test_suite ${SOURCE_DIR}/publishing_single_path_resources/http_head.cpp )
target_link_libraries( publishing_single_path_resources_http_head_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_single_path_resources_http_head_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_single_path_resources_http_head_feature_test_suite )

add_executable( publishing_single_path_resources_http_post_feature_test_suite ${SOURCE_DIR}/publishing_single_path_resources/http_post.cpp )
target_link_libraries( publishing_single_path_resources_http_post_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_single_path_resources_http_post_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_single_path_resources_http_post_feature_test_suite )

add_executable( publishing_single_path_resources_http_trace_feature_test_suite ${SOURCE_DIR}/publishing_single_path_resources/http_trace.cpp )
target_link_libraries( publishing_single_path_resources_http_trace_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_single_path_resources_http_trace_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_single_path_resources_http_trace_feature_test_suite )

add_executable( publishing_single_path_resources_http_patch_feature_test_suite ${SOURCE_DIR}/publishing_single_path_resources/http_patch.cpp )
target_link_libraries( publishing_single_path_resources_http_patch_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_single_path_resources_http_patch_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_single_path_resources_http_patch_feature_test_suite )

add_executable( publishing_single_path_resources_http_delete_feature_test_suite ${SOURCE_DIR}/publishing_single_path_resources/http_delete.cpp )
target_link_libraries( publishing_single_path_resources_http_delete_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_single_path_resources_http_delete_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_single_path_resources_http_delete_feature_test_suite )

add_executable( publishing_single_path_resources_http_connect_feature_test_suite ${SOURCE_DIR}/publishing_single_path_resources/http_connect.cpp )
target_link_libraries( publishing_single_path_resources_http_connect_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_single_path_resources_http_connect_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_single_path_resources_http_connect_feature_test_suite )

add_executable( publishing_single_path_resources_http_options_feature_test_suite ${SOURCE_DIR}/publishing_single_path_resources/http_options.cpp )
target_link_libraries( publishing_single_path_resources_http_options_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_single_path_resources_http_options_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_single_path_resources_http_options_feature_test_suite )

add_executable( publishing_multi_path_resources_http_get_feature_test_suite ${SOURCE_DIR}/publishing_multi_path_resources/http_get.cpp )
target_link_libraries( publishing_multi_path_resources_http_get_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_multi_path_resources_http_get_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_multi_path_resources_http_get_feature_test_suite )

add_executable( publishing_multi_path_resources_http_put_feature_test_suite ${SOURCE_DIR}/publishing_multi_path_resources/http_put.cpp )
target_link_libraries( publishing_multi_path_resources_http_put_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_multi_path_resources_http_put_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_multi_path_resources_http_put_feature_test_suite )

add_executable( publishing_multi_path_resources_http_head_feature_test_suite ${SOURCE_DIR}/publishing_multi_path_resources/http_head.cpp )
target_link_libraries( publishing_multi_path_resources_http_head_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_multi_path_resources_http_head_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_multi_path_resources_http_head_feature_test_suite )

add_executable( publishing_multi_path_resources_http_post_feature_test_suite ${SOURCE_DIR}/publishing_multi_path_resources/http_post.cpp )
target_link_libraries( publishing_multi_path_resources_http_post_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_multi_path_resources_http_post_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_multi_path_resources_http_post_feature_test_suite )

add_executable( publishing_multi_path_resources_http_trace_feature_test_suite ${SOURCE_DIR}/publishing_multi_path_resources/http_trace.cpp )
target_link_libraries( publishing_multi_path_resources_http_trace_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_multi_path_resources_http_trace_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_multi_path_resources_http_trace_feature_test_suite )

add_executable( publishing_multi_path_resources_http_patch_feature_test_suite ${SOURCE_DIR}/publishing_multi_path_resources/http_patch.cpp )
target_link_libraries( publishing_multi_path_resources_http_patch_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_multi_path_resources_http_patch_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_multi_path_resources_http_patch_feature_test_suite )

add_executable( publishing_multi_path_resources_http_delete_feature_test_suite ${SOURCE_DIR}/publishing_multi_path_resources/http_delete.cpp )
target_link_libraries( publishing_multi_path_resources_http_delete_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_multi_path_resources_http_delete_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_multi_path_resources_http_delete_feature_test_suite )

add_executable( publishing_multi_path_resources_http_connect_feature_test_suite ${SOURCE_DIR}/publishing_multi_path_resources/http_connect.cpp )
target_link_libraries( publishing_multi_path_resources_http_connect_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_multi_path_resources_http_connect_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_multi_path_resources_http_connect_feature_test_suite )

add_executable( publishing_multi_path_resources_http_options_feature_test_suite ${SOURCE_DIR}/publishing_multi_path_resources/http_options.cpp )
target_link_libraries( publishing_multi_path_resources_http_options_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publishing_multi_path_resources_http_options_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publishing_multi_path_resources_http_options_feature_test_suite )

add_executable( custom_http_methods_http_get_feature_test_suite ${SOURCE_DIR}/custom_http_methods/http_get.cpp )
target_link_libraries( custom_http_methods_http_get_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_http_methods_http_get_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_http_methods_http_get_feature_test_suite )

add_executable( custom_http_methods_http_put_feature_test_suite ${SOURCE_DIR}/custom_http_methods/http_put.cpp )
target_link_libraries( custom_http_methods_http_put_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_http_methods_http_put_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_http_methods_http_put_feature_test_suite )

add_executable( custom_http_methods_http_head_feature_test_suite ${SOURCE_DIR}/custom_http_methods/http_head.cpp )
target_link_libraries( custom_http_methods_http_head_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_http_methods_http_head_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_http_methods_http_head_feature_test_suite )

add_executable( custom_http_methods_http_post_feature_test_suite ${SOURCE_DIR}/custom_http_methods/http_post.cpp )
target_link_libraries( custom_http_methods_http_post_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_http_methods_http_post_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_http_methods_http_post_feature_test_suite )

add_executable( custom_http_methods_http_trace_feature_test_suite ${SOURCE_DIR}/custom_http_methods/http_trace.cpp )
target_link_libraries( custom_http_methods_http_trace_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_http_methods_http_trace_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_http_methods_http_trace_feature_test_suite )

add_executable( custom_http_methods_http_patch_feature_test_suite ${SOURCE_DIR}/custom_http_methods/http_patch.cpp )
target_link_libraries( custom_http_methods_http_patch_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_http_methods_http_patch_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_http_methods_http_patch_feature_test_suite )

add_executable( custom_http_methods_http_delete_feature_test_suite ${SOURCE_DIR}/custom_http_methods/http_delete.cpp )
target_link_libraries( custom_http_methods_http_delete_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_http_methods_http_delete_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_http_methods_http_delete_feature_test_suite )

add_executable( custom_http_methods_http_connect_feature_test_suite ${SOURCE_DIR}/custom_http_methods/http_connect.cpp )
target_link_libraries( custom_http_methods_http_connect_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_http_methods_http_connect_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_http_methods_http_connect_feature_test_suite )

add_executable( custom_http_methods_http_options_feature_test_suite ${SOURCE_DIR}/custom_http_methods/http_options.cpp )
target_link_libraries( custom_http_methods_http_options_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_http_methods_http_options_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_http_methods_http_options_feature_test_suite )

add_executable( custom_http_methods_http_invoke_feature_test_suite ${SOURCE_DIR}/custom_http_methods/http_invoke.cpp )
target_link_libraries( custom_http_methods_http_invoke_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_http_methods_http_invoke_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_http_methods_http_invoke_feature_test_suite )

add_executable( http_method_handlers_http_get_feature_test_suite ${SOURCE_DIR}/http_method_handlers/http_get.cpp )
target_link_libraries( http_method_handlers_http_get_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( http_method_handlers_http_get_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_method_handlers_http_get_feature_test_suite )

add_executable( http_method_handlers_http_put_feature_test_suite ${SOURCE_DIR}/http_method_handlers/http_put.cpp )
target_link_libraries( http_method_handlers_http_put_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( http_method_handlers_http_put_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_method_handlers_http_put_feature_test_suite )

add_executable( http_method_handlers_http_head_feature_test_suite ${SOURCE_DIR}/http_method_handlers/http_head.cpp )
target_link_libraries( http_method_handlers_http_head_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( http_method_handlers_http_head_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_method_handlers_http_head_feature_test_suite )

add_executable( http_method_handlers_http_post_feature_test_suite ${SOURCE_DIR}/http_method_handlers/http_post.cpp )
target_link_libraries( http_method_handlers_http_post_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( http_method_handlers_http_post_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_method_handlers_http_post_feature_test_suite )

add_executable( http_method_handlers_http_trace_feature_test_suite ${SOURCE_DIR}/http_method_handlers/http_trace.cpp )
target_link_libraries( http_method_handlers_http_trace_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( http_method_handlers_http_trace_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_method_handlers_http_trace_feature_test_suite )

add_executable( http_method_handlers_http_patch_feature_test_suite ${SOURCE_DIR}/http_method_handlers/http_patch.cpp )
target_link_libraries( http_method_handlers_http_patch_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( http_method_handlers_http_patch_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_method_handlers_http_patch_feature_test_suite )

add_executable( http_method_handlers_http_delete_feature_test_suite ${SOURCE_DIR}/http_method_handlers/http_delete.cpp )
target_link_libraries( http_method_handlers_http_delete_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( http_method_handlers_http_delete_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_method_handlers_http_delete_feature_test_suite )

add_executable( http_method_handlers_http_connect_feature_test_suite ${SOURCE_DIR}/http_method_handlers/http_connect.cpp )
target_link_libraries( http_method_handlers_http_connect_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( http_method_handlers_http_connect_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_method_handlers_http_connect_feature_test_suite )

add_executable( http_method_handlers_http_options_feature_test_suite ${SOURCE_DIR}/http_method_handlers/http_options.cpp )
target_link_libraries( http_method_handlers_http_options_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( http_method_handlers_http_options_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_method_handlers_http_options_feature_test_suite )

add_executable( custom_service_authentication_feature_test_suite ${SOURCE_DIR}/custom_authentication/service.cpp )
target_link_libraries( custom_service_authentication_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_service_authentication_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_service_authentication_feature_test_suite )

add_executable( custom_resource_authentication_feature_test_suite ${SOURCE_DIR}/custom_authentication/resource.cpp )
target_link_libraries( custom_resource_authentication_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_resource_authentication_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_resource_authentication_feature_test_suite )

add_executable( custom_failed_service_filter_validation_handler_feature_test_suite ${SOURCE_DIR}/custom_failed_resource_filter_validation_handler/service.cpp )
target_link_libraries( custom_failed_service_filter_validation_handler_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_failed_service_filter_validation_handler_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_failed_service_filter_validation_handler_feature_test_suite )

add_executable( custom_failed_resource_filter_validation_handler_feature_test_suite ${SOURCE_DIR}/custom_failed_resource_filter_validation_handler/resource.cpp )
target_link_libraries( custom_failed_resource_filter_validation_handler_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_failed_resource_filter_validation_handler_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_failed_resource_filter_validation_handler_feature_test_suite )

add_executable( custom_method_not_allowed_handler_feature_test_suite ${SOURCE_DIR}/custom_method_not_allowed_handler/feature.cpp )
target_link_libraries( custom_method_not_allowed_handler_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_method_not_allowed_handler_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_method_not_allowed_handler_feature_test_suite )

add_executable( custom_method_not_implemented_handler_feature_test_suite ${SOURCE_DIR}/custom_method_not_implemented_handler/feature.cpp )
target_link_libraries( custom_method_not_implemented_handler_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_method_not_implemented_handler_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_method_not_implemented_handler_feature_test_suite )

add_executable( custom_resource_not_found_handler_feature_test_suite ${SOURCE_DIR}/custom_resource_not_found_handler/feature.cpp )
target_link_libraries( custom_resource_not_found_handler_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_resource_not_found_handler_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_resource_not_found_handler_feature_test_suite )

add_executable( path_parameters_feature_test_suite ${SOURCE_DIR}/path_parameters/feature.cpp )
target_link_libraries( path_parameters_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( path_parameters_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/path_parameters_feature_test_suite )

add_executable( query_parameters_feature_test_suite ${SOURCE_DIR}/query_parameters/feature.cpp )
target_link_libraries( query_parameters_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( query_parameters_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/query_parameters_feature_test_suite )

add_executable( resource_method_filters_feature_test_suite ${SOURCE_DIR}/resource_method_filters/feature.cpp )
target_link_libraries( resource_method_filters_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( resource_method_filters_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/resource_method_filters_feature_test_suite )

add_executable( runtime_service_modifications_feature_test_suite ${SOURCE_DIR}/runtime_service_modifications/feature.cpp )
target_link_libraries( runtime_service_modifications_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( runtime_service_modifications_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/runtime_service_modifications_feature_test_suite )

add_executable( publish_duplicate_resources_feature_test_suite ${SOURCE_DIR}/publish_duplicate_resources/feature.cpp )
target_link_libraries( publish_duplicate_resources_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( publish_duplicate_resources_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/publish_duplicate_resources_feature_test_suite )

add_executable( custom_service_error_handling_feature_test_suite ${SOURCE_DIR}/custom_error_handling/service.cpp )
target_link_libraries( custom_service_error_handling_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_service_error_handling_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_service_error_handling_feature_test_suite )

add_executable( custom_resource_error_handling_feature_test_suite ${SOURCE_DIR}/custom_error_handling/resource.cpp )
target_link_libraries( custom_resource_error_handling_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_resource_error_handling_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_resource_error_handling_feature_test_suite )

add_executable( case_insensitive_service_feature_test_suite ${SOURCE_DIR}/service_case_sensitivity/case_insensitive.cpp )
target_link_libraries( case_insensitive_service_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( case_insensitive_service_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/case_insensitive_service_feature_test_suite )

add_executable( service_rules_engine_feature_test_suite ${SOURCE_DIR}/rules_engine/service.cpp )
target_link_libraries( service_rules_engine_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( service_rules_engine_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/service_rules_engine_feature_test_suite )

add_executable( resource_rules_engine_feature_test_suite ${SOURCE_DIR}/rules_engine/resource.cpp )
target_link_libraries( resource_rules_engine_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( resource_rules_engine_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/resource_rules_engine_feature_test_suite )

add_executable( mixed_rules_engine_feature_test_suite ${SOURCE_DIR}/rules_engine/mixed.cpp )
target_link_libraries( mixed_rules_engine_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( mixed_rules_engine_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/mixed_rules_engine_feature_test_suite )

add_executable( http_client_connect_feature_test_suite ${SOURCE_DIR}/http_client/connect.cpp )
target_link_libraries( http_client_connect_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( http_client_connect_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_client_connect_feature_test_suite )

add_executable( http_client_fetch_feature_test_suite ${SOURCE_DIR}/http_client/fetch.cpp )
target_link_libraries( http_client_fetch_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( http_client_fetch_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_client_fetch_feature_test_suite )

add_executable( http_client_close_feature_test_suite ${SOURCE_DIR}/http_client/close.cpp )
target_link_libraries( http_client_close_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( http_client_close_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_client_close_feature_test_suite )

add_executable( http_client_async_feature_test_suite ${SOURCE_DIR}/http_client/async.cpp )
target_link_libraries( http_client_async_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( http_client_async_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_client_async_feature_test_suite )

add_executable( http_client_keep_alive_feature_test_suite ${SOURCE_DIR}/http_client/keep_alive.cpp )
target_link_libraries( http_client_keep_alive_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( http_client_keep_alive_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_client_keep_alive_feature_test_suite )

add_executable( custom_status_message_feature_test_suite ${SOURCE_DIR}/custom_status_message/feature.cpp )
target_link_libraries( custom_status_message_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( custom_status_message_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/custom_status_message_feature_test_suite )

add_executable( signal_handling_feature_test_suite ${SOURCE_DIR}/signal_handling/feature.cpp )
target_link_libraries( signal_handling_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( signal_handling_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/signal_handling_feature_test_suite )

add_executable( service_connection_timeout_feature_test_suite ${SOURCE_DIR}/connection_timeout/server.cpp )
target_link_libraries( service_connection_timeout_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( service_connection_timeout_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/service_connection_timeout_feature_test_suite )

add_executable( client_connection_timeout_feature_test_suite ${SOURCE_DIR}/connection_timeout/client.cpp )
target_link_libraries( client_connection_timeout_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( client_connection_timeout_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/client_connection_timeout_feature_test_suite )

add_executable( service_status_feature_test_suite ${SOURCE_DIR}/service_status/feature.cpp )
target_link_libraries( service_status_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
add_test( service_status_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/service_status_feature_test_suite )

if ( BUILD_IPC )
    add_executable( ipc_service_feature_test_suite ${SOURCE_DIR}/ipc_service/feature.cpp )
    target_link_libraries( ipc_service_feature_test_suite ${STATIC_LIBRARY_NAME} ${OPENSSL_DEPS}  ${catch_main_LIBRARY_STATIC} ${catch_LIBRARY_STATIC} )
    add_test( ipc_service_feature_test_suite ${EXECUTABLE_OUTPUT_PATH}/ipc_service_feature_test_suite )
endif ( )
