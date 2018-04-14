project( "example" )

cmake_minimum_required( VERSION 3.1.0 FATAL_ERROR )

#
# Configuration
#
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/example" )

#
# Build
#
if ( BUILD_SSL )
    add_executable( https_client_verify_none https_client/source/verify_none.cpp )
    target_link_libraries( https_client_verify_none ${STATIC_LIBRARY_NAME} )

    add_executable( https_client_verify_peer https_client/source/verify_peer.cpp )
    target_link_libraries( https_client_verify_peer ${STATIC_LIBRARY_NAME} )
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

install( FILES "${CMAKE_SOURCE_DIR}/example/server_sent_events/resource/server_sent_events.html" DESTINATION ${RESOURCE_INSTALL_DIR} )
