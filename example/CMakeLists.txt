project( "example" )

cmake_minimum_required( VERSION 3.1.0 FATAL_ERROR )

#
# Configuration
#
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/example" )

#
# Build
#
add_executable( custom_status_codes custom_status_codes/source/example.cpp )
target_link_libraries( custom_status_codes ${STATIC_LIBRARY_NAME} )

add_executable( digest_authentication digest_authentication/source/example.cpp )
target_link_libraries( digest_authentication ${STATIC_LIBRARY_NAME} )

add_executable( error_handling error_handling/source/example.cpp )
target_link_libraries( error_handling ${STATIC_LIBRARY_NAME} )

add_executable( logging logging/source/example.cpp )
target_link_libraries( logging ${STATIC_LIBRARY_NAME} )

add_executable( path_parameters path_parameters/source/example.cpp )
target_link_libraries( path_parameters ${STATIC_LIBRARY_NAME} )

add_executable( publishing_resources publishing_resources/source/example.cpp )
target_link_libraries( publishing_resources ${STATIC_LIBRARY_NAME} )

add_executable( custom_methods custom_methods/source/example.cpp )
target_link_libraries( custom_methods ${STATIC_LIBRARY_NAME} )

add_executable( publishing_multipath_resources publishing_multipath_resources/source/example.cpp )
target_link_libraries( publishing_multipath_resources ${STATIC_LIBRARY_NAME} )

add_executable( resource_filtering resource_filtering/source/example.cpp )
target_link_libraries( resource_filtering ${STATIC_LIBRARY_NAME} )

add_executable( serving_html serving_html/source/example.cpp )
target_link_libraries( serving_html ${STATIC_LIBRARY_NAME} )

add_executable( transfer_encoding_request transfer_encoding_request/source/example.cpp )
target_link_libraries( transfer_encoding_request ${STATIC_LIBRARY_NAME} )

add_executable( transfer_encoding_response transfer_encoding_response/source/example.cpp )
target_link_libraries( transfer_encoding_response ${STATIC_LIBRARY_NAME} )

add_executable( persistent_connection persistent_connection/source/example.cpp )
target_link_libraries( persistent_connection ${STATIC_LIBRARY_NAME} )

add_executable( compression compression/source/example.cpp )
target_link_libraries( compression ${STATIC_LIBRARY_NAME} )

add_executable( http_service http_service/source/example.cpp )
target_link_libraries( http_service ${STATIC_LIBRARY_NAME} )

add_executable( service_ready_handler service_ready_handler/source/example.cpp )
target_link_libraries( service_ready_handler ${STATIC_LIBRARY_NAME} )

add_executable( session_data session_data/source/example.cpp )
target_link_libraries( session_data ${STATIC_LIBRARY_NAME} )

add_executable( rules_engine rules_engine/source/example.cpp )
target_link_libraries( rules_engine ${STATIC_LIBRARY_NAME} )

add_executable( multithreaded_service multithreaded_service/source/example.cpp )
target_link_libraries( multithreaded_service ${STATIC_LIBRARY_NAME} )

add_executable( schedule_work_on_service_runloop schedule_work_on_service_runloop/source/example.cpp )
target_link_libraries( schedule_work_on_service_runloop ${STATIC_LIBRARY_NAME} )

add_executable( bind_service_address bind_service_address/source/example.cpp )
target_link_libraries( bind_service_address ${STATIC_LIBRARY_NAME} )

add_executable( session_manager session_manager/source/example.cpp )
target_link_libraries( session_manager ${STATIC_LIBRARY_NAME} )

add_executable( http_client http_client/source/example.cpp )
target_link_libraries( http_client ${STATIC_LIBRARY_NAME} )

add_executable( signal_handling signal_handling/source/example.cpp )
target_link_libraries( signal_handling ${STATIC_LIBRARY_NAME} )

add_executable( server_sent_events server_sent_events/source/example.cpp )
target_link_libraries( server_sent_events ${STATIC_LIBRARY_NAME} )

add_executable( http_pipelining http_pipelining/source/example.cpp )
target_link_libraries( http_pipelining ${STATIC_LIBRARY_NAME} )

if ( BUILD_SSL )
    add_executable( https_service https_service/source/example.cpp )
    target_link_libraries( https_service ${STATIC_LIBRARY_NAME} )

    add_executable( https_client_verify_none https_client/source/verify_none.cpp )
    target_link_libraries( https_client_verify_none ${STATIC_LIBRARY_NAME} )

    add_executable( https_client_verify_peer https_client/source/verify_peer.cpp )
    target_link_libraries( https_client_verify_peer ${STATIC_LIBRARY_NAME} )

    add_executable( web_socket web_socket/source/example.cpp )
    target_link_libraries( web_socket ${STATIC_LIBRARY_NAME} ${ssl_LIBRARY} ${crypto_LIBRARY} )
endif ( )

#
# Install
#
if ( NOT DEFINED CMAKE_INSTALL_LIBDIR )
    set( EXAMPLE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX})
    set( RESOURCE_INSTALL_DIR "${EXAMPLE_INSTALL_DIR}/resource")
else ( )
    set( EXAMPLE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/restbed" )
    set( RESOURCE_INSTALL_DIR "${EXAMPLE_INSTALL_DIR}/${PROJECT_NAME}/resource")
endif ( )

install( DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/example" DESTINATION ${EXAMPLE_INSTALL_DIR} FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE )

install( DIRECTORY "${CMAKE_SOURCE_DIR}/example/https_client/resource/certificates" DESTINATION ${RESOURCE_INSTALL_DIR} FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE )

install( FILES "${CMAKE_SOURCE_DIR}/example/compression/resource/data.zlib" DESTINATION ${RESOURCE_INSTALL_DIR} )
install( FILES "${CMAKE_SOURCE_DIR}/example/serving_html/resource/index.html" DESTINATION ${RESOURCE_INSTALL_DIR} )
install( FILES "${CMAKE_SOURCE_DIR}/example/web_socket/resource/web_socket.html" DESTINATION ${RESOURCE_INSTALL_DIR} )
install( FILES "${CMAKE_SOURCE_DIR}/example/server_sent_events/resource/server_sent_events.html" DESTINATION ${RESOURCE_INSTALL_DIR} )
install( FILES "${CMAKE_SOURCE_DIR}/example/transfer_encoding_request/resource/request.txt" DESTINATION ${RESOURCE_INSTALL_DIR} )
